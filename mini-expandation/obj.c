#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "tac.h"
#include "obj.h"

/* Global variables */
int tos;  /* Top of static memory area */
int tof;  /* Top of frame */
int oof;  /* Offset of formal parameters */
int oon;  /* Offset of next parameter */
struct rdesc rdesc[R_NUM];  /* Register descriptors */
static int call_count = 0;  /* Counter for function calls */

/**
 * Clear register descriptor
 * @param r Register number to clear
 */
void rdesc_clear(int r)    
{
    rdesc[r].var = NULL;
    rdesc[r].mod = 0;
}

/**
 * Fill register descriptor with variable information
 * @param r Register number
 * @param s Symbol to store in register
 * @param mod Modification status
 */
void rdesc_fill(int r, SYM *s, int mod)
{
    int old;
    /* Clear any existing entries for this symbol */
    for(old=R_GEN; old < R_NUM; old++)
    {
        if(rdesc[old].var==s)
        {
            rdesc_clear(old);
        }
    }
    /* Fill the register descriptor */
    rdesc[r].var=s;
    rdesc[r].mod=mod;
}     

/**
 * Write back modified register to memory
 * @param r Register number to write back
 */
void asm_write_back(int r)
{
    if((rdesc[r].var!=NULL) && rdesc[r].mod)
    {
        /* Temporary variables (offset = -1) don't need to be written back */
        if (rdesc[r].var->offset == -1) {
            fprintf(stderr, "DEBUG: Skipping write back for temporary variable %s\n", rdesc[r].var->name);
            rdesc[r].mod = UNMODIFIED;
            return;
        }

        fprintf(stderr, "DEBUG: Writing back %s to memory (offset=%d, scope=%d)\n", 
                rdesc[r].var->name, rdesc[r].var->offset, rdesc[r].var->scope);

        if(rdesc[r].var->scope==1) /* Local variable */
        {
            if (rdesc[r].var->offset >= 0)
                out_str(file_s, "	STO (R%u+%d),R%u\n", R_BP, rdesc[r].var->offset, r);
            else
                out_str(file_s, "	STO (R%u%d),R%u\n", R_BP, rdesc[r].var->offset, r);
        }
        else /* Global variable */
        {
            out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
            out_str(file_s, "	STO (R%u+%d),R%u\n", R_TP, rdesc[r].var->offset, r);
        }
        rdesc[r].mod=UNMODIFIED;
    }
}

/**
 * Load variable into register
 * @param r Destination register
 * @param s Symbol to load
 */
void asm_load(int r, SYM *s) 
{
    /* Check if variable is already in a register */
    for(int i=R_GEN; i < R_NUM; i++)  
    {
        if(rdesc[i].var==s)
        {
            fprintf(stderr, "DEBUG: Loading %s from register R%d (offset=%d)\n", s->name, i, s->offset);
            /* Load from the existing register */
            out_str(file_s, "	LOD R%u,R%u\n", r, i);
            return;
        }
    }
    
    /* Variable not in register - load from memory */
    fprintf(stderr, "DEBUG: Loading %s from memory (offset=%d, scope=%d)\n", s->name, s->offset, s->scope);
    switch(s->type)
    {
        case SYM_INT:
            out_str(file_s, "	LOD R%u,%u\n", r, s->value);
            break;

        case SYM_VAR:
            /* Temporary variables should not be loaded */
            if (s->offset == -1) {
                fprintf(stderr, "WARNING: trying to load temporary variable %s\n", s->name);
                return;
            }
            
            if(s->scope==1) /* Local variable */
            {
                if((s->offset)>=0) 
                    out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_BP, s->offset);
                else 
                    out_str(file_s, "	LOD R%u,(R%u%d)\n", r, R_BP, s->offset);
            }
            else /* Global variable */
            {
                out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
                out_str(file_s, "	LOD R%u,(R%u+%d)\n", r, R_TP, s->offset);
            }
            break;
            
        case SYM_TEXT:
            out_str(file_s, "	LOD R%u,L%u\n", r, s->label);
            break;
    }
}

/**
 * Get a free register
 * @return Free register number
 */
