#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "tac.h"

/* global var */
int scope, next_tmp, next_label;
SYM *sym_tab_global, *sym_tab_local;
TAC *tac_first, *tac_last;
LOOP_CONTEXT *loop_stack = NULL;
int loop_sp = 0;
int loop_stack_size = 0;

// 创建访问节点
ACCESS_NODE *mk_access_member(char *name) {
    ACCESS_NODE *node = malloc(sizeof(ACCESS_NODE));
    node->type = ACCESS_MEMBER;
    node->member_name = strdup(name);
    node->next = NULL;
    return node;
}

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

// 创建左值
LVALUE *mk_lvalue(char *base_name, ACCESS_NODE *access_chain) {
    LVALUE *lval = malloc(sizeof(LVALUE));
    lval->base_name = strdup(base_name);
    lval->access_chain = access_chain;
    return lval;
}


ADDR_RESULT *calculate_lvalue_address(LVALUE *lval) {
    SYM *base_var = get_var(lval->base_name);
    if (!base_var) {
        error("undefined variable '%s'", lval->base_name);
        return NULL;
    }
    
    ADDR_RESULT *result = malloc(sizeof(ADDR_RESULT));
    
    // 初始地址：基础变量的地址
    SYM *current_addr = mk_tmp();
    current_addr->is_ptr = 1;
    TAC *code = mk_tac(TAC_ADDR, current_addr, base_var, NULL);
    int step = 1;
    // 当前类型信息
    SYM *current_type = base_var->struct_tag;
    int current_data_type = base_var->data_type;
    int current_is_array = base_var->is_array;
    int current_array_size = base_var->array_size;
    int current_is_ptr = base_var->is_ptr;  // 添加这一行
    
    // 遍历访问链
    ACCESS_NODE *node = lval->access_chain;
    while (node) {
        switch (node->type) {
            case ACCESS_MEMBER: {
				                printf("Step %d: member access '.%s'\n", step, node->member_name);
                printf("  current_type: %s\n", current_type ? current_type->name : "NULL");
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
                printf("  found offset: %d\n", offset);
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
                current_is_ptr = member_info->a->is_ptr;  // 添加这一行
                break;
            }
            
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
				                 printf("Step %d: array access [%s]\n", step, 
                       node->index_exp->ret ? node->index_exp->ret->name : "?");
                printf("  element_size: %d\n", element_size);
                break;
            }
        }
        node = node->next;
		step++;
    }
    
    result->addr_sym = current_addr;
    result->code = code;
    
    // 创建类型信息符号
    result->type_info = mk_sym();
    result->type_info->data_type = current_data_type;
    result->type_info->struct_tag = current_type;
    result->type_info->is_array = current_is_array;
    result->type_info->array_size = current_array_size;
    result->type_info->is_ptr = current_is_ptr;  // 添加这一行
    
    return result;
}


