#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* --- Register and Stack Definitions --- */
#define R_UNDEF -1
#define R_FLAG 0
#define R_IP 1
#define R_BP 2
#define R_JP 3
#define R_TP 4
#define R_GEN 5
#define R_NUM 64

#define FORMAL_OFF -4
#define OBP_OFF 0
#define RET_OFF 4
#define LOCAL_OFF 8

#define MODIFIED 1
#define UNMODIFIED 0

/* --- TAC Operation Codes --- */
#define TAC_UNDEF 0
#define TAC_ADD 1
#define TAC_SUB 2
#define TAC_MUL 3
#define TAC_DIV 4
#define TAC_EQ 5
#define TAC_NE 6
#define TAC_LT 7
#define TAC_LE 8
#define TAC_GT 9
#define TAC_GE 10
#define TAC_NEG 11
#define TAC_COPY 12
#define TAC_GOTO 13
#define TAC_IFZ 14
#define TAC_BEGINFUNC 15
#define TAC_ENDFUNC 16
#define TAC_LABEL 17
#define TAC_VAR 18
#define TAC_FORMAL 19
#define TAC_ACTUAL 20
#define TAC_CALL 21
#define TAC_RETURN 22
#define TAC_INPUT 23
#define TAC_OUTPUT 24
#define TAC_ADDR 25
#define TAC_DEREF 26
#define TAC_STORE 27

/* Data types */
#define TYPE_INT  1
#define TYPE_CHAR 2
#define TYPE_STRUCT 3

/* Symbol Types */
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_TEXT 3
#define SYM_INT 4
#define SYM_LABEL 5
#define SYM_STRUCT_TAG 6
#define SYM_CHAR 7

/* Forward declarations */
typedef struct sym SYM;
typedef struct tac TAC;

/* Symbol structure */
typedef struct sym
{
    int type;
    int data_type;
    int is_ptr;
    int is_array;
    int array_size;
    int scope;
    char *name;
    int offset;
    int value;
    int label;
    struct sym *struct_tag;
    struct tac *address;
    struct sym *next;
    void *etc;
} SYM;

/* TAC instruction structure */
typedef struct tac
{
    struct tac *next;
    struct tac *prev;
    int op;
    SYM *a;
    SYM *b;
    SYM *c;
    void *etc;
} TAC;

/* Enhanced register descriptor with usage tracking */
struct rdesc
{
    SYM *var;
    int mod;
    int read_count;
    int write_count;
    int last_use;
    int pinned;         /* Register cannot be spilled */
    int preferred;      /* Preferred register for this variable */
};

/* Global variables */
FILE *file_s = NULL;
int scope = 0, next_tmp = 0, next_label = 1;
SYM *sym_tab_global = NULL, *sym_tab_local = NULL;
TAC *tac_first = NULL, *tac_last = NULL;

/* Register optimization state */
static int last_jump_valid = 0;
static char last_jump_label_name[128];
int tos = 0, tof = 0, oof = 0, oon = 0;
struct rdesc rdesc[R_NUM];
static int timestamp = 0;
static int call_count = 0;

/* Register pressure tracking */
static int reg_pressure = 0;
static int max_reg_pressure = 0;

/* ========== ORIGINAL PARSE FUNCTIONS ========== */
/* --- Forward declarations for assembly generation functions --- */
void asm_write_back(int r);
void asm_load(int r, SYM *s);
void asm_bin_optimized(char *op, SYM *a, SYM *b, SYM *c);
void asm_copy_optimized(SYM *a, SYM *b);
void asm_cmp_optimized(int op, SYM *a, SYM *b, SYM *c);
void asm_cond_optimized(char *op, SYM *a, char *l);
void asm_call_optimized(SYM *a, SYM *b);
void asm_return_optimized(SYM *a);
void asm_addr_optimized(SYM *a, SYM *b);
void asm_deref_optimized(SYM *a, SYM *b);
void asm_store_optimized(SYM *a, SYM *b);
void asm_imm_add(SYM *a, SYM *b, int imm);
void asm_imm_sub(SYM *a, SYM *b, int imm);
void asm_imm_mul(SYM *a, SYM *b, int imm);

void tac_init(void)
{
    scope = 0;
    sym_tab_global = NULL;
    sym_tab_local = NULL;
    next_tmp = 0;
    next_label = 1;
    tac_first = NULL;
    tac_last = NULL;
    timestamp = 0;
    max_reg_pressure = 0;
    reg_pressure = 0;
}

void tac_complete(void)
{
    TAC *cur = NULL;
    TAC *prev = tac_last;
    
    while (prev != NULL) {
        prev->next = cur;
        cur = prev;
        prev = prev->prev;
    }
    
    tac_first = cur;
}

SYM *lookup_sym(SYM *symtab, char *name)
{
    SYM *t = symtab;
    while (t != NULL) {
        if (t->name && strcmp(t->name, name) == 0)
            return t;
        t = t->next;
    }
    return NULL;
}

void insert_sym(SYM **symtab, SYM *sym)
{
    sym->next = *symtab;
    *symtab = sym;
}

SYM *mk_sym(void)
{
    SYM *t = (SYM *)malloc(sizeof(SYM));
    memset(t, 0, sizeof(SYM));
    t->offset = -1;
    t->data_type = TYPE_INT;
    return t;
}

SYM *mk_var(char *name)
{
    SYM *sym = NULL;
    
    if (scope)
        sym = lookup_sym(sym_tab_local, name);
    else
        sym = lookup_sym(sym_tab_global, name);
    
    if (sym != NULL) {
        return sym;
    }
    
    sym = mk_sym();
    sym->type = SYM_VAR;
    sym->name = strdup(name);
    sym->offset = -1;
    
    if (scope)
        insert_sym(&sym_tab_local, sym);
    else
        insert_sym(&sym_tab_global, sym);
    
    return sym;
}

SYM *mk_label(char *name)
{
    SYM *t = mk_sym();
    t->type = SYM_LABEL;
    t->name = strdup(name);
    return t;
}

SYM *mk_const(int n)
{
    char name[32];
    sprintf(name, "%d", n);
    SYM *sym = lookup_sym(sym_tab_global, name);
    if (sym)
        return sym;
    
    sym = mk_sym();
    sym->type = SYM_INT;
    sym->value = n;
    sym->name = strdup(name);
    insert_sym(&sym_tab_global, sym);
    return sym;
}

