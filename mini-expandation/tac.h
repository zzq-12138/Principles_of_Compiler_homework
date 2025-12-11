/* type of symbol */
#define SYM_UNDEF 0
#define SYM_VAR 1
#define SYM_FUNC 2
#define SYM_TEXT 3
#define SYM_INT 4
#define SYM_LABEL 5
#define SYM_STRUCT_TAG 6  // 结构体标签
#define SYM_CHAR       7  // 区分 int/char 成员（原 SYM_INT 复用）
/* type of tac */ 
#define TAC_UNDEF 0 /* undefine */
#define TAC_ADD 1 /* a=b+c */
#define TAC_SUB 2 /* a=b-c */
#define TAC_MUL 3 /* a=b*c */
#define TAC_DIV 4 /* a=b/c */
#define TAC_EQ 5 /* a=(b==c) */
#define TAC_NE 6 /* a=(b!=c) */
#define TAC_LT 7 /* a=(b<c) */
#define TAC_LE 8 /* a=(b<=c) */
#define TAC_GT 9 /* a=(b>c) */
#define TAC_GE 10 /* a=(b>=c) */
#define TAC_NEG 11 /* a=-b */
#define TAC_COPY 12 /* a=b */
#define TAC_GOTO 13 /* goto a */
#define TAC_IFZ 14 /* ifz b goto a */
#define TAC_BEGINFUNC 15 /* function begin */
#define TAC_ENDFUNC 16 /* function end */
#define TAC_LABEL 17 /* label a */
#define TAC_VAR 18 /* int a */
#define TAC_FORMAL 19 /* formal a */
#define TAC_ACTUAL 20 /* actual a */
#define TAC_CALL 21 /* a=call b */
#define TAC_RETURN 22 /* return a */
#define TAC_INPUT 23 /* input a */
#define TAC_OUTPUT 24 /* output a */
#define TAC_ADDR 25
#define TAC_DEREF 26
#define TAC_STORE 27
/* Data types */
#define TYPE_INT  1
#define TYPE_CHAR 2
#define TYPE_STRUCT 3 
typedef struct sym
{
	/*	
		type:SYM_VAR name:abc value:98 offset:-1
		type:SYM_VAR name:bcd value:99 offset:4
		type:SYM_LABEL name:L1/max			
		type:SYM_INT value:1			
		type:SYM_FUNC name:max address:1234		
		type:SYM_TEXT name:"hello" label:10
	*/
	int type;
	int data_type;   // TYPE_INT 或 TYPE_CHAR
	int is_ptr;
	int is_array;
	int array_size;
	int scope; /* 0:global, 1:local */
	char *name;
	int offset;
	int value;
	int label;
	struct sym *struct_tag; 
	struct tac *address; /* SYM_FUNC */	
	struct sym *next;
	void *etc;
} SYM;

typedef struct tac
{
	struct tac  *next;
	struct tac  *prev;
	int op;
	SYM *a;
	SYM *b;
	SYM *c;
	void *etc;
} TAC;

typedef struct exp
{
	struct exp *next; /* for argument list */
	TAC *tac; /* code */
	SYM *ret; /* return value */
	void *etc;
} EXP;

// 访问路径节点类型
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

// 左值表达式（可赋值的表达式）
typedef struct lvalue {
    char *base_name;              // 基础变量名
    ACCESS_NODE *access_chain;    // 访问链
} LVALUE;

// 通用的地址计算函数
typedef struct addr_result {
    SYM *addr_sym;     // 计算出的地址
    TAC *code;         // 生成的代码
    SYM *type_info;    // 类型信息
} ADDR_RESULT;
/* global var */
extern FILE *file_x, *file_s;
extern int yylineno, scope, next_tmp, next_label;
extern SYM *sym_tab_global, *sym_tab_local;
extern TAC *tac_first, *tac_last;
// 循环上下文结构（在 tac.c 中定义）
typedef struct loop_context {
    SYM *break_label;      /* break 跳转目标 */
    SYM *continue_label;   /* continue 跳转目标（循环开始） */
} LOOP_CONTEXT;

