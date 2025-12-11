# 编译器功能完整逻辑提取文档

本文档提取了数组、指针、结构体、for循环、break/continue功能的完整实现逻辑，可直接复制使用。

---

## 目录

1. [数组 (Array)](#1-数组-array)
2. [指针 (Pointer)](#2-指针-pointer)
3. [结构体 (Struct)](#3-结构体-struct)
4. [For循环](#4-for循环)

---

## 1. 数组 (Array)

### 1.1 数据结构定义 (tac.h)

```c
// SYM 结构体中数组相关字段
typedef struct sym {
    int is_array;        // 是否为数组
    int array_size;      // 数组大小
    // ... 其他字段
} SYM;

// 访问节点类型
typedef enum {
    ACCESS_MEMBER,    // .member
    ACCESS_INDEX,     // [index]
    ACCESS_DEREF      // *ptr
} ACCESS_TYPE;

// 访问路径节点
typedef struct access_node {
    ACCESS_TYPE type;
    union {
        char *member_name;        // 成员名
        struct exp *index_exp;    // 数组索引表达式
    };
    struct access_node *next;
} ACCESS_NODE;
```

### 1.2 语法规则 (mini.y)

```yacc
// 变量声明中的数组
var_decl
    : IDENTIFIER '[' INTEGER ']'
    {
        $$.name = $1;
        $$.is_ptr = 0;
        $$.is_array = 1;
        $$.array_size = atoi($3);
        $$.struct_tag = NULL;
    }
    ;

// 数组访问
access_item
    : '[' expression ']'
    {
        $$ = mk_access_index($2);
    }
    ;
```

### 1.3 访问节点创建 (tac.c)

```c
// 创建数组索引访问节点
ACCESS_NODE *mk_access_index(EXP *index) {
    ACCESS_NODE *node = malloc(sizeof(ACCESS_NODE));
    node->type = ACCESS_INDEX;
    node->index_exp = index;
    node->next = NULL;
    return node;
}

// 连接访问链
ACCESS_NODE *append_access(ACCESS_NODE *chain, ACCESS_NODE *new_node) {
    if (!chain) return new_node;
    
    ACCESS_NODE *current = chain;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
    return chain;
}
```

### 1.4 数组地址计算 (tac.c - calculate_lvalue_address)

```c
case ACCESS_INDEX: {
    // 数组访问：current_addr + index * element_size
    if (!current_is_array) {
        error("array access on non-array type");
        return NULL;
    }
    
    int element_size = 4; // 默认元素大小
    if (current_data_type == TYPE_STRUCT && current_type) {
        element_size = calculate_struct_size(current_type);
    }

    // 计算索引 * 元素大小
    SYM *scaled_index = mk_tmp();
    TAC *scale_tac = mk_tac(TAC_MUL, scaled_index, node->index_exp->ret, mk_const(element_size));
    scale_tac->prev = join_tac(code, node->index_exp->tac);
    
    // 计算最终地址
    SYM *new_addr = mk_tmp();
    new_addr->is_ptr = 1;
    TAC *add_tac = mk_tac(TAC_ADD, new_addr, current_addr, scaled_index);
    add_tac->prev = scale_tac;
    code = add_tac;
    current_addr = new_addr;
    
    // 数组访问后不再是数组
    current_is_array = 0;
    break;
}
```

### 1.5 数组大小计算 (tac.c)

```c
// 在 calculate_struct_size 中处理数组成员
if (p->a->is_array) {
    if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
        // 结构体数组：元素个数 * 结构体大小
        int element_size = calculate_struct_size(p->a->struct_tag);
        member_size = p->a->array_size * element_size;
    } else {
        // 普通数组
        member_size = p->a->array_size * 4;
    }
}

// 在 calculate_member_offset 中处理数组成员
if (p->a->is_array) {
    if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
        int element_size = calculate_struct_size(p->a->struct_tag);
        member_size = p->a->array_size * element_size;
    } else {
        member_size = p->a->array_size * 4;
    }
}
```

### 1.6 数组变量声明 (tac.c)

```c
TAC *declare_typed_var_ext(char *name, int data_type, int is_ptr, int is_array, int array_size, SYM *struct_tag){
    SYM *sym = NULL;
    if (scope)
        sym = lookup_sym(sym_tab_local, name);
    else
        sym = lookup_sym(sym_tab_global, name);
    if (sym != NULL) {
        error("variable '%s' already declared", name);
        return NULL;
    }
    sym = mk_sym();
    sym->type = SYM_VAR;
    sym->data_type = data_type;
    sym->is_ptr = is_ptr;
    sym->is_array = is_array;
    sym->array_size = array_size;
    sym->name = name;
    sym->scope = scope;
    sym->offset = -1;
    sym->struct_tag = struct_tag; 
    if (scope)
        insert_sym(&sym_tab_local, sym);
    else
        insert_sym(&sym_tab_global, sym);

    TAC *t = mk_tac(TAC_VAR, sym, NULL, NULL);
    return t;
}
```

### 1.7 代码生成 - 数组内存分配 (obj.c)

```c
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
    } else {
        c->a->offset = tos;
        tos += size;
    }
    break;
}
```

---

## 2. 指针 (Pointer)

### 2.1 数据结构定义 (tac.h)

```c
typedef struct sym {
    int is_ptr;          // 是否为指针
    // ... 其他字段
} SYM;

// TAC 操作码
#define TAC_ADDR 25      // 取地址: a = &b
#define TAC_DEREF 26     // 解引用: a = *b
#define TAC_STORE 27     // 存储: *a = b
```

### 2.2 语法规则 (mini.y)

```yacc
// 指针声明
var_decl
    : '*' IDENTIFIER
    {
        $$.name = $2;
        $$.is_ptr = 1;
        $$.is_array = 0;
        $$.array_size = 0;
        $$.struct_tag = NULL;
    }
    ;

// 取地址
expression
    : '&' lvalue_expr
    {
        $$ = do_lvalue_addr($2);
    }
    ;

// 解引用
expression
    : '*' expression
    {
        if (!$2->ret->is_ptr) {
            error("dereference of non-pointer");
        }
        SYM *tmp = mk_tmp();
        tmp->data_type = $2->ret->data_type;
        tmp->is_ptr = 0;
        TAC *code = mk_tac(TAC_DEREF, tmp, $2->ret, NULL);
        code->prev = $2->tac;
        $$ = mk_exp(NULL, tmp, code);
    }
    ;

// 通过指针赋值
assignment_statement
    : '*' expression '=' expression
    {
        if (!$2->ret->is_ptr) error("assign to non-pointer");
        TAC *code = mk_tac(TAC_STORE, $2->ret, $4->ret, NULL);
        code->prev = join_tac($2->tac, $4->tac);
        $$ = code;
    }
    ;
```

### 2.3 取地址实现 (tac.c)

```c
// 左值取地址
EXP *do_lvalue_addr(LVALUE *lval) {
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    
    return mk_exp(NULL, addr_result->addr_sym, addr_result->code);
}
```

### 2.4 解引用实现 (tac.c - do_lvalue_access)

```c
EXP *do_lvalue_access(LVALUE *lval) {
    // 如果没有访问链，就是简单变量
    if (!lval->access_chain) {
        SYM *var = get_var(lval->base_name);
        return mk_exp(NULL, var, NULL);
    }
    
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    
    // 如果是指针，需要解引用获取指针值
    if (addr_result->type_info->is_ptr) {
        // 指针成员，需要解引用获取指针值
        SYM *ptr_value = mk_tmp();
        ptr_value->data_type = addr_result->type_info->data_type;
        ptr_value->is_ptr = 1; // 这是一个指针值
        
        TAC *deref_tac = mk_tac(TAC_DEREF, ptr_value, addr_result->addr_sym, NULL);
        deref_tac->prev = addr_result->code;
        
        return mk_exp(NULL, ptr_value, deref_tac);
    } else {
        // 普通成员，解引用
        SYM *value = mk_tmp();
        value->data_type = addr_result->type_info->data_type;
        value->struct_tag = addr_result->type_info->struct_tag;
        
        TAC *deref_tac = mk_tac(TAC_DEREF, value, addr_result->addr_sym, NULL);
        deref_tac->prev = addr_result->code;
        
        return mk_exp(NULL, value, deref_tac);
    }
}
```

### 2.5 通过指针赋值 (tac.c)

```c
// 左值赋值
TAC *do_lvalue_assign(LVALUE *lval, EXP *rval) {
    if (!lval->access_chain) {
        SYM *var = get_var(lval->base_name);
        if (var && var->data_type != TYPE_STRUCT && !var->is_array) {
            return do_assign(var, rval); // TAC_COPY
        }
    }
    
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    
    TAC *store_tac = mk_tac(TAC_STORE, addr_result->addr_sym, rval->ret, NULL);
    store_tac->prev = join_tac(addr_result->code, rval->tac);
    
    return store_tac;
}
```

### 2.6 代码生成 - 取地址 (obj.c)

```c
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
```

### 2.7 代码生成 - 解引用 (obj.c)

```c
case TAC_DEREF:
{
    int r_ptr = reg_alloc(c->b);
    int r_dst = get_free_register();
    /* Load value from pointer */
    out_str(file_s, "	LOD R%u,(R%u)\n", r_dst, r_ptr);
    rdesc_fill(r_dst, c->a, MODIFIED);
    return;
}
```

### 2.8 代码生成 - 通过指针存储 (obj.c)

```c
case TAC_STORE:
{
    int r_ptr = reg_alloc(c->a);  /* Get pointer register */
    
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
            r_val = (r_ptr == R_GEN) ? R_GEN + 1 : R_GEN;
            asm_write_back(r_val);
            rdesc_clear(r_val);
        }
        
        /* Load constant and store */
        out_str(file_s, "	LOD R%u,%d\n", r_val, c->b->value);
        out_str(file_s, "	STO (R%u),R%u\n", r_ptr, r_val);
        rdesc_clear(r_val);
    } else {
        /* Handle variable value */
        int r_val = reg_alloc(c->b);
        
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
            
            out_str(file_s, "	LOD R%u,R%u\n", new_reg, r_val);
            r_val = new_reg;
            rdesc_fill(r_val, c->b, UNMODIFIED);
        }

        /* Store value through pointer */
        out_str(file_s, "	STO (R%u),R%u\n", r_ptr, r_val);
    }
    return;
}
```

---

## 3. 结构体 (Struct)

### 3.1 数据结构定义 (tac.h)

```c
#define SYM_STRUCT_TAG 6
#define TYPE_STRUCT 3

typedef struct sym {
    int data_type;          // TYPE_INT, TYPE_CHAR, TYPE_STRUCT
    struct sym *struct_tag; // 结构体标签（当 data_type == TYPE_STRUCT 时）
    void *etc;              // 用于存储结构体成员列表（TAC* 链表）
    // ... 其他字段
} SYM;
```

### 3.2 语法规则 (mini.y)

```yacc
// 结构体声明
struct_decl
    : STRUCT IDENTIFIER '{' struct_member_list '}' ';'
    {
        SYM *tag = lookup_sym(sym_tab_global, $2);
        if (tag) {
            error("struct '%s' redefined", $2);
        }
        tag = mk_sym();
        tag->type = SYM_STRUCT_TAG;
        tag->name = $2;
        tag->etc = $4;
        insert_sym(&sym_tab_global, tag);
    }
    ;

struct_member_list
    : struct_member
    | struct_member_list struct_member
    { $$ = join_tac($1, $2); }
    ;

struct_member
    : type_specifier_value var_decl ';'
    {
        SYM *member_sym = mk_sym();
        member_sym->name = strdup($2.name);
        member_sym->type = SYM_VAR;
        member_sym->data_type = $1.type;
        member_sym->is_ptr = $2.is_ptr;
        member_sym->is_array = $2.is_array;
        member_sym->array_size = $2.array_size;
        member_sym->struct_tag = $1.struct_tag;
        
        SYM *type_sym = mk_sym();
        type_sym->type = ($1.type == TYPE_INT) ? SYM_INT : 
                        ($1.type == TYPE_CHAR) ? SYM_CHAR : SYM_STRUCT_TAG;
        
        TAC *member_tac = mk_tac(TAC_UNDEF, member_sym, type_sym, NULL);
        $$ = member_tac;
    }
    ;

// 结构体类型说明符
type_specifier_value
    : struct_specifier
    {
        $$.type = TYPE_STRUCT;
        $$.struct_tag = $1;
    }
    ;

struct_specifier
    : STRUCT IDENTIFIER
    {
        SYM *tag = lookup_sym(sym_tab_global, $2);
        if (!tag || tag->type != SYM_STRUCT_TAG) {
            error("undefined struct '%s'", $2);
        }
        $$ = tag;
    }
    ;

// 成员访问
access_item
    : '.' IDENTIFIER
    {
        $$ = mk_access_member($2);
    }
    ;
```

### 3.3 成员访问节点创建 (tac.c)

```c
// 创建成员访问节点
ACCESS_NODE *mk_access_member(char *name) {
    ACCESS_NODE *node = malloc(sizeof(ACCESS_NODE));
    node->type = ACCESS_MEMBER;
    node->member_name = strdup(name);
    node->next = NULL;
    return node;
}
```

### 3.4 成员偏移计算 (tac.c)

```c
int calculate_member_offset(SYM *struct_tag, char *member_name, TAC **found_member) {
    int offset = 0;
    *found_member = NULL;

    if (!struct_tag || !struct_tag->etc) {
        return -1;
    }

    // 遍历成员列表
    for (TAC *p = (TAC*)struct_tag->etc; p; p = p->prev) {
        if (!p->a || !p->a->name) {
            offset += 4;
            continue;
        }

        // 如果匹配
        if (strcmp(p->a->name, member_name) == 0) {
            *found_member = p;
            return offset;
        }

        // 计算当前成员的大小
        int member_size = 4; // 默认大小
        
        if (p->a->is_ptr) {
            member_size = 4;
        } else if (p->a->is_array) {
            if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                int element_size = calculate_struct_size(p->a->struct_tag);
                member_size = p->a->array_size * element_size;
            } else {
                member_size = p->a->array_size * 4;
            }
        } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
            member_size = calculate_struct_size(p->a->struct_tag);
        } else {
            member_size = 4;
        }
        
        offset += member_size;
    }

    return -1;
}
```

### 3.5 结构体大小计算 (tac.c)

```c
int calculate_struct_size(SYM *struct_tag)
{
    int total_size = 0;
    
    if (!struct_tag || !struct_tag->etc) {
        return 4; // 默认大小
    }
    
    for (TAC *p = (TAC*)struct_tag->etc; p; p = p->prev) {
        if (!p->a) {
            total_size += 4;
            continue;
        }
        
        int member_size = 4; // 默认大小
        
        if (p->a->is_ptr) {
            member_size = 4; // 指针大小
        } else if (p->a->is_array) {
            if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                int element_size = calculate_struct_size(p->a->struct_tag);
                member_size = p->a->array_size * element_size;
            } else {
                member_size = p->a->array_size * 4;
            }
        } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
            if (p->a->struct_tag != struct_tag) { // 防止自引用
                member_size = calculate_struct_size(p->a->struct_tag);
            } else {
                member_size = 4; // 自引用时使用默认大小
            }
        } else {
            member_size = 4; // int/char 都按 4 字节
        }
        
        total_size += member_size;
    }
    
    return total_size;
}
```

### 3.6 成员访问地址计算 (tac.c - calculate_lvalue_address)

```c
case ACCESS_MEMBER: {
    // 成员访问：current_addr + member_offset
    if (current_data_type != TYPE_STRUCT || !current_type) {
        error("member access on non-struct type");
        return NULL;
    }
    
    TAC *member_info = NULL;
    int offset = calculate_member_offset(current_type, node->member_name, &member_info);
    if (offset < 0) {
        error("no member '%s' in struct", node->member_name);
        return NULL;
    }
    
    SYM *new_addr = mk_tmp();
    new_addr->is_ptr = 1;
    TAC *add_tac = mk_tac(TAC_ADD, new_addr, current_addr, mk_const(offset));
    add_tac->prev = code;
    code = add_tac;
    current_addr = new_addr;
    
    // 更新类型信息
    current_data_type = member_info->a->data_type;
    current_type = member_info->a->struct_tag;
    current_is_array = member_info->a->is_array;
    current_array_size = member_info->a->array_size;
    current_is_ptr = member_info->a->is_ptr;
    break;
}
```

### 3.7 代码生成 - 结构体变量内存分配 (obj.c)

```c
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
    } else {
        c->a->offset = tos;
        tos += size;
    }
    break;
}
```

---

## 4. For循环

### 4.1 数据结构定义 (tac.h)

```c
// 循环上下文结构
typedef struct loop_context {
    SYM *break_label;      /* break 跳转目标 */
    SYM *continue_label;   /* continue 跳转目标（循环开始） */
} LOOP_CONTEXT;

extern LOOP_CONTEXT *loop_stack;   // 循环上下文栈
extern int loop_sp;                // 循环栈指针
extern int loop_stack_size;
```

### 4.2 语法规则 (mini.y)

```yacc
// For循环语法
for_statement : FOR '(' assignment_statement ';' expression ';' assignment_statement ')' for_start block for_end
{
    $$ = do_for_with_context($3, $5, $7, $10, $9, $11);
}
;

// For循环开始（创建上下文）
for_start : /* empty */
{
    $$ = mk_label(mk_lstr(next_label++));
    // 创建一个临时的 continue 标签（占位符，稍后会被更新）
    SYM *temp_continue = mk_label(mk_lstr(next_label++));
    push_loop_context($$, temp_continue);
}
;

// For循环结束（清理上下文）
for_end : /* empty */
{
    pop_break_label();
    $$ = NULL;
}
;
```

### 4.3 循环上下文管理 (tac.c)

```c
// 初始化循环栈
void tac_init()
{
    scope = 0;
    sym_tab_global = NULL;
    sym_tab_local = NULL;
    next_tmp = 0;
    next_label = 1;
    // 初始化循环上下文栈
    loop_sp = 0;
    loop_stack_size = 0;
    free(loop_stack);
    loop_stack = NULL;
}

// 推送循环上下文（同时设置 break 和 continue 标签）
void push_loop_context(SYM *break_label, SYM *continue_label) {
    if (loop_sp >= loop_stack_size) {
        loop_stack_size = loop_stack_size ? loop_stack_size * 2 : 8;
        loop_stack = realloc(loop_stack, loop_stack_size * sizeof(LOOP_CONTEXT));
    }
    loop_stack[loop_sp].break_label = break_label;
    loop_stack[loop_sp].continue_label = continue_label;
    loop_sp++;
}

// 弹出循环上下文
void pop_break_label() {
    if (loop_sp <= 0) {
        error("break/continue not inside loop or switch");
        exit(1);
    }
    loop_sp--;
}

// 获取当前 break 标签
SYM *peek_break_label() {
    if (loop_sp <= 0) {
        error("break not inside loop or switch");
        return NULL;
    }
    return loop_stack[loop_sp - 1].break_label;
}

// 获取当前 continue 标签
SYM *peek_continue_label() {
    if (loop_sp <= 0) {
        error("continue not inside loop");
        return NULL;
    }
    return loop_stack[loop_sp - 1].continue_label;
}

// 更新栈顶的 continue 标签
void update_continue_label(SYM *new_continue_label) {
    if (loop_sp <= 0) {
        error("update_continue_label: not inside loop");
        return;
    }
    loop_stack[loop_sp - 1].continue_label = new_continue_label;
}

// 替换 TAC 链中所有使用 old_label 的 GOTO 为 new_label
void replace_label_in_tac(TAC *tac, SYM *old_label, SYM *new_label) {
    if (tac == NULL) return;
    
    // 找到链表的头部（prev 为 NULL 的节点）
    TAC *head = tac;
    while (head->prev != NULL) {
        head = head->prev;
    }
    
    // 从头部开始遍历整个链表
    for (TAC *p = head; p != NULL; p = p->next) {
        if (p->op == TAC_GOTO && p->a == old_label) {
            p->a = new_label;
        }
    }
}
```

### 4.4 For循环代码生成 (tac.c)

```c
TAC *do_for_with_context(TAC *init, EXP *cond, TAC *incr, TAC *body, SYM *end_label, TAC *dummy) {
    SYM *begin_label = mk_label(mk_lstr(next_label++));
    SYM *continue_label = mk_label(mk_lstr(next_label++));  // continue 跳转到递增部分

    // for_start 已经 push 了上下文（break=end_label, continue=临时标签）
    // body 已经解析完了，body 中的 continue 使用的是临时标签
    // 我们需要找到所有使用临时标签的 GOTO，并替换为 continue_label
    SYM *old_continue_label = NULL;
    if (loop_sp > 0) {
        old_continue_label = loop_stack[loop_sp - 1].continue_label;
        update_continue_label(continue_label);
        // 替换 body 中所有使用临时标签的 GOTO
        if (old_continue_label != continue_label && body != NULL) {
            replace_label_in_tac(body, old_continue_label, continue_label);
        }
    } else {
        // 如果栈为空，说明 for_end 已经执行了，我们需要重新 push
        push_loop_context(end_label, continue_label);
    }

    // 循环开始标签
    TAC *label_begin = mk_tac(TAC_LABEL, begin_label, NULL, NULL);

    // 条件判断（如果有）
    TAC *cond_check = NULL;
    if (cond) {
        cond_check = mk_tac(TAC_IFZ, end_label, cond->ret, NULL);
        cond_check->prev = cond->tac;
    }

    // continue 标签（递增部分开始）
    TAC *label_continue = mk_tac(TAC_LABEL, continue_label, NULL, NULL);

    // 循环体 + 递增 + 跳回开始
    TAC *loop_core = join_tac(body, label_continue);  // body 后是 continue 标签
    loop_core = join_tac(loop_core, incr);  // 然后是递增部分
    loop_core = join_tac(loop_core, mk_tac(TAC_GOTO, begin_label, NULL, NULL));  // 跳回开始

    // 拼接循环体
    TAC *loop = label_begin;
    if (cond) {
        loop = join_tac(loop, cond_check);
        loop = join_tac(loop, loop_core);
    } else {
        // 无条件循环（for(;;)）
        loop = join_tac(loop, body);
        loop = join_tac(loop, label_continue);
        loop = join_tac(loop, incr);
        loop = join_tac(loop, mk_tac(TAC_GOTO, begin_label, NULL, NULL));
    }

    // 结束标签（由外部传入，用于 break）
    TAC *label_end = mk_tac(TAC_LABEL, end_label, NULL, NULL);
    loop = join_tac(loop, label_end);

    return join_tac(init, loop);
}
```

### 4.5 For循环结构说明

For循环生成的代码结构：
```
init_code
L_begin:
  if (!cond) goto L_end;
  body_code
L_continue:
  incr_code
  goto L_begin;
L_end:
```