SYM *mk_text(char *text)
{
    SYM *sym = lookup_sym(sym_tab_global, text);
    if (sym)
        return sym;
    
    sym = mk_sym();
    sym->type = SYM_TEXT;
    sym->name = strdup(text);
    sym->label = next_label++;
    insert_sym(&sym_tab_global, sym);
    return sym;
}

SYM *mk_tmp(void)
{
    char name[32];
    sprintf(name, "t%d", next_tmp++);
    return mk_var(strdup(name));
}

SYM *mk_char_const(char c)
{
    char name[4];
    sprintf(name, "'%c'", c);
    
    SYM *sym = lookup_sym(sym_tab_global, name);
    if (sym) return sym;
    
    sym = mk_sym();
    sym->type = SYM_INT;
    sym->data_type = TYPE_CHAR;
    sym->value = (unsigned char)c;
    sym->name = strdup(name);
    insert_sym(&sym_tab_global, sym);
    return sym;
}

TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c)
{
    TAC *t = (TAC *)malloc(sizeof(TAC));
    t->next = NULL;
    t->prev = NULL;
    t->op = op;
    t->a = a;
    t->b = b;
    t->c = c;
    t->etc = NULL;
    return t;
}

TAC *join_tac(TAC *c1, TAC *c2)
{
    TAC *t;
    if (c1 == NULL) return c2;
    if (c2 == NULL) return c1;
    
    t = c2;
    while (t->prev != NULL)
        t = t->prev;
    
    t->prev = c1;
    return c2;
}

void error(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

void out_str(FILE *f, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(f, format, args);
    va_end(args);
}

/* Helper: find an existing TEXT symbol by label id */
static SYM *find_text_by_label(int lbl)
{
    for (SYM *s = sym_tab_global; s != NULL; s = s->next)
    {
        if (s->type == SYM_TEXT && s->label == lbl)
            return s;
    }
    return NULL;
}

/* Helper: create a TEXT symbol with a specific label id and content */
static SYM *mk_text_labeled(int lbl, const char *content_with_quotes)
{
    SYM *exist = find_text_by_label(lbl);
    if (exist)
        return exist;
    SYM *sym = mk_sym();
    sym->type = SYM_TEXT;
    sym->name = strdup(content_with_quotes);
    sym->label = lbl;
    insert_sym(&sym_tab_global, sym);
    return sym;
}

/* ========== REGISTER OPTIMIZATION FUNCTIONS ========== */

void rdesc_init(void)
{
    for (int i = 0; i < R_NUM; i++) {
        rdesc[i].var = NULL;
        rdesc[i].mod = 0;
        rdesc[i].read_count = 0;
        rdesc[i].write_count = 0;
        rdesc[i].last_use = 0;
        rdesc[i].pinned = 0;
        rdesc[i].preferred = 0;
    }
}

void rdesc_clear(int r)
{
    rdesc[r].var = NULL;
    rdesc[r].mod = 0;
    rdesc[r].read_count = 0;
    rdesc[r].write_count = 0;
    rdesc[r].last_use = 0;
    rdesc[r].pinned = 0;
    rdesc[r].preferred = 0;
}

void rdesc_fill(int r, SYM *s, int mod)
{
    /* Clear any existing entries for this symbol */
    for (int old = R_GEN; old < R_NUM; old++) {
        if (rdesc[old].var == s && old != r) {
            rdesc_clear(old);
        }
    }
    
    rdesc[r].var = s;
    rdesc[r].mod = mod;
    if (mod == MODIFIED) {
        rdesc[r].write_count++;
    } else {
        rdesc[r].read_count++;
    }
    rdesc[r].last_use = timestamp;
    
    /* Pin important registers */
    if (s && (s->name[0] != 't' || s->is_ptr)) {
        rdesc[r].pinned = 1;
    }
}

void rdesc_pin(int r)
{
    rdesc[r].pinned = 1;
}

void rdesc_unpin(int r)
{
    rdesc[r].pinned = 0;
}

void update_reg_pressure(void)
{
    reg_pressure = 0;
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var != NULL) {
            reg_pressure++;
        }
    }
    if (reg_pressure > max_reg_pressure) {
        max_reg_pressure = reg_pressure;
    }
}

double calculate_reg_score(int r, int current_time)
{
    if (rdesc[r].var == NULL) {
        return -1000.0; /* Free registers have highest priority */
    }
    
    if (rdesc[r].pinned) {
        return 1000.0; /* Pinned registers are last to spill */
    }
    
    double score = 0.0;
    
    /* Frequency-based scoring */
    int total_access = rdesc[r].read_count + rdesc[r].write_count;
    if (total_access > 0) {
        double frequency_score = total_access * 5.0;
        double read_ratio = (double)rdesc[r].read_count / total_access;
        double balance_score = read_ratio * 20.0;
        score += frequency_score + balance_score;
    }
    
    /* Recency scoring - prefer to keep recently used registers */
    double time_decay = 1.0 / (1.0 + (current_time - rdesc[r].last_use) * 0.1);
    score += time_decay * 50.0;
    
    /* Modification penalty - modified registers are more expensive to spill */
    if (rdesc[r].mod) {
        score += 25.0;
    }
    
    /* Temporary variables are easier to spill */
    if (rdesc[r].var->name && rdesc[r].var->name[0] == 't') {
        score -= 15.0;
    }
    
    /* Pointer variables should be kept in registers */
    if (rdesc[r].var->is_ptr) {
        score += 30.0;
    }
    
    return score;
}

int find_best_reg_to_spill(void)
{
    int best_reg = -1;
    double best_score = 1e9;
    
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var != NULL && !rdesc[r].pinned) {
            double score = calculate_reg_score(r, timestamp);
            if (score < best_score) {
                best_score = score;
                best_reg = r;
            }
        }
    }
    
    /* If no unpinned registers, spill the lowest scored pinned register */
    if (best_reg == -1) {
        best_score = 1e9;
        for (int r = R_GEN; r < R_NUM; r++) {
            if (rdesc[r].var != NULL) {
                double score = calculate_reg_score(r, timestamp);
                if (score < best_score) {
                    best_score = score;
                    best_reg = r;
                }
            }
        }
    }
    
    return best_reg;
}