// 左值访问（读取）
// 左值访问（读取）
EXP *do_lvalue_access(LVALUE *lval) {
    // 如果没有访问链，就是简单变量
    if (!lval->access_chain) {
        SYM *var = get_var(lval->base_name);
        return mk_exp(NULL, var, NULL);
    }
    
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    
    // 如果是数组，返回地址；如果是指针，也返回地址；否则解引用
    if (addr_result->type_info->is_array) {
        return mk_exp(NULL, addr_result->addr_sym, addr_result->code);
    } else if (addr_result->type_info->is_ptr) {
        fprintf(stderr, "DEBUG: Accessing pointer member %s\n", lval->base_name);
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


// 左值赋值
TAC *do_lvalue_assign(LVALUE *lval, EXP *rval) {
	    if (!lval->access_chain) {
        SYM *var = get_var(lval->base_name);
        if (var && var->data_type != TYPE_STRUCT && !var->is_array) {
            fprintf(stderr, "DEBUG: Simple assignment to variable %s\n", var->name);
            return do_assign(var, rval); // TAC_COPY
        }
    }
    fprintf(stderr, "DEBUG: Pointer assignment to %s\n", lval->base_name);
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    fprintf(stderr, "DEBUG: Storing value through pointer at offset %d\n", 
            addr_result->addr_sym->offset);
    
    TAC *store_tac = mk_tac(TAC_STORE, addr_result->addr_sym, rval->ret, NULL);
    store_tac->prev = join_tac(addr_result->code, rval->tac);
    
    return store_tac;
}

// 左值取地址
EXP *do_lvalue_addr(LVALUE *lval) {
    ADDR_RESULT *addr_result = calculate_lvalue_address(lval);
    if (!addr_result) return NULL;
    
    return mk_exp(NULL, addr_result->addr_sym, addr_result->code);
}


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

/* 推送循环上下文（同时设置 break 和 continue 标签） */
void push_loop_context(SYM *break_label, SYM *continue_label) {
    if (loop_sp >= loop_stack_size) {
        loop_stack_size = loop_stack_size ? loop_stack_size * 2 : 8;
        loop_stack = realloc(loop_stack, loop_stack_size * sizeof(LOOP_CONTEXT));
    }
    loop_stack[loop_sp].break_label = break_label;
    loop_stack[loop_sp].continue_label = continue_label;
    loop_sp++;
}

/* 推送 switch 上下文（只有 break，continue 等同于 break） */
void push_break_label(SYM *label) {
    push_loop_context(label, label);  /* switch 中 continue = break */
}

void pop_break_label() {
    if (loop_sp <= 0) {
        error("break/continue not inside loop or switch");
        exit(1);
    }
    loop_sp--;
}

SYM *peek_break_label() {
    if (loop_sp <= 0) {
        error("break not inside loop or switch");
        return NULL;
    }
    return loop_stack[loop_sp - 1].break_label;
}

SYM *peek_continue_label() {
    if (loop_sp <= 0) {
        error("continue not inside loop");
        return NULL;
    }
    return loop_stack[loop_sp - 1].continue_label;
}

/* 更新栈顶的 continue 标签 */
void update_continue_label(SYM *new_continue_label) {
    if (loop_sp <= 0) {
        error("update_continue_label: not inside loop");
        return;
    }
    loop_stack[loop_sp - 1].continue_label = new_continue_label;
}

/* 替换 TAC 链中所有使用 old_label 的 GOTO 为 new_label */
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

void tac_complete()
{
	TAC *cur=NULL; 		/* Current TAC */
	TAC *prev=tac_last; 	/* Previous TAC */

	while(prev !=NULL)
	{
		prev->next=cur;
		cur=prev;
		prev=prev->prev;
	}

	tac_first = cur;
}

SYM *lookup_sym(SYM *symtab, char *name)
{
	SYM *t=symtab;

	while(t !=NULL)
	{
		if(strcmp(t->name, name)==0) break; 
		else t=t->next;
	}
	
	return t; /* NULL if not found */
}

void insert_sym(SYM **symtab, SYM *sym)
{
	sym->next=*symtab; /* Insert at head */
	*symtab=sym;
}

SYM *mk_sym(void) {
    SYM *t = (SYM *)calloc(1, sizeof(SYM)); // ← 用 calloc 自动清零
    return t;
}

SYM *mk_var(char *name)
{
	SYM *sym=NULL;

	if(scope)  
		sym=lookup_sym(sym_tab_local,name);
	else
		sym=lookup_sym(sym_tab_global,name);

	/* var already declared */
	if(sym!=NULL)
	{
		error("variable already declared");
		return NULL;
	}

	/* var unseen before, set up a new symbol table node, insert_sym it into the symbol table. */
	sym=mk_sym();
	sym->type=SYM_VAR;
	sym->name=name;
	sym->scope=scope;
	sym->offset=-1; /* Unset address */

	if(scope)  
		insert_sym(&sym_tab_local,sym);
	else
		insert_sym(&sym_tab_global,sym);

	return sym;
}

TAC *join_tac(TAC *c1, TAC *c2)
{
	TAC *t;

	if(c1==NULL) return c2;
	if(c2==NULL) return c1;

	/* Run down c2, until we get to the beginning and then add c1 */
	t=c2;
	while(t->prev !=NULL) 
		t=t->prev;

	t->prev=c1;
	return c2;
}
int calculate_member_offset(SYM *struct_tag, char *member_name, TAC **found_member) {
    printf(">>> calculate_member_offset: looking for '%s' in struct '%s'\n", 
           member_name, struct_tag ? struct_tag->name : "NULL");
    
    int offset = 0;
    *found_member = NULL;

    if (!struct_tag || !struct_tag->etc) {
        printf(">>> struct_tag or etc is NULL\n");
        return -1;
    }

    // 遍历成员列表
    for (TAC *p = (TAC*)struct_tag->etc; p; p = p->prev) {
        if (!p->a || !p->a->name) {
            printf(">>> unnamed member, offset += 4 (now %d)\n", offset + 4);
            offset += 4;
            continue;
        }

        printf(">>> checking member '%s' at offset %d\n", p->a->name, offset);

        // 如果匹配
        if (strcmp(p->a->name, member_name) == 0) {
            printf(">>> FOUND '%s' at offset %d\n", member_name, offset);
            *found_member = p;
            return offset;
        }

        // 计算当前成员的大小 - 这里是关键修复！
        int member_size = 4; // 默认大小
        
        if (p->a->is_ptr) {
            member_size = 4;
            printf(">>> '%s' is pointer, size=4\n", p->a->name);
        } else if (p->a->is_array) {
            if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                // 结构体数组：需要计算结构体大小
                int element_size = calculate_struct_size(p->a->struct_tag);
                member_size = p->a->array_size * element_size;
                printf(">>> '%s' is struct array[%d], element_size=%d, total_size=%d\n", 
                       p->a->name, p->a->array_size, element_size, member_size);
            } else {
                // 普通数组（int/char）
                member_size = p->a->array_size * 4;
                printf(">>> '%s' is array[%d], size=%d\n", 
                       p->a->name, p->a->array_size, member_size);
            }
        } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
            // 嵌套结构体（非数组）
            member_size = calculate_struct_size(p->a->struct_tag);
            printf(">>> '%s' is struct, size=%d\n", p->a->name, member_size);
        } else {
            // 普通类型
            printf(">>> '%s' is regular type, size=4\n", p->a->name);
        }
        
        offset += member_size;
        printf(">>> after '%s', offset becomes %d\n", p->a->name, offset);
    }

    printf(">>> Member '%s' NOT FOUND in struct '%s'\n", member_name, struct_tag->name);
    return -1;
}