int get_free_register()
{
    /* First try to find an empty register */
    for(int r=R_GEN; r < R_NUM; r++)
    {
        if(rdesc[r].var==NULL)
        {
            return r;
        }
    }
    
    /* Then try to find an unmodified register */
    for(int r=R_GEN; r < R_NUM; r++)
    {
        if(!rdesc[r].mod)
        {
            rdesc_clear(r);
            return r;
        }
    }
    
    /* Finally, select a random register and write it back */
    int r = R_GEN + (rand() % (R_NUM - R_GEN));
    asm_write_back(r);
    rdesc_clear(r);
    return r;
}

/**
 * Allocate register for variable
 * @param s Symbol to allocate register for
 * @return Register number
 */
int reg_alloc(SYM *s)
{
    int r; 

    /* Handle temporary variables */
    if (s->offset == -1) {
        /* Check if already allocated */
        for(r=R_GEN; r < R_NUM; r++)
        {
            if(rdesc[r].var==s)
            {
                return r;
            }
        }
        
        /* Allocate new register */
        r = get_free_register();
        rdesc_fill(r, s, UNMODIFIED);
        return r;
    }

    /* Check if variable is already in a register */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(rdesc[r].var==s)
        {
            return r;
        }
    }

    /* Try to find an empty register */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(rdesc[r].var==NULL)
        {
            asm_load(r, s);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }
    
    /* Try to find an unmodified register */
    for(r=R_GEN; r < R_NUM; r++)
    {
        if(!rdesc[r].mod)
        {
            asm_load(r, s);
            rdesc_fill(r, s, UNMODIFIED);
            return r;
        }
    }

    /* Allocate random register */
    int random = R_GEN + (rand() % (R_NUM - R_GEN));
    asm_write_back(random);
    asm_load(random, s);
    rdesc_fill(random, s, UNMODIFIED);
    return random;
}

/**
 * Generate binary operation assembly code
 * @param op Operation code
 * @param a Destination symbol
 * @param b First operand symbol
 * @param c Second operand symbol
 */
void asm_bin(char *op, SYM *a, SYM *b, SYM *c)
{
    int reg_b = reg_alloc(b); 
    int reg_c = reg_alloc(c); 
    
    /* Ensure registers are different */
    int attempts = 0;
    while(reg_b == reg_c && attempts < 5)
    {
        /* Find alternative register for c */
        int new_reg = -1;
        for (int r = R_GEN; r < R_NUM; r++) {
            if (r != reg_b) {
                if (rdesc[r].var == NULL || !rdesc[r].mod) {
                    new_reg = r;
                    if (rdesc[r].var != NULL) {
                        asm_write_back(r);
                        rdesc_clear(r);
                    }
                    break;
                }
            }
        }
        
        if (new_reg == -1) {
            /* Force use of different register */
            new_reg = (reg_b == R_GEN) ? R_GEN + 1 : R_GEN;
            asm_write_back(new_reg);
            rdesc_clear(new_reg);
        }
        
        /* Load c into new register */
        asm_load(new_reg, c);
        rdesc_fill(new_reg, c, UNMODIFIED);
        reg_c = new_reg;
        attempts++;
    }
    
    if (reg_b == reg_c) {
        /* Final resort: force allocation */
        reg_c = (reg_b == R_GEN) ? R_GEN + 1 : R_GEN;
        asm_write_back(reg_c);
        rdesc_clear(reg_c);
        asm_load(reg_c, c);
        rdesc_fill(reg_c, c, UNMODIFIED);
    }
    
    /* Generate operation */
    out_str(file_s, "	%s R%u,R%u\n", op, reg_b, reg_c);
    rdesc_fill(reg_b, a, MODIFIED);
}

/**
 * Generate comparison operation assembly code
 * @param op Comparison operation code
 * @param a Destination symbol
 * @param b First operand symbol
 * @param c Second operand symbol
 */