int get_free_register(void)
{
    timestamp++;
    
    /* First try to find completely free register */
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == NULL) {
            return r;
        }
    }
    
    /* Try to find unmodified register */
    for (int r = R_GEN; r < R_NUM; r++) {
        if (!rdesc[r].mod && !rdesc[r].pinned) {
            asm_write_back(r);
            rdesc_clear(r);
            return r;
        }
    }
    
    /* Find best register to spill */
    int spill_reg = find_best_reg_to_spill();
    if (spill_reg != -1) {
        asm_write_back(spill_reg);
        rdesc_clear(spill_reg);
        return spill_reg;
    }
    
    /* Last resort - use R_GEN */
    asm_write_back(R_GEN);
    rdesc_clear(R_GEN);
    return R_GEN;
}

int reg_alloc(SYM *s)
{
    timestamp++;
    
    /* Check if already in register */
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == s) {
            rdesc[r].last_use = timestamp;
            rdesc[r].read_count++;
            return r;
        }
    }
    
    /* Allocate new register */
    int r = get_free_register();
    asm_load(r, s);
    rdesc_fill(r, s, UNMODIFIED);
    
    update_reg_pressure();
    return r;
}

void asm_write_back(int r)
{
    if (rdesc[r].var != NULL && rdesc[r].mod) {
        if (rdesc[r].var->scope == 1) { /* Local variable */
            if (rdesc[r].var->offset >= 0)
                out_str(file_s, "\tSTO (R%u+%d),R%u\n", R_BP, rdesc[r].var->offset, r);
            else
                out_str(file_s, "\tSTO (R%u-%d),R%u\n", R_BP, -rdesc[r].var->offset, r);
        } else { /* Global variable */
            out_str(file_s, "\tLOD R%u,STATIC\n", R_TP);
            if (rdesc[r].var->offset >= 0)
                out_str(file_s, "\tSTO (R%u+%d),R%u\n", R_TP, rdesc[r].var->offset, r);
            else
                out_str(file_s, "\tSTO (R%u-%d),R%u\n", R_TP, -rdesc[r].var->offset, r);
        }
        rdesc[r].mod = UNMODIFIED;
    }
}

void asm_write_back_all(void)
{
    for (int r = R_GEN; r < R_NUM; r++) {
        asm_write_back(r);
    }
}

void asm_load(int r, SYM *s)
{
    /* Check if variable is already in a register */
    for (int i = R_GEN; i < R_NUM; i++) {
        if (rdesc[i].var == s) {
            out_str(file_s, "\tLOD R%u,R%u\n", r, i);
            return;
        }
    }
    
    /* Variable not in register - load from memory */
    switch (s->type) {
        case SYM_INT:
            out_str(file_s, "\tLOD R%u,%u\n", r, s->value);
            break;
            
        case SYM_VAR:
            if (s->scope == 1) { /* Local variable */
                if (s->offset >= 0)
                    out_str(file_s, "\tLOD R%u,(R%u+%d)\n", r, R_BP, s->offset);
                else
                    out_str(file_s, "\tLOD R%u,(R%u-%d)\n", r, R_BP, -s->offset);
            } else { /* Global variable */
                out_str(file_s, "\tLOD R%u,STATIC\n", R_TP);
                if (s->offset >= 0)
                    out_str(file_s, "\tLOD R%u,(R%u+%d)\n", r, R_TP, s->offset);
                else
                    out_str(file_s, "\tLOD R%u,(R%u-%d)\n", r, R_TP, -s->offset);
            }
            break;
            
        case SYM_TEXT:
            out_str(file_s, "\tLOD R%u,L%u\n", r, s->label);
            break;
            
        default:
            out_str(file_s, "\tLOD R%u,0\n", r);
            break;
    }
}

void asm_bin_optimized(char *op, SYM *a, SYM *b, SYM *c)
{
    int reg_b = reg_alloc(b);
    int reg_c = reg_alloc(c);
    
    /* Smart register selection to avoid conflicts */
    if (reg_b == reg_c) {
        /* Find alternative register for c */
        int new_reg = -1;
        for (int r = R_GEN; r < R_NUM; r++) {
            if (r != reg_b && (rdesc[r].var == NULL || !rdesc[r].pinned)) {
                new_reg = r;
                if (rdesc[r].var != NULL) {
                    asm_write_back(r);
                    rdesc_clear(r);
                }
                break;
            }
        }
        
        if (new_reg == -1) {
            new_reg = (reg_b == R_GEN) ? R_GEN + 1 : R_GEN;
            asm_write_back(new_reg);
            rdesc_clear(new_reg);
        }
        
        asm_load(new_reg, c);
        rdesc_fill(new_reg, c, UNMODIFIED);
        reg_c = new_reg;
    }
    
    /* Try to reuse destination register if possible */
    int target_reg = -1;
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == a) {
            target_reg = r;
            break;
        }
    }
    
    if (target_reg != -1 && target_reg != reg_b && target_reg != reg_c) {
        /* Destination already has a register - use it */
        if (target_reg != reg_b) {
            out_str(file_s, "\tLOD R%u,R%u\n", target_reg, reg_b);
        }
        out_str(file_s, "\t%s R%u,R%u\n", op, target_reg, reg_c);
        rdesc_fill(target_reg, a, MODIFIED);
    } else {
        /* Use source register as destination */
        out_str(file_s, "\t%s R%u,R%u\n", op, reg_b, reg_c);
        rdesc_fill(reg_b, a, MODIFIED);
    }
}

void asm_copy_optimized(SYM *a, SYM *b)
{
    if (a == b) return; /* Self-assignment, no-op */
    
    int src_reg = reg_alloc(b);
    
    /* Check if destination already has a register */
    int dst_reg = -1;
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == a) {
            dst_reg = r;
            break;
        }
    }
    
    if (dst_reg != -1 && dst_reg != src_reg) {
        /* Destination has different register - copy value */
        out_str(file_s, "\tLOD R%u,R%u\n", dst_reg, src_reg);
        rdesc_fill(dst_reg, a, MODIFIED);
    } else if (dst_reg == -1) {
        /* Destination not in register - reuse source register */
        rdesc_fill(src_reg, a, MODIFIED);
    }
    /* If dst_reg == src_reg, no operation needed */
}