// 计算结构体大小的函数
// 在 tac.c 中添加这个函数
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
                // 结构体数组：元素个数 * 结构体大小
                int element_size = calculate_struct_size(p->a->struct_tag);
                member_size = p->a->array_size * element_size;
            } else {
                // 普通数组
                member_size = p->a->array_size * 4;
            }
        } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
            // 嵌套结构体
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



TAC *declare_var(char *name)
{
	return mk_tac(TAC_VAR,mk_var(name),NULL,NULL);
}

TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c)
{
	TAC *t=(TAC *)malloc(sizeof(TAC));

	t->next=NULL; /* Set these for safety */
	t->prev=NULL;
	t->op=op;
	t->a=a;
	t->b=b;
	t->c=c;
	t->etc=NULL;  // 初始化 etc 字段

	return t;
}  

SYM *mk_label(char *name)
{
	SYM *t=mk_sym();

	t->type=SYM_LABEL;
	t->name=strdup(name);

	return t;
}  

TAC *do_func(SYM *func, TAC *args, TAC *code)
{
	TAC *tlist; /* The backpatch list */

	TAC *tlab; /* Label at start of function */
	TAC *tbegin; /* BEGINFUNC marker */
	TAC *tend; /* ENDFUNC marker */

	tlab=mk_tac(TAC_LABEL, mk_label(func->name), NULL, NULL);
	tbegin=mk_tac(TAC_BEGINFUNC, NULL, NULL, NULL);
	tend=mk_tac(TAC_ENDFUNC,   NULL, NULL, NULL);

	tbegin->prev=tlab;
	code=join_tac(args, code);
	tend->prev=join_tac(tbegin, code);

	return tend;
}

SYM *mk_tmp(void)
{
	SYM *sym;
	char *name;
	name=malloc(12);
	sprintf(name, "t%d", next_tmp++);
	sym = mk_var(name);
	sym->offset = -1; 
	return sym;
}

TAC *declare_para(char *name)
{
	return mk_tac(TAC_FORMAL,mk_var(name),NULL,NULL);
}