void asm_cmp(int op, SYM *a, SYM *b, SYM *c)
{
    int reg_b=-1, reg_c=-1; 

    /* Ensure registers are different */
    while(reg_b == reg_c)
    {
        reg_b = reg_alloc(b); 
        reg_c = reg_alloc(c); 
    }

    /* Generate comparison */
    out_str(file_s, "	SUB R%u,R%u\n", reg_b, reg_c);
    out_str(file_s, "	TST R%u\n", reg_b);

    int label1 = next_label++;
    int label2 = next_label++;

    switch(op)
    {		
        case TAC_EQ:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JEZ R3\n");
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
        
        case TAC_NE:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JEZ R3\n");
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
        
        case TAC_LT:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JLZ R3\n");
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
        
        case TAC_LE:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JGZ R3\n");
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
        
        case TAC_GT:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JGZ R3\n");
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
        
        case TAC_GE:
            out_str(file_s, "	LOD R3,L%d\n", label1);
            out_str(file_s, "	JLZ R3\n");
            out_str(file_s, "	LOD R%u,1\n", reg_b);
            out_str(file_s, "	LOD R3,L%d\n", label2);
            out_str(file_s, "	JMP R3\n");
            out_str(file_s, "L%d:\n", label1);
            out_str(file_s, "	LOD R%u,0\n", reg_b);
            out_str(file_s, "L%d:\n", label2);
            break;
    }

    /* Update register descriptor */
    rdesc_clear(reg_b);
    rdesc_fill(reg_b, a, MODIFIED);
}

/**
 * Generate conditional jump assembly code
 * @param op Jump operation code
 * @param a Condition symbol
 * @param l Label to jump to
 */
void asm_cond(char *op, SYM *a, char *l)
{
    /* Write back all registers */
    for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);

    if(a !=NULL)
    {
        int r;

        /* Check if condition is in register */
        for(r=R_GEN; r < R_NUM; r++) 
        {
            if(rdesc[r].var==a) break;
        }

        if(r < R_NUM) 
            out_str(file_s, "	TST R%u\n", r);
        else 
            out_str(file_s, "	TST R%u\n", reg_alloc(a)); /* Load into new register */
    }

    /* Generate jump */
    out_str(file_s, "	%s %s\n", op, l); 
} 

/**
 * Generate function call assembly code
 * @param a Return value symbol
 * @param b Function symbol
 */
void asm_call(SYM *a, SYM *b)
{
    /* Write back and clear all registers */
    for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
    for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);
    
    call_count++;
    
    fprintf(stderr, "DEBUG: Function call %s (call_count=%d)\n", b->name, call_count);
    fprintf(stderr, "DEBUG: Current frame offset: %d, parameter offset: %d\n", tof, oon);
    
    /* Save current frame */
    out_str(file_s, "	STO (R2+%d),R2\n", tof+oon);
    
    /* Set return address */
    out_str(file_s, "	LOD R4,LRET%d\n", call_count);
    out_str(file_s, "	STO (R2+%d),R4\n", tof+oon+4);
    
    /* Switch to new frame */
    out_str(file_s, "	LOD R2,R2+%d\n", tof+oon);
    
    /* Jump to function */
    out_str(file_s, "	JMP %s\n", b->name);
    
    /* Return point label */
    out_str(file_s, "LRET%d:\n", call_count);
    
    /* Get return value */
    if(a != NULL)
    {
        int r_dst = get_free_register();
        out_str(file_s, "	LOD R%u,R%u\n", r_dst, R_TP);
        rdesc_fill(r_dst, a, MODIFIED);
    }
    oon=0;
}

/**
 * Generate return statement assembly code
 * @param a Return value symbol
 */
void asm_return(SYM *a)
{
    /* Write back and clear all registers */
    for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
    for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);

    if(a!=NULL)	 /* Return value */
    {
        asm_load(R_TP, a);
    }

    /* Generate return sequence */
    out_str(file_s, "	LOD R3,(R2+4)\n");	/* Return address */
    out_str(file_s, "	LOD R2,(R2)\n");	/* Restore base pointer */
    out_str(file_s, "	JMP R3\n");			/* Return */
}   

/**
 * Generate assembly code header
 */
void asm_head()
{
    char head[]=
    "	# head\n"
    "	LOD R2,STACK\n"
    "	STO (R2),0\n"
    "	LOD R4,EXIT\n"
    "	STO (R2+4),R4\n"
    "	JMP main\n";

    out_str(file_s, "%s", head);
}

/**
 * Generate assembly code footer
 */
void asm_tail()
{
    char tail[]=
    "\n	# tail\n"
    "EXIT:\n"
    "	END\n";

    out_str(file_s, "%s", tail);
}