void asm_cmp_optimized(int op, SYM *a, SYM *b, SYM *c)
{
    int reg_b = -1, reg_c = -1;
    
    /* Ensure different registers for comparison */
    int attempts = 0;
    do {
        reg_b = reg_alloc(b);
        reg_c = reg_alloc(c);
        attempts++;
        
        if (reg_b == reg_c && attempts < 3) {
            /* Force different register for c */
            int new_reg = (reg_b == R_GEN) ? R_GEN + 1 : R_GEN;
            if (rdesc[new_reg].var != NULL) {
                asm_write_back(new_reg);
                rdesc_clear(new_reg);
            }
            asm_load(new_reg, c);
            rdesc_fill(new_reg, c, UNMODIFIED);
            reg_c = new_reg;
        }
    } while (reg_b == reg_c && attempts < 3);
    
    /* Generate comparison */
    out_str(file_s, "\tSUB R%u,R%u\n", reg_b, reg_c);
    out_str(file_s, "\tTST R%u\n", reg_b);
    
    int label_true = next_label++;
    int label_false = next_label++;
    int label_end = next_label++;
    
    switch (op) {
        case TAC_EQ:
            out_str(file_s, "\tJEZ L%d\n", label_true);
            break;
        case TAC_NE:
            out_str(file_s, "\tJNZ L%d\n", label_true);
            break;
        case TAC_LT:
            out_str(file_s, "\tJLZ L%d\n", label_true);
            break;
        case TAC_LE:
            out_str(file_s, "\tJLE L%d\n", label_true);
            break;
        case TAC_GT:
            out_str(file_s, "\tJGZ L%d\n", label_true);
            break;
        case TAC_GE:
            out_str(file_s, "\tJGE L%d\n", label_true);
            break;
    }
    
    out_str(file_s, "\tLOD R%u,0\n", reg_b);
    out_str(file_s, "\tJMP L%d\n", label_end);
    out_str(file_s, "L%d:\n", label_true);
    out_str(file_s, "\tLOD R%u,1\n", reg_b);
    out_str(file_s, "L%d:\n", label_end);
    
    rdesc_fill(reg_b, a, MODIFIED);
}

void asm_cond_optimized(char *op, SYM *a, char *l)
{
    /* Smart conditional jump - only write back if necessary */
    if (a != NULL) {
        int r;
        for (r = R_GEN; r < R_NUM; r++) {
            if (rdesc[r].var == a) break;
        }
        
        if (r < R_NUM) {
            out_str(file_s, "\tTST R%u\n", r);
        } else {
            int temp_reg = reg_alloc(a);
            out_str(file_s, "\tTST R%u\n", temp_reg);
            /* Don't keep temporary condition values in registers */
            rdesc_clear(temp_reg);
        }
    }
    
    out_str(file_s, "\t%s %s\n", op, l);
    last_jump_valid = 1;
    snprintf(last_jump_label_name, sizeof(last_jump_label_name), "%s", l);
}

void asm_call_optimized(SYM *a, SYM *b)
{
    /* Write back only modified registers before call */
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].mod && rdesc[r].var && rdesc[r].var->name && rdesc[r].var->name[0] != 't') {
            asm_write_back(r);
        }
    }
    
    call_count++;
    
    /* Save current frame */
    out_str(file_s, "\tSTO (R2+%d),R2\n", tof + oon);
    
    /* Set return address */
    out_str(file_s, "\tLOD R4,LRET%d\n", call_count);
    out_str(file_s, "\tSTO (R2+%d),R4\n", tof + oon + 4);
    
    /* Switch to new frame */
    out_str(file_s, "\tLOD R2,R2+%d\n", tof + oon);
    
    /* Jump to function */
    out_str(file_s, "\tJMP %s\n", b->name);
    
    /* Return point label */
    out_str(file_s, "LRET%d:\n", call_count);
    
    /* Get return value */
    if (a != NULL) {
        int r_dst = get_free_register();
        out_str(file_s, "\tLOD R%u,R%u\n", r_dst, R_TP);
        rdesc_fill(r_dst, a, MODIFIED);
    }
    
    oon = 0;
}

void asm_return_optimized(SYM *a)
{
    /* Write back all persistent variables */
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var && rdesc[r].var->name && rdesc[r].var->name[0] != 't') {
            asm_write_back(r);
        }
    }
    
    if (a != NULL) {
        asm_load(R_TP, a);
    }
    
    out_str(file_s, "\tLOD R3,(R2+4)\n");
    out_str(file_s, "\tLOD R2,(R2)\n");
    out_str(file_s, "\tJMP R3\n");
    
    /* Clear all registers after return */
    for (int r = R_GEN; r < R_NUM; r++) {
        rdesc_clear(r);
    }
}

void asm_addr_optimized(SYM *a, SYM *b)
{
    int r_dst = get_free_register();
    if (b->scope == 1) { /* Local variable */
        out_str(file_s, "\tLOD R%u,R%u\n", r_dst, R_BP);
        if (b->offset != 0) {
            if (b->offset > 0)
                out_str(file_s, "\tADD R%u,%d\n", r_dst, b->offset);
            else
                out_str(file_s, "\tSUB R%u,%d\n", r_dst, -b->offset);
        }
    } else { /* Global variable */
        // 正确计算全局变量地址
        out_str(file_s, "\tLOD R%u,STATIC\n", r_dst);
        if (b->offset != 0) {
            if (b->offset > 0)
                out_str(file_s, "\tADD R%u,%d\n", r_dst, b->offset);
            else
                out_str(file_s, "\tSUB R%u,%d\n", r_dst, -b->offset);
        }
    }
    rdesc_fill(r_dst, a, MODIFIED);
    rdesc_pin(r_dst); /* Pin pointer registers */
}

void asm_deref_optimized(SYM *a, SYM *b)
{
    int r_ptr = reg_alloc(b);
    int r_dst = get_free_register();
    out_str(file_s, "\tLOD R%u,(R%u)\n", r_dst, r_ptr);
    rdesc_fill(r_dst, a, MODIFIED);
}