SYM *declare_func(char *name)
{
	SYM *sym=NULL;

	sym=lookup_sym(sym_tab_global,name);

	/* name used before declared */
	if(sym!=NULL)
	{
		if(sym->type==SYM_FUNC)
		{
			error("func already declared");
			return NULL;
		}

		if(sym->type !=SYM_UNDEF)
		{
			error("func name already used");
			return NULL;
		}

		return sym;
	}
	
	
	sym=mk_sym();
	sym->type=SYM_FUNC;
	sym->name=name;
	sym->address=NULL;

	insert_sym(&sym_tab_global,sym);
	return sym;
}

// 添加 get_func 函数
SYM *get_func(char *name)
{
    SYM *sym = lookup_sym(sym_tab_global, name);
    
    if (sym == NULL) {
        error("undefined function '%s'", name);
        return NULL;
    }
    
    if (sym->type != SYM_FUNC) {
        error("'%s' is not a function", name);
        return NULL;
    }
    
    return sym;
}

TAC *do_assign(SYM *var, EXP *exp)
{
	TAC *code;

	if(var->type !=SYM_VAR) error("assignment to non-variable");

	code=mk_tac(TAC_COPY, var, exp->ret, NULL);
	code->prev=exp->tac;

	return code;
}

TAC *do_input(SYM *var)
{
	TAC *code;

	if(var->type !=SYM_VAR) error("input to non-variable");

	code=mk_tac(TAC_INPUT, var, NULL, NULL);

	return code;
}

TAC *do_output(SYM *s)
{
	TAC *code;

	code=mk_tac(TAC_OUTPUT, s, NULL, NULL);

	return code;
}

EXP *do_bin( int binop, EXP *exp1, EXP *exp2)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev=join_tac(exp1->tac, exp2->tac);
	ret=mk_tac(binop, temp->a, exp1->ret, exp2->ret);
	ret->prev=temp;

	exp1->ret=temp->a;
	exp1->tac=ret;

	return exp1;  
}   

EXP *do_cmp( int binop, EXP *exp1, EXP *exp2)
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev=join_tac(exp1->tac, exp2->tac);
	ret=mk_tac(binop, temp->a, exp1->ret, exp2->ret);
	ret->prev=temp;

	exp1->ret=temp->a;
	exp1->tac=ret;

	return exp1;  
}   

EXP *do_un( int unop, EXP *exp) 
{
	TAC *temp; /* TAC code for temp symbol */
	TAC *ret; /* TAC code for result */

	temp=mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
	temp->prev=exp->tac;
	ret=mk_tac(unop, temp->a, exp->ret, NULL);
	ret->prev=temp;

	exp->ret=temp->a;
	exp->tac=ret;

	return exp;   
}

// 修改 do_call 函数
TAC *do_call(char *name, EXP *arglist)
{
    EXP  *alt; /* For counting args */
    TAC *code; /* Resulting code */
    TAC *temp; /* Temporary for building code */

    // 查找函数符号
    SYM *func = get_func(name);
    if (!func) return NULL;

    code=NULL;
    for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(code, alt->tac);

    while(arglist !=NULL) /* Generate ARG instructions */
    {
        temp=mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
        temp->prev=code;
        code=temp;

        alt=arglist->next;
        arglist=alt;
    };

    // 修改：存储 SYM 指针而不是字符串
    temp=mk_tac(TAC_CALL, NULL, func, NULL);
    temp->prev=code;
    code=temp;

    return code;
}

// 修改 do_call_ret 函数
EXP *do_call_ret(char *name, EXP *arglist)
{
    EXP  *alt; /* For counting args */
    SYM *ret; /* Where function result will go */
    TAC *code; /* Resulting code */
    TAC *temp; /* Temporary for building code */

    // 查找函数符号
    SYM *func = get_func(name);
    if (!func) return mk_exp(NULL, NULL, NULL);

    ret=mk_tmp(); /* For the result */
    code=mk_tac(TAC_VAR, ret, NULL, NULL);

    for(alt=arglist; alt !=NULL; alt=alt->next) code=join_tac(code, alt->tac);

    while(arglist !=NULL) /* Generate ARG instructions */
    {
        temp=mk_tac(TAC_ACTUAL, arglist->ret, NULL, NULL);
        temp->prev=code;
        code=temp;

        alt=arglist->next;
        arglist=alt;
    };

    // 修改：存储 SYM 指针而不是字符串
    temp=mk_tac(TAC_CALL, ret, func, NULL);
    temp->prev=code;
    code=temp;

    return mk_exp(NULL, ret, code);
}