extern LOOP_CONTEXT *loop_stack;   // 循环上下文栈
extern int loop_sp;                // 循环栈指针
extern int loop_stack_size;
/* function */
ACCESS_NODE *mk_access_member(char *name);
ACCESS_NODE *mk_access_index(EXP *index);
ACCESS_NODE *mk_access_deref();
LVALUE *mk_lvalue(char *base_name, ACCESS_NODE *access_chain);
SYM *resolve_lvalue(LVALUE *lval, TAC **code);

void tac_init();
void tac_complete();
SYM *get_func(char *name);
int calculate_member_offset(SYM *struct_tag, char *member_name, TAC **found_member);
int calculate_struct_size(SYM *struct_tag);
TAC *join_tac(TAC *c1, TAC *c2);
void out_str(FILE *f, const char *format, ...);
void out_sym(FILE *f, SYM *s);
void out_tac(FILE *f, TAC *i);
SYM *mk_label(char *name);
SYM *mk_tmp(void);
SYM *mk_const(int n);
SYM *mk_text(char *text);
TAC *mk_tac(int op, SYM *a, SYM *b, SYM *c);
EXP *mk_exp(EXP *next, SYM *ret, TAC *code);
char *mk_lstr(int i);
SYM *get_var(char *name); 
SYM *declare_func(char *name);
TAC *do_lvalue_assign(LVALUE *lval, EXP *rval) ;
EXP *do_lvalue_addr(LVALUE *lval);
EXP *do_lvalue_access(LVALUE *lval);
ACCESS_NODE *append_access(ACCESS_NODE *chain, ACCESS_NODE *new_node);
TAC *declare_var(char *name);
TAC *declare_para(char *name);
TAC *do_func(SYM *name,    TAC *args, TAC *code);
TAC *do_assign(SYM *var, EXP *exp);
TAC *do_output(SYM *var);
TAC *do_input(SYM *var);
TAC *do_call(char *name, EXP *arglist);
TAC *do_if(EXP *exp, TAC *stmt);
TAC *do_test(EXP *exp, TAC *stmt1, TAC *stmt2);
// break/continue support
void push_loop_context(SYM *break_label, SYM *continue_label);
void push_break_label(SYM *label);  // 用于 switch（continue = break）
void pop_break_label(void);
SYM *peek_break_label(void);
SYM *peek_continue_label(void);
void update_continue_label(SYM *new_continue_label);
void replace_label_in_tac(TAC *tac, SYM *old_label, SYM *new_label);
SYM *lookup_sym(SYM *symtab, char *name);
void insert_sym(SYM **symtab, SYM *sym);
SYM *mk_sym(void);
SYM *mk_var(char *name);
// new while handler
TAC *do_while_with_context(EXP *exp, TAC *body, SYM *end_label, TAC *dummy);
// tac.h 中声明
TAC *declare_typed_var_ext(char *name, int data_type, int is_ptr, int is_array, int array_size, SYM *struct_tag);
SYM *mk_char_const(char c);
TAC *do_break(void);
TAC *do_continue(void);
TAC *do_case(int value, TAC *stmts);
TAC *do_default(TAC *stmts);
TAC *do_for_with_context(TAC *init, EXP *cond, TAC *incr, TAC *body, SYM *end_label, TAC *dummy);
TAC *do_switch_with_context(EXP *exp, TAC *cases, TAC *def, SYM *end_label, TAC *dummy);
EXP *do_bin( int binop, EXP *exp1, EXP *exp2);
EXP *do_cmp( int binop, EXP *exp1, EXP *exp2);
EXP *do_un( int unop, EXP *exp);
EXP *do_call_ret(char *name, EXP *arglist);

void error(const char *format, ...);