void asm_store_optimized(SYM *a, SYM *b)
{
    int r_ptr = reg_alloc(a);
    int r_val = reg_alloc(b);
    
    /* Ensure different registers */
    if (r_ptr == r_val) {
        int temp_reg = (r_ptr == R_GEN) ? R_GEN + 1 : R_GEN;
        if (rdesc[temp_reg].var != NULL) {
            asm_write_back(temp_reg);
            rdesc_clear(temp_reg);
        }
        out_str(file_s, "\tLOD R%u,R%u\n", temp_reg, r_val);
        r_val = temp_reg;
    }
    
    out_str(file_s, "\tSTO (R%u),R%u\n", r_ptr, r_val);
}

void asm_imm_add(SYM *a, SYM *b, int imm)
{
    if (imm == 0) {
        asm_copy_optimized(a, b);
        return;
    }
    
    int reg_b = reg_alloc(b);
    if (imm > 0) {
        out_str(file_s, "\tADD R%u,%d\n", reg_b, imm);
    } else {
        out_str(file_s, "\tSUB R%u,%d\n", reg_b, -imm);
    }
    rdesc_fill(reg_b, a, MODIFIED);
}

void asm_imm_sub(SYM *a, SYM *b, int imm)
{
    if (imm == 0) {
        asm_copy_optimized(a, b);
        return;
    }
    
    int reg_b = reg_alloc(b);
    if (imm > 0) {
        out_str(file_s, "\tSUB R%u,%d\n", reg_b, imm);
    } else {
        out_str(file_s, "\tADD R%u,%d\n", reg_b, -imm);
    }
    rdesc_fill(reg_b, a, MODIFIED);
}

void asm_imm_mul(SYM *a, SYM *b, int imm)
{
    if (imm == 0) {
        int r = get_free_register();
        out_str(file_s, "\tLOD R%u,0\n", r);
        rdesc_fill(r, a, MODIFIED);
        return;
    }
    
    if (imm == 1) {
        asm_copy_optimized(a, b);
        return;
    }
    
    int reg_b = reg_alloc(b);
    
    out_str(file_s, "\tMUL R%u,%d\n", reg_b, imm);
    
    rdesc_fill(reg_b, a, MODIFIED);
}

int can_eliminate_move(SYM *a, SYM *b)
{
    /* Check if this move can be eliminated by register coalescing */
    if (a == b) return 1;
    
    /* Check if both variables are already in the same register */
    int reg_a = -1, reg_b = -1;
    for (int r = R_GEN; r < R_NUM; r++) {
        if (rdesc[r].var == a) reg_a = r;
        if (rdesc[r].var == b) reg_b = r;
    }
    
    return (reg_a != -1 && reg_b != -1 && reg_a == reg_b);
}

void peephole_optimize(TAC *tac)
{
    /* Simple peephole optimizations at TAC level */
    if (tac->op == TAC_COPY && can_eliminate_move(tac->a, tac->b)) {
        tac->op = TAC_UNDEF; /* Mark for elimination */
    }
}

/* ========== ORIGINAL PARSE UTILITY FUNCTIONS ========== */

static void str_trim(char *s)
{
    char *p = s;
    while (*p && isspace((unsigned char)*p))
        p++;
    if (p != s)
        memmove(s, p, strlen(p) + 1);
    int len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1]))
        s[--len] = '\0';
}

static void strip_addr_prefix(char *s)
{
    str_trim(s);
    size_t len = strlen(s);
    if (len < 3)
        return;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
    {
        size_t i = 2;
        while (i < len && isxdigit((unsigned char)s[i]))
            i++;
        while (i < len && (s[i] == ' ' || s[i] == '\t'))
            i++;
        if (i < len)
        {
            memmove(s, s + i, len - i + 1);
        }
        else
        {
            s[0] = '\0';
        }
    }
}

static void print_sym_token(FILE *f, SYM *s)
{
    if (!s)
    {
        fprintf(f, "null");
        return;
    }
    switch (s->type)
    {
    case SYM_INT:
        fprintf(f, "%d", s->value);
        break;
    case SYM_VAR:
        fprintf(f, "%s", s->name ? s->name : "?");
        break;
    case SYM_TEXT:
        fprintf(f, "L%u", (unsigned)s->label);
        break;
    case SYM_LABEL:
        fprintf(f, "%s", s->name ? s->name : "?");
        break;
    default:
        fprintf(f, "%s", s->name ? s->name : "?");
        break;
    }
}

static void out_tac_comment(FILE *f, TAC *t)
{
    fprintf(f, "\n\t# ");
    switch (t->op)
    {
    case TAC_BEGINFUNC:
        fprintf(f, "begin");
        break;
    case TAC_ENDFUNC:
        fprintf(f, "end");
        break;
    case TAC_LABEL:
        fprintf(f, "label ");
        print_sym_token(f, t->a);
        break;
    case TAC_VAR:
        fprintf(f, "var ");
        print_sym_token(f, t->a);
        break;
    case TAC_FORMAL:
        fprintf(f, "formal ");
        print_sym_token(f, t->a);
        break;
    case TAC_GOTO:
        fprintf(f, "goto ");
        print_sym_token(f, t->a);
        break;
    case TAC_IFZ:
        fprintf(f, "ifz ");
        print_sym_token(f, t->b);
        fprintf(f, " goto ");
        print_sym_token(f, t->a);
        break;
    case TAC_INPUT:
        fprintf(f, "input ");
        print_sym_token(f, t->a);
        break;
    case TAC_OUTPUT:
        fprintf(f, "output ");
        print_sym_token(f, t->a);
        break;
    case TAC_COPY:
        print_sym_token(f, t->a);
        fprintf(f, " = ");
        print_sym_token(f, t->b);
        break;
    case TAC_NEG:
        print_sym_token(f, t->a);
        fprintf(f, " = -");
        print_sym_token(f, t->b);
        break;
    case TAC_ADD:
        print_sym_token(f, t->a);
        fprintf(f, " = ");
        print_sym_token(f, t->b);
        fprintf(f, " + ");
        print_sym_token(f, t->c);
        break;
    case TAC_SUB:
        print_sym_token(f, t->a);
        fprintf(f, " = ");
        print_sym_token(f, t->b);
        fprintf(f, " - ");
        print_sym_token(f, t->c);
        break;
    case TAC_MUL:
        print_sym_token(f, t->a);
        fprintf(f, " = ");
        print_sym_token(f, t->b);
        fprintf(f, " * ");
        print_sym_token(f, t->c);
        break;
    case TAC_DIV:
        print_sym_token(f, t->a);
        fprintf(f, " = ");
        print_sym_token(f, t->b);
        fprintf(f, " / ");
        print_sym_token(f, t->c);
        break;
    case TAC_EQ:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " == ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_NE:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " != ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_LT:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " < ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_LE:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " <= ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_GT:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " > ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_GE:
        print_sym_token(f, t->a);
        fprintf(f, " = (");
        print_sym_token(f, t->b);
        fprintf(f, " >= ");
        print_sym_token(f, t->c);
        fprintf(f, ")");
        break;
    case TAC_ACTUAL:
        fprintf(f, "actual ");
        print_sym_token(f, t->a);
        break;
    case TAC_CALL:
        fprintf(f, "call ");
        print_sym_token(f, t->b);
        break;
    case TAC_RETURN:
        fprintf(f, "return ");
        if (t->a)
            print_sym_token(f, t->a);
        break;
    default:
        break;
    }
}