/**
 * Generate string constant assembly code
 * @param s String symbol
 */
void asm_str(SYM *s)
{
    char *t=s->name; /* The text */
    int i;

    out_str(file_s, "L%u:\n", s->label); /* Label for the string */
    out_str(file_s, "	DBS "); /* Label for the string */

    for(i=1; t[i + 1] !=0; i++)
    {
        if(t[i]=='\\')
        {
            switch(t[++i])
            {
                case 'n':
                    out_str(file_s, "%u,", '\n');
                    break;

                case '\"':
                    out_str(file_s, "%u,", '\"');
                    break;
            }
        }
        else out_str(file_s, "%u,", t[i]);
    }

    out_str(file_s, "0\n"); /* End of string */
}

/**
 * Generate static data area assembly code
 */
void asm_static(void)
{
    SYM *sl;

    /* Generate string constants */
    for(sl=sym_tab_global; sl !=NULL; sl=sl->next)
    {
        if(sl->type==SYM_TEXT) asm_str(sl);
    }

    /* Generate static data area */
    out_str(file_s, "STATIC:\n");
    out_str(file_s, "	DBN 0,%u\n", tos);				
    out_str(file_s, "STACK:\n");
}

/**
 * Generate assembly code for TAC instruction
 * @param c TAC instruction to translate
 */