char *mk_lstr(int i)
{
	char lstr[10]="L";
	sprintf(lstr,"L%d",i);
	return(strdup(lstr));	
}

TAC *do_if(EXP *exp, TAC *stmt)
{
	TAC *label=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *code=mk_tac(TAC_IFZ, label->a, exp->ret, NULL);

	code->prev=exp->tac;
	code=join_tac(code, stmt);
	label->prev=code;

	return label;
}

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

TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2)
{
	TAC *label1=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *label2=mk_tac(TAC_LABEL, mk_label(mk_lstr(next_label++)), NULL, NULL);
	TAC *code1=mk_tac(TAC_IFZ, label1->a, exp->ret, NULL);
	TAC *code2=mk_tac(TAC_GOTO, label2->a, NULL, NULL);

	code1->prev=exp->tac; /* Join the code */
	code1=join_tac(code1, stmt1);
	code2->prev=code1;
	label1->prev=code2;
	label1=join_tac(label1, stmt2);
	label2->prev=label1;
	
	return label2;
}

TAC *do_case(int value, TAC *stmts)
{
    SYM *lab = mk_label(mk_lstr(next_label++));
    TAC *node = mk_tac(TAC_LABEL, lab, mk_const(value), NULL);
    node->etc = (void*)stmts;   /* 不与语句块立即拼接，先存放在 etc */
    return node;                /* 仅返回占位节点，供 do_switch 统一生成 */
}

/* default 占位节点：op=TAC_LABEL, a=default标签, b=NULL, etc=default 语句块 */
TAC *do_default(TAC *stmts)
{
    SYM *lab = mk_label(mk_lstr(next_label++));
    TAC *node = mk_tac(TAC_LABEL, lab, NULL, NULL);
    node->etc = (void*)stmts;
    return node;
}

TAC *do_switch_with_context(EXP *exp, TAC *cases, TAC *def, SYM *end_label, TAC *dummy) {
    // 1) 收集 case 节点（和原来一样）
    int n = 0;
    for (TAC *t = cases; t != NULL; t = t->prev) n++;

    TAC **arr = NULL;
    if (n > 0) {
        arr = (TAC**)malloc(sizeof(TAC*) * n);
        int i = n - 1;
        for (TAC *t = cases; t != NULL; t = t->prev) arr[i--] = t;
        for (int k = 0; k < n; ++k) arr[k]->prev = NULL;
    }

    // 2) default 处理
    SYM *default_label = NULL;
    TAC *default_block = NULL;
    if (def) {
        def->prev = NULL;
        default_label = def->a;
        default_block = (TAC*)def->etc;
    } else {
        default_label = end_label; // 无 default 时跳到 end
    }

    // 3) 生成判别链：if (exp == case_val) goto Lcase
    TAC *conds = NULL;
    for (int i = 0; i < n; ++i) {
        TAC *tvar = mk_tac(TAC_VAR, mk_tmp(), NULL, NULL);
        TAC *tcmp = mk_tac(TAC_NE, tvar->a, exp->ret, arr[i]->b); // tmp = (exp != val)
        tcmp->prev = tvar;
        TAC *tifz = mk_tac(TAC_IFZ, arr[i]->a, tvar->a, NULL);     // ifz tmp goto Lcase_i
        tifz->prev = tcmp;
        conds = join_tac(conds, tifz);
    }
    // 都不匹配 → default 或 end
    TAC *tg = mk_tac(TAC_GOTO, default_label, NULL, NULL);
    conds = join_tac(conds, tg);

    // 4) 入口：表达式求值 + 判别
    TAC *code = join_tac(exp->tac, conds);

    // 5) 拼接所有 case 块（顺序贯穿）
    for (int i = 0; i < n; ++i) {
        code = join_tac(code, arr[i]);
        if (arr[i]->etc) code = join_tac(code, (TAC*)arr[i]->etc);
    }

    // 6) default 块（若有）
    if (def) {
        code = join_tac(code, def);
        if (default_block) code = join_tac(code, default_block);
    }

    // 7) 结束标签（由外部传入，用于 break）
    code = join_tac(code, mk_tac(TAC_LABEL, end_label, NULL, NULL));

    if (arr) free(arr);
    return code;
}