int is_number_token(const char *t)
{
    if (!t || !*t)
        return 0;
    const char *p = t;
    if (*p == '-' || *p == '+')
        p++;
    if (!*p)
        return 0;
    while (*p)
    {
        if (!isdigit((unsigned char)*p))
            return 0;
        p++;
    }
    return 1;
}

SYM *sym_from_token(char *tok)
{
    if (tok == NULL)
        return NULL;
    
    if (tok[0] == 'L')
    {
        const char *p = tok + 1;
        int ok = 1;
        if (!*p)
            ok = 0;
        while (*p)
        {
            if (!isdigit((unsigned char)*p))
            {
                ok = 0;
                break;
            }
            p++;
        }
        if (ok)
        {
            int lbl = atoi(tok + 1);
            if (lbl == 1)
            {
                return mk_text_labeled(lbl, "\"\\n\"");
            }
            else if (lbl == 3)
            {
                return mk_text_labeled(lbl, "\" \"");
            }
            else if (lbl == 6)
            {
                return mk_text_labeled(lbl, "\"\\n\"");
            }
            else
            {
                return mk_text_labeled(lbl, "\"\"");
            }
        }
    }
    
    if (is_number_token(tok))
    {
        int v = atoi(tok);
        return mk_const(v);
    }
    
    if (tok[0] == '\'')
    {
        return mk_text(tok);
    }
    
    SYM *s = lookup_sym(sym_tab_local, tok);
    if (!s)
        s = lookup_sym(sym_tab_global, tok);
    if (s)
        return s;

    return mk_var(strdup(tok));
}

/* ========== COMPLETE PARSE FUNCTION ========== */