void asm_code(TAC *c)
{
    int r;

    switch(c->op)
    {
        case TAC_UNDEF:
            error("cannot translate TAC_UNDEF");
            return;

        case TAC_ADD:
            if (c->c->type == SYM_INT) {
                /* Handle address + constant case */
                int reg_b = reg_alloc(c->b);
                if (c->c->value == 0) {
                    /* Adding zero - just copy */
                    rdesc_fill(reg_b, c->a, MODIFIED);
                } else {
                    out_str(file_s, "	ADD R%u,%d\n", reg_b, c->c->value);
                    rdesc_fill(reg_b, c->a, MODIFIED);
                }
            } else {
                asm_bin("ADD", c->a, c->b, c->c);
            }
            return;

        case TAC_SUB:
            asm_bin("SUB", c->a, c->b, c->c);
            return;

        case TAC_MUL:
            if (c->c->type == SYM_INT) {
                /* Handle multiplication by constant */
                int reg_b = reg_alloc(c->b);
                out_str(file_s, "	MUL R%u,%d\n", reg_b, c->c->value);
                rdesc_fill(reg_b, c->a, MODIFIED);
            } else {
                asm_bin("MUL", c->a, c->b, c->c);
            }
            return;

        case TAC_DIV:
            asm_bin("DIV", c->a, c->b, c->c);
            return;

        case TAC_NEG:
            asm_bin("SUB", c->a, mk_const(0), c->b);
            return;

        case TAC_EQ:
        case TAC_NE:
        case TAC_LT:
        case TAC_LE:
        case TAC_GT:
        case TAC_GE:
            asm_cmp(c->op, c->a, c->b, c->c);
            return;

        case TAC_COPY:
        {
            int r_src = reg_alloc(c->b);
            if (c->a->scope == 1) { /* Local variable */
                if (c->a->offset >= 0)
                    out_str(file_s, "	STO (R%u+%d),R%u\n", R_BP, c->a->offset, r_src);
                else
                    out_str(file_s, "	STO (R%u%d),R%u\n", R_BP, c->a->offset, r_src);
            } else { /* Global variable */
                out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
                out_str(file_s, "	STO (R%u+%d),R%u\n", R_TP, c->a->offset, r_src);
            }
            return;
        }

        case TAC_INPUT:
        {
            /* 1. Execute input instruction (read into R15) */
            out_str(file_s, "	ITI\n");
            
            /* 2. Store R15 into variable memory */
            if (c->a->scope == 1) { /* Local variable */
                if (c->a->offset >= 0)
                    out_str(file_s, "	STO (R%u+%d),R15\n", R_BP, c->a->offset);
                else
                    out_str(file_s, "	STO (R%u%d),R15\n", R_BP, c->a->offset);
            } else { /* Global variable */
                out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
                out_str(file_s, "	STO (R%u+%d),R15\n", R_TP, c->a->offset);
            }
            return;
        }
            
        case TAC_OUTPUT:
        {
            /* Check if value is in register */
            int r_val = -1;
            for (int r = R_GEN; r < R_NUM; r++) {
                if (rdesc[r].var == c->a) {
                    r_val = r;
                    break;
                }
            }

            if (r_val != -1) {
                /* Value in register - use directly */
                out_str(file_s, "	LOD R15,R%u\n", r_val);
            } else {
                /* Value not in register - load from memory */
                if (c->a->type == SYM_VAR) {
                    if (c->a->scope == 1) {
                        if (c->a->offset >= 0)
                            out_str(file_s, "	LOD R15,(R%u+%d)\n", R_BP, c->a->offset);
                        else
                            out_str(file_s, "	LOD R15,(R%u-%d)\n", R_BP, -c->a->offset);
                    } else {
                        out_str(file_s, "	LOD R%u,STATIC\n", R_TP);
                        out_str(file_s, "	LOD R15,(R%u+%d)\n", R_TP, c->a->offset);
                    }
                } else if (c->a->type == SYM_TEXT) {
                    out_str(file_s, "	LOD R15,L%u\n", c->a->label);
                    out_str(file_s, "	OTS\n");
                    return;
                } else if (c->a->type == SYM_INT) {
                    out_str(file_s, "	LOD R15,%d\n", c->a->value);
                }
            }

            /* Output value */
            if (c->a->data_type == TYPE_CHAR) {
                out_str(file_s, "	OTC\n");
            } else {
                out_str(file_s, "	OTI\n");
            }
            return;
        }

        case TAC_GOTO:
            asm_cond("JMP", NULL, c->a->name);
            return;

        case TAC_IFZ:
            asm_cond("JEZ", c->b, c->a->name);
            return;

        case TAC_LABEL:
            /* Write back and clear all registers */
            for(int r=R_GEN; r < R_NUM; r++) asm_write_back(r);
            for(int r=R_GEN; r < R_NUM; r++) rdesc_clear(r);
            out_str(file_s, "%s:\n", c->a->name);
            return;

        case TAC_ACTUAL:
            r=reg_alloc(c->a);
            out_str(file_s, "	STO (R2+%d),R%u\n", tof+oon, r);
            oon += 4;
            return;

        case TAC_CALL:
            asm_call(c->a, c->b);
            return;

        case TAC_RETURN:
            asm_return(c->a);
            return;

        case TAC_BEGINFUNC:
            /* Reset top of stack - currently empty except for link information */
            scope=1;
            tof=LOCAL_OFF;
            oof=FORMAL_OFF;
            oon=0;
            return;

        case TAC_ADDR:
        {
            int r_dst = get_free_register();
            if (c->b->scope == 1) {
                /* Local variable: R_BP + offset */
                out_str(file_s, "	LOD R%u,R%u\n", r_dst, R_BP);
                if (c->b->offset != 0) {
                    if (c->b->offset > 0)
                        out_str(file_s, "	ADD R%u,%d\n", r_dst, c->b->offset);
                    else
                        out_str(file_s, "	SUB R%u,%d\n", r_dst, -c->b->offset);
                }
            } else {
                /* Global variable: STATIC + offset */
                out_str(file_s, "	LOD R%u,STATIC\n", r_dst);
                if (c->b->offset != 0) {
                    out_str(file_s, "	ADD R%u,%d\n", r_dst, c->b->offset);
                }
            }
            rdesc_fill(r_dst, c->a, MODIFIED);
            return;
        }

        case TAC_DEREF:
        {
            int r_ptr = reg_alloc(c->b);
            int r_dst = get_free_register();
            fprintf(stderr, "DEBUG: Dereferencing pointer %s (R%d)\n", 
            c->b->name, r_ptr);
            /* Load value from pointer */
            out_str(file_s, "	LOD R%u,(R%u)\n", r_dst, r_ptr);
            rdesc_fill(r_dst, c->a, MODIFIED);
            return;
        }

        case TAC_STORE:
        {
            int r_ptr = reg_alloc(c->a);  /* Get pointer register */
            fprintf(stderr, "DEBUG: Storing value %s through pointer %s (R%d)\n", 
            c->b->name, c->a->name, r_ptr);
            
            /* Special handling for constants to avoid register conflicts */
            if (c->b->type == SYM_INT) {
                /* Find register different from pointer register */
                int r_val = -1;
                for (int r = R_GEN; r < R_NUM; r++) {
                    if (r != r_ptr) {
                        if (rdesc[r].var == NULL || !rdesc[r].mod) {
                            r_val = r;
                            if (rdesc[r].var != NULL) {
                                asm_write_back(r);
                                rdesc_clear(r);
                            }
                            break;
                        }
                    }
                }
                
                if (r_val == -1) {
                    /* Force use of different register */
                    r_val = (r_ptr == R_GEN) ? R_GEN + 1 : R_GEN;
                    asm_write_back(r_val);
                    rdesc_clear(r_val);
                }
                
                /* Load constant and store */
                out_str(file_s, "	LOD R%u,%d\n", r_val, c->b->value);
                out_str(file_s, "	STO (R%u),R%u\n", r_ptr, r_val);
                
                /* Clean up temporary register */
                rdesc_clear(r_val);
            } else {
                /* Handle variable value */
                int r_val = reg_alloc(c->b);
                fprintf(stderr, "DEBUG: Loading value %s into register R%d\n", 
                c->b->name, r_val);
                
                /* Ensure pointer and value are in different registers */
                if (r_ptr == r_val) {
                    int new_reg = -1;
                    for (int r = R_GEN; r < R_NUM; r++) {
                        if (r != r_ptr && (rdesc[r].var == NULL || !rdesc[r].mod)) {
                            new_reg = r;
                            if (rdesc[r].var != NULL) {
                                asm_write_back(r);
                                rdesc_clear(r);
                            }
                            break;
                        }
                    }
                    
                    if (new_reg == -1) {
                        new_reg = (r_ptr == R_GEN) ? R_GEN + 1 : R_GEN;
                        asm_write_back(new_reg);
                        rdesc_clear(new_reg);
                    }
                    
                    /* Copy value to new register */
                    out_str(file_s, "	LOD R%u,R%u\n", new_reg, r_val);
                    r_val = new_reg;
                    rdesc_fill(r_val, c->b, UNMODIFIED);
                }

                /* Store value through pointer */
                out_str(file_s, "	STO (R%u),R%u\n", r_ptr, r_val);
            }
            return;
        }

        case TAC_FORMAL:
            if (scope) {
                c->a->offset = oof;
                oof -= 4;
                fprintf(stderr, "DEBUG: FORMAL %s offset=%d\n", c->a->name, c->a->offset);
            }
            return;

        case TAC_VAR:
        {
            int size = 0;
            if (c->a->data_type == TYPE_STRUCT && c->a->struct_tag) {
                size = calculate_struct_size(c->a->struct_tag);
            } else if (c->a->is_array) {
                size = c->a->array_size * 4;
            } else if (c->a->is_ptr) {
                size = 4; /* Pointer size */
            } else {
                size = 4; /* Regular variable */
            }
            
            if (scope) {
                c->a->offset = tof;
                tof += size;
                fprintf(stderr, "DEBUG: VAR %s offset=%d size=%d scope=local\n", c->a->name, c->a->offset, size);
            } else {
                c->a->offset = tos;
                tos += size;
                fprintf(stderr, "DEBUG: VAR %s offset=%d size=%d scope=global\n", c->a->name, c->a->offset, size);
            }
            break;
        }

    }
}

/**
 * Translate TAC to assembly code
 */
void tac_obj()
{
    /* Initialize stack management variables */
    tos = 0; 
    tof=LOCAL_OFF; /* TOS allows space for link info */
    oof=FORMAL_OFF;
    oon=0;
    /* Clear all register descriptors */
    for(int r=0; r < R_NUM; r++) rdesc[r].var=NULL;
    
    /* Generate header */
    asm_head();

    /* Process all TAC instructions */
    TAC * cur;
    for(cur=tac_first; cur!=NULL; cur=cur->next)
    {
        out_str(file_s, "\n	# ");
        out_tac(file_s, cur);
        out_str(file_s, "\n");
        asm_code(cur);
    }
    /* Generate footer and static data */
    asm_tail();
    asm_static();
}