TAC *do_while_with_context(EXP *exp, TAC *body, SYM *end_label, TAC *dummy) {
    SYM *begin_label = mk_label(mk_lstr(next_label++));

    // loop_start 已经 push 了上下文（break=end_label, continue=临时标签）
    // body 已经解析完了，body 中的 continue 使用的是临时标签
    // 我们需要找到所有使用临时标签的 GOTO，并替换为 begin_label
    SYM *old_continue_label = NULL;
    if (loop_sp > 0) {
        old_continue_label = loop_stack[loop_sp - 1].continue_label;
        update_continue_label(begin_label);
        // 替换 body 中所有使用临时标签的 GOTO
        if (old_continue_label != begin_label && body != NULL) {
            replace_label_in_tac(body, old_continue_label, begin_label);
        }
    } else {
        // 如果栈为空，说明 loop_end 已经执行了，我们需要重新 push
        push_loop_context(end_label, begin_label);
    }

    TAC *label_begin = mk_tac(TAC_LABEL, begin_label, NULL, NULL);
    TAC *cond_check = mk_tac(TAC_IFZ, end_label, exp->ret, NULL);
    cond_check->prev = exp->tac;

    TAC *goto_begin = mk_tac(TAC_GOTO, begin_label, NULL, NULL);
    TAC *label_end = mk_tac(TAC_LABEL, end_label, NULL, NULL);

    TAC *loop = join_tac(cond_check, body);
    loop = join_tac(loop, goto_begin);
    loop = join_tac(loop, label_end);

    return join_tac(label_begin, loop);
}

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
	sym->data_type = data_type;
    sym->struct_tag = struct_tag; 
    if (scope)
        insert_sym(&sym_tab_local, sym);
    else
        insert_sym(&sym_tab_global, sym);

    // 分配空间：数组按元素个数 * 4 字节（假设 int/char 都占 4 字节，简化处理）
    int size = is_array ? array_size * 4 : 4;
    TAC *t = mk_tac(TAC_VAR, sym, NULL, NULL);
    // 在 TAC_VAR 中不直接体现 size，由 obj.c 根据 sym->is_array 和 array_size 处理
    return t;
}

SYM *mk_char_const(char c) {
    // 用字符串 "'a'" 作为名字避免冲突
    char name[4];
    sprintf(name, "'%c'", c);

    SYM *sym = lookup_sym(sym_tab_global, name);
    if (sym) return sym;

    sym = mk_sym();
    sym->type = SYM_INT;        // 复用整数常量
    sym->data_type = TYPE_CHAR; // 但标记为 char 类型
    sym->value = (unsigned char)c;
    sym->name = strdup(name);
    insert_sym(&sym_tab_global, sym);
    return sym;
}

TAC *do_break() {
    SYM *target = peek_break_label();  // 获取当前 break 目标
    return mk_tac(TAC_GOTO, target, NULL, NULL);
}

TAC *do_continue() {
    SYM *target = peek_continue_label();  // 获取当前 continue 目标（循环开始）
    return mk_tac(TAC_GOTO, target, NULL, NULL);
}

SYM *get_var(char *name)
{
	SYM *sym=NULL; /* Pointer to looked up symbol */

	if(scope) sym=lookup_sym(sym_tab_local,name);

	if(sym==NULL) sym=lookup_sym(sym_tab_global,name);

	if(sym==NULL)
	{
		error("name not declared as local/global variable");
		return NULL;
	}

	if(sym->type!=SYM_VAR)
	{
		error("not a variable");
		return NULL;
	}

	return sym;
} 

EXP *mk_exp(EXP *next, SYM *ret, TAC *code)
{
	EXP *exp=(EXP *)malloc(sizeof(EXP));

	exp->next=next;
	exp->ret=ret;
	exp->tac=code;

	return exp;
}