void parse_input_file(FILE *in)
{
    char line[1024];
    TAC *last = NULL;
    while (fgets(line, sizeof(line), in))
    {
        str_trim(line);
        strip_addr_prefix(line);
        if (line[0] == '\0')
            continue;
        if (line[0] == '#')
            continue;

        TAC *t = NULL;

        if (strcmp(line, "undef") == 0)
        {
            t = mk_tac(TAC_UNDEF, NULL, NULL, NULL);
        }
        else if (strcmp(line, "begin") == 0)
        {
            t = mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL);
            scope = 1;
        }
        else if (strcmp(line, "end") == 0)
        {
            t = mk_tac(TAC_ENDFUNC, NULL, NULL, NULL);
        }
        else if (strncmp(line, "goto ", 5) == 0)
        {
            char *name = line + 5;
            str_trim(name);
            SYM *a = mk_label(name);
            t = mk_tac(TAC_GOTO, a, NULL, NULL);
        }
        else if (strncmp(line, "label ", 6) == 0)
        {
            char *name = line + 6;
            str_trim(name);
            SYM *a = mk_label(name);
            t = mk_tac(TAC_LABEL, a, NULL, NULL);
        }
        else if (strncmp(line, "actual ", 7) == 0)
        {
            char *tok = line + 7;
            str_trim(tok);
            SYM *a = sym_from_token(tok);
            t = mk_tac(TAC_ACTUAL, a, NULL, NULL);
        }
        else if (strncmp(line, "formal ", 7) == 0)
        {
            char *tok = line + 7;
            str_trim(tok);
            SYM *a = sym_from_token(tok);
            t = mk_tac(TAC_FORMAL, a, NULL, NULL);
        }
        else if (strncmp(line, "call ", 5) == 0)
        {
            char *name = line + 5;
            str_trim(name);
            SYM *func_sym = mk_sym();
            func_sym->type = SYM_FUNC;
            func_sym->name = strdup(name);
            t = mk_tac(TAC_CALL, NULL, func_sym, NULL);
        }
        else if (strncmp(line, "input ", 6) == 0)
        {
            char *tok = line + 6;
            str_trim(tok);
            SYM *a = sym_from_token(tok);
            t = mk_tac(TAC_INPUT, a, NULL, NULL);
        }
        else if (strncmp(line, "output ", 7) == 0)
        {
            char *tok = line + 7;
            str_trim(tok);
            SYM *a = sym_from_token(tok);
            t = mk_tac(TAC_OUTPUT, a, NULL, NULL);
        }
        else if (strncmp(line, "ifz ", 4) == 0)
        {
            char *rest = line + 4;
            str_trim(rest);
            char *p = strstr(rest, " goto ");
            if (p)
            {
                *p = '\0';
                char *cond = rest;
                str_trim(cond);
                char *lab = p + 6;
                str_trim(lab);
                SYM *b = sym_from_token(cond);
                SYM *a = mk_label(lab);
                t = mk_tac(TAC_IFZ, a, b, NULL);
            }
            else
            {
                t = NULL;
            }
        }
        else if (strncmp(line, "return ", 7) == 0)
        {
            char *tok = line + 7;
            str_trim(tok);
            SYM *a = sym_from_token(tok);
            t = mk_tac(TAC_RETURN, a, NULL, NULL);
        }
        else if (strncmp(line, "var ", 4) == 0)
        {
            char *tok = line + 4;
            str_trim(tok);
            SYM *a = mk_var(strdup(tok));
            t = mk_tac(TAC_VAR, a, NULL, NULL);
        }
        else
        {
            char *eq = strstr(line, " = ");
            if (eq)
            {
                char left[256];
                strncpy(left, line, eq - line);
                left[eq - line] = '\0';
                str_trim(left);
                char *rhs = eq + 3;
                str_trim(rhs);

                char *pos;
                if ((pos = strstr(rhs, " + ")))
                {
                    char b[256], c[256];
                    strncpy(b, rhs, pos - rhs);
                    b[pos - rhs] = '\0';
                    strcpy(c, pos + 3);
                    str_trim(b);
                    str_trim(c);
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(b);
                    SYM *C = sym_from_token(c);
                    t = mk_tac(TAC_ADD, A, B, C);
                }
                else if ((pos = strstr(rhs, " - ")))
                {
                    char b[256], c[256];
                    strncpy(b, rhs, pos - rhs);
                    b[pos - rhs] = '\0';
                    strcpy(c, pos + 3);
                    str_trim(b);
                    str_trim(c);
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(b);
                    SYM *C = sym_from_token(c);
                    t = mk_tac(TAC_SUB, A, B, C);
                }
                else if ((pos = strstr(rhs, " * ")))
                {
                    char b[256], c[256];
                    strncpy(b, rhs, pos - rhs);
                    b[pos - rhs] = '\0';
                    strcpy(c, pos + 3);
                    str_trim(b);
                    str_trim(c);
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(b);
                    SYM *C = sym_from_token(c);
                    t = mk_tac(TAC_MUL, A, B, C);
                }
                else if ((pos = strstr(rhs, " / ")))
                {
                    char b[256], c[256];
                    strncpy(b, rhs, pos - rhs);
                    b[pos - rhs] = '\0';
                    strcpy(c, pos + 3);
                    str_trim(b);
                    str_trim(c);
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(b);
                    SYM *C = sym_from_token(c);
                    t = mk_tac(TAC_DIV, A, B, C);
                }
                else if (rhs[0] == '(')
                {
                    char tmp[256];
                    size_t len = strlen(rhs);
                    while (len > 0 && isspace((unsigned char)rhs[len - 1]))
                        len--;
                    if (len == 0 || rhs[0] != '(')
                    {
                        strcpy(tmp, rhs);
                    }
                    else
                    {
                        size_t end = len;
                        if (rhs[end - 1] == ')')
                            end--;
                        size_t inner_len = (end > 1 && end - 1 > 0) ? (end - 1) : 0;
                        if (inner_len >= sizeof(tmp))
                            inner_len = sizeof(tmp) - 1;
                        if (inner_len > 0)
                        {
                            memcpy(tmp, rhs + 1, inner_len);
                            tmp[inner_len] = '\0';
                        }
                        else
                        {
                            tmp[0] = '\0';
                        }
                    }
                    char *opstr = NULL;
                    int opcode = TAC_UNDEF;
                    size_t op_len = 0;
                    if ((pos = strstr(tmp, " == ")))
                    {
                        opstr = pos;
                        opcode = TAC_EQ;
                        op_len = 4;
                    }
                    else if ((pos = strstr(tmp, " != ")))
                    {
                        opstr = pos;
                        opcode = TAC_NE;
                        op_len = 4;
                    }
                    else if ((pos = strstr(tmp, " <= ")))
                    {
                        opstr = pos;
                        opcode = TAC_LE;
                        op_len = 4;
                    }
                    else if ((pos = strstr(tmp, " >= ")))
                    {
                        opstr = pos;
                        opcode = TAC_GE;
                        op_len = 4;
                    }
                    else if ((pos = strstr(tmp, " < ")))
                    {
                        opstr = pos;
                        opcode = TAC_LT;
                        op_len = 3;
                    }
                    else if ((pos = strstr(tmp, " > ")))
                    {
                        opstr = pos;
                        opcode = TAC_GT;
                        op_len = 3;
                    }
                    if (opstr)
                    {
                        char b[256], c[256];
                        strncpy(b, tmp, opstr - tmp);
                        b[opstr - tmp] = '\0';
                        strcpy(c, opstr + op_len);
                        str_trim(b);
                        str_trim(c);
                        if (c[0] == '\0')
                            strcpy(c, "0");
                        SYM *A = sym_from_token(left);
                        SYM *B = sym_from_token(b);
                        SYM *C = sym_from_token(c);
                        t = mk_tac(opcode, A, B, C);
                    }
                }
                else if (rhs[0] == '-' && rhs[1] == ' ')
                {
                    char b[256];
                    strcpy(b, rhs + 2);
                    str_trim(b);
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(b);
                    t = mk_tac(TAC_NEG, A, B, NULL);
                }
                else
                {
                    SYM *A = sym_from_token(left);
                    SYM *B = sym_from_token(rhs);
                    t = mk_tac(TAC_COPY, A, B, NULL);
                }
            }
            else
            {
                continue;
            }
        }

        if (t)
        {
            t->prev = last;
            last = t;
        }
    }

    tac_last = last;
    tac_complete();
}

/* ========== ASSEMBLY GENERATION ========== */

void asm_head(void)
{
    out_str(file_s, "\t# head\n");
    out_str(file_s, "\tLOD R2,STACK\n");
    out_str(file_s, "\tSTO (R2),0\n");
    out_str(file_s, "\tLOD R4,EXIT\n");
    out_str(file_s, "\tSTO (R2+4),R4\n");
    out_str(file_s, "\tJMP main\n");
}

void asm_tail(void)
{
    out_str(file_s, "\n\t# tail\n");
    out_str(file_s, "EXIT:\n");
    out_str(file_s, "\tEND\n");
}

void asm_str(SYM *s)
{
    char *t = s->name;
    int i;
    
    out_str(file_s, "L%u:\n", s->label);
    out_str(file_s, "\tDBS ");
    
    for (i = 1; t[i + 1] != 0; i++) {
        if (t[i] == '\\') {
            switch (t[++i]) {
                case 'n':
                    out_str(file_s, "%u,", '\n');
                    break;
                case '\"':
                    out_str(file_s, "%u,", '\"');
                    break;
                default:
                    out_str(file_s, "%u,", t[i]);
                    break;
            }
        } else {
            out_str(file_s, "%u,", t[i]);
        }
    }
    
    out_str(file_s, "0\n");
}

void asm_static(void)
{
    SYM *sl;
    
    for (sl = sym_tab_global; sl != NULL; sl = sl->next) {
        if (sl->type == SYM_TEXT) {
            asm_str(sl);
        }
    }
    
    out_str(file_s, "STATIC:\n");
    out_str(file_s, "\tDBN 0,%u\n", tos);
    out_str(file_s, "STACK:\n");
}

void asm_gen_optimized(void)
{
    TAC *cur;
    
    /* Initialize */
    tos = 0;
    tof = LOCAL_OFF;
    oof = FORMAL_OFF;
    oon = 0;
    rdesc_init();
    
    /* Generate header */
    asm_head();
    
    /* Process all TAC instructions */
    for (cur = tac_first; cur != NULL; cur = cur->next) {
        /* Apply peephole optimization */
        peephole_optimize(cur);
        
        if (cur->op == TAC_UNDEF) continue;
        
        out_tac_comment(file_s, cur);
        out_str(file_s, "\n");
        
        timestamp++;
        
        switch (cur->op) {
            case TAC_ADD:
                if (cur->c && cur->c->type == SYM_INT) {
                    asm_imm_add(cur->a, cur->b, cur->c->value);
                } else {
                    asm_bin_optimized("ADD", cur->a, cur->b, cur->c);
                }
                break;
                
            case TAC_SUB:
                if (cur->c && cur->c->type == SYM_INT) {
                    asm_imm_sub(cur->a, cur->b, cur->c->value);
                } else {
                    asm_bin_optimized("SUB", cur->a, cur->b, cur->c);
                }
                break;
                
            case TAC_MUL:
                if (cur->c && cur->c->type == SYM_INT) {
                    asm_imm_mul(cur->a, cur->b, cur->c->value);
                } else {
                    asm_bin_optimized("MUL", cur->a, cur->b, cur->c);
                }
                break;
                
            case TAC_DIV:
                asm_bin_optimized("DIV", cur->a, cur->b, cur->c);
                break;
                
            case TAC_NEG:
                asm_bin_optimized("SUB", cur->a, mk_const(0), cur->b);
                break;
                
            case TAC_EQ:
            case TAC_NE:
            case TAC_LT:
            case TAC_LE:
            case TAC_GT:
            case TAC_GE:
                asm_cmp_optimized(cur->op, cur->a, cur->b, cur->c);
                break;
                
            case TAC_COPY:
                asm_copy_optimized(cur->a, cur->b);
                break;
                
            case TAC_GOTO:
                asm_cond_optimized("JMP", NULL, cur->a->name);
                break;
                
            case TAC_IFZ:
                asm_cond_optimized("JEZ", cur->b, cur->a->name);
                break;
                
            case TAC_LABEL:
                out_str(file_s, "%s:\n", cur->a->name);
                last_jump_valid = 0;
                break;
                
            case TAC_CALL:
                asm_call_optimized(cur->a, cur->b);
                break;
                
            case TAC_RETURN:
                asm_return_optimized(cur->a);
                break;
                
            case TAC_ADDR:
                asm_addr_optimized(cur->a, cur->b);
                break;
                
            case TAC_DEREF:
                asm_deref_optimized(cur->a, cur->b);
                break;
                
            case TAC_STORE:
                asm_store_optimized(cur->a, cur->b);
                break;
                
            case TAC_BEGINFUNC:
                scope = 1;
                tof = LOCAL_OFF;
                oof = FORMAL_OFF;
                oon = 0;
                break;
                
            case TAC_ENDFUNC:
                scope = 0;
                break;
                
            case TAC_VAR:
                if (scope) {
                    cur->a->scope = 1;
                    cur->a->offset = tof;
                    tof += 4;
                } else {
                    cur->a->scope = 0;
                    cur->a->offset = tos;
                    tos += 4;
                }
                break;
                
            case TAC_FORMAL:
                if (scope) {
                    cur->a->scope = 1;
                    cur->a->offset = oof;
                    oof -= 4;
                }
                break;
                
            case TAC_ACTUAL:
                {
                    int r = reg_alloc(cur->a);
                    out_str(file_s, "\tSTO (R2+%d),R%u\n", tof + oon, r);
                    oon += 4;
                }
                break;
                
            case TAC_INPUT:
                {
                    int r = reg_alloc(cur->a);
                    out_str(file_s, "\tITI\n");
                    out_str(file_s, "\tLOD R%u,R15\n", r);
                    rdesc_fill(r, cur->a, MODIFIED);
                }
                break;
                
            case TAC_OUTPUT:
                if (cur->a->type == SYM_TEXT) {
                    out_str(file_s, "\tLOD R15,L%u\n", cur->a->label);
                    out_str(file_s, "\tOTS\n");
                } else {
                    int r = reg_alloc(cur->a);
                    out_str(file_s, "\tLOD R15,R%u\n", r);
                    out_str(file_s, "\tOTI\n");
                }
                break;
                
            default:
                break;
        }
        
        update_reg_pressure();
    }
    
    /* Generate footer and static data */
    asm_tail();
    asm_static();
    
    fprintf(stderr, "Maximum register pressure: %d/%d\n", max_reg_pressure, R_NUM - R_GEN);
}

/* ========== MAIN FUNCTION ========== */

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input.x> <output.s>\n", argv[0]);
        return 1;
    }
    
    FILE *in = fopen(argv[1], "r");
    if (!in)
    {
        perror("open input");
        return 1;
    }
    
    file_s = fopen(argv[2], "w");
    if (!file_s)
    {
        perror("open output");
        fclose(in);
        return 1;
    }
    
    tac_init();
    parse_input_file(in);
    asm_gen_optimized();
    
    fclose(file_s);
    fclose(in);
    
    printf("Optimized assembly written to %s\n", argv[2]);
    return 0;
}