SYM *mk_text(char *text)
{
	SYM *sym=NULL; /* Pointer to looked up symbol */

	sym=lookup_sym(sym_tab_global,text);

	/* text already used */
	if(sym!=NULL)
	{
		return sym;
	}

	/* text unseen before */
	sym=mk_sym();
	sym->type=SYM_TEXT;
	sym->name=text;
	sym->label=next_label++;

	insert_sym(&sym_tab_global,sym);
	return sym;
}

SYM *mk_const(int n)
{
	SYM *sym=NULL;

	char name[10];
	sprintf(name, "%d", n);

	sym=lookup_sym(sym_tab_global, name);
	if(sym!=NULL)
	{
		return sym;
	}

	sym=mk_sym();
	sym->type=SYM_INT;
	sym->value=n;
	sym->name=strdup(name);
	insert_sym(&sym_tab_global,sym);

	return sym;
}     

char *to_str(SYM *s, char *str) 
{
	if(s==NULL)	return "NULL";

	switch(s->type)
	{
		case SYM_FUNC:
		case SYM_VAR:
		/* Just return the name */
		return s->name;

		case SYM_TEXT:
		/* Put the address of the text */
		sprintf(str, "L%d", s->label);
		return str;

		case SYM_INT:
		/* Convert the number to string */
		sprintf(str, "%d", s->value);
		return str;

		default:
		/* Unknown arg type */
		error("unknown TAC arg type");
		return "?";
	}
} 

void out_str(FILE *f, const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(f, format, args);
    va_end(args);
}

void out_sym(FILE *f, SYM *s)
{
	out_str(f, "%p\t%s", s, s->name);
}

void out_tac(FILE *f, TAC *i)
{
	char sa[12]; /* For text of TAC args */
	char sb[12];
	char sc[12];

	switch(i->op)
	{
		case TAC_UNDEF:
		fprintf(f, "undef");
		break;

		case TAC_ADD:
		fprintf(f, "%s = %s + %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_SUB:
		fprintf(f, "%s = %s - %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_MUL:
		fprintf(f, "%s = %s * %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_DIV:
		fprintf(f, "%s = %s / %s", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_EQ:
		fprintf(f, "%s = (%s == %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_NE:
		fprintf(f, "%s = (%s != %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_LT:
		fprintf(f, "%s = (%s < %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_LE:
		fprintf(f, "%s = (%s <= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_GT:
		fprintf(f, "%s = (%s > %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_GE:
		fprintf(f, "%s = (%s >= %s)", to_str(i->a, sa), to_str(i->b, sb), to_str(i->c, sc));
		break;

		case TAC_NEG:
		fprintf(f, "%s = - %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_COPY:
		fprintf(f, "%s = %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_GOTO:
		fprintf(f, "goto %s", i->a->name);
		break;

		case TAC_IFZ:
		fprintf(f, "ifz %s goto %s", to_str(i->b, sb), i->a->name);
		break;

		case TAC_ACTUAL:
		fprintf(f, "actual %s", to_str(i->a, sa));
		break;

		case TAC_FORMAL:
		fprintf(f, "formal %s", to_str(i->a, sa));
		break;

		case TAC_CALL:
		// 修改：使用 i->b->name 而不是 (char *)i->b
		if(i->a==NULL) fprintf(f, "call %s", i->b->name);
		else fprintf(f, "%s = call %s", to_str(i->a, sa), i->b->name);
		break;

		case TAC_INPUT:
		fprintf(f, "input %s", to_str(i->a, sa));
		break;

		case TAC_OUTPUT:
		fprintf(f, "output %s", to_str(i->a, sa));
		break;

		case TAC_RETURN:
		fprintf(f, "return %s", to_str(i->a, sa));
		break;

		case TAC_LABEL:
		fprintf(f, "label %s", i->a->name);
		break;

		case TAC_VAR:
		fprintf(f, "var %s", to_str(i->a, sa));
		break;

		case TAC_BEGINFUNC:
		fprintf(f, "begin");
		break;

		case TAC_ENDFUNC:
		fprintf(f, "end");
		break;

		case TAC_ADDR:
		fprintf(f, "%s = &%s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_DEREF:
		fprintf(f, "%s = *%s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		case TAC_STORE:
		fprintf(f, "*%s = %s", to_str(i->a, sa), to_str(i->b, sb));
		break;

		default:
		error("unknown TAC opcode");
		break;
	}
}