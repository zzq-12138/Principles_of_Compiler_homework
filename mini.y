%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);

%}

%union {
    char character;
    char *string;
    SYM *sym;
    TAC *tac;
    EXP *exp;
    int integer;
    struct { char *name; int is_ptr; int is_array; int array_size; SYM *struct_tag;} decl;
    struct { int type; SYM *struct_tag; } type_info;
    ACCESS_NODE *access_node;
    LVALUE *lvalue;
}

%token INT CHAR EQ NE LT LE GT GE UMINUS IF ELSE WHILE FUNC INPUT OUTPUT RETURN FOR SWITCH CASE DEFAULT BREAK CONTINUE STRUCT
%token <string> INTEGER IDENTIFIER TEXT CHARACTER

%left EQ NE LT LE GT GE
%left '+' '-'
%left '*' '/'
%right UMINUS

%type <tac> program function switch_statement case_list variable_list case_clause default_clause parameter_list statement assignment_statement return_statement if_statement for_statement while_statement call_statement block declaration_list declaration statement_list input_statement output_statement
%type <exp> argument_list expression_list expression call_expression
%type <sym> function_head loop_start for_start switch_start
%type <tac> loop_end for_end switch_end global_declarations
%type <type_info> type_specifier_value
%type <decl> var_decl
%type <sym> struct_specifier
%type <tac> struct_member_list struct_member
%type <access_node> access_chain access_item
%type <lvalue> lvalue_expr

%%

program : global_declarations
{
    tac_last = $1;
    tac_complete();
}
;

global_declarations
    : /* empty */
    { $$ = NULL; }
    | global_declarations struct_decl
    { $$ = $1; }
    | global_declarations function
    { $$ = join_tac($1, $2); }
    | global_declarations declaration
    { $$ = join_tac($1, $2); }
;

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
        
        printf("=== Defining struct %s ===\n", $2);
        
        tag->etc = $4;
        
        printf("Final struct layout verification:\n");
        int offset = 0;
        for (TAC *p = (TAC*)tag->etc; p; p = p->prev) {
            if (p->a && p->a->name) {
                int member_size = 4;
                if (p->a->is_array) {
                    if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                        int element_size = calculate_struct_size(p->a->struct_tag);
                        member_size = p->a->array_size * element_size;
                    } else {
                        member_size = p->a->array_size * 4;
                    }
                } else if (p->a->data_type == TYPE_STRUCT && p->a->struct_tag) {
                    member_size = calculate_struct_size(p->a->struct_tag);
                }
                printf("  %s: offset=%d, size=%d\n", p->a->name, offset, member_size);
                offset += member_size;
            }
        }
        printf("Total struct size: %d\n", offset);
        printf("=== End struct %s ===\n\n", $2);
        
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
        if (!member_sym->name) {
            error("memory allocation failed for member name");
        }
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
        if (!member_tac) {
            error("memory allocation failed for member TAC");
        }
        $$ = member_tac;
    }
;

declaration : type_specifier_value variable_list ';'
{
    $$ = $2;
}
;

type_specifier_value
    : INT
    {
        $$.type = TYPE_INT;
        $$.struct_tag = NULL;
    }
    | CHAR
    {
        $$.type = TYPE_CHAR;
        $$.struct_tag = NULL;
    }
    | struct_specifier
    {
        $$.type = TYPE_STRUCT;
        $$.struct_tag = $1;
    }
;

variable_list
    : var_decl
    {
        int dt = $<type_info>0.type;
        SYM *st = $<type_info>0.struct_tag;
        $$ = declare_typed_var_ext($1.name, dt, $1.is_ptr, $1.is_array, $1.array_size, st);
    }
    | variable_list ',' var_decl
    {
        int dt = $<type_info>0.type;
        SYM *st = $<type_info>0.struct_tag;
        $$ = join_tac($1, declare_typed_var_ext($3.name, dt, $3.is_ptr, $3.is_array, $3.array_size, st));
    }
;

var_decl
    : IDENTIFIER
    {
        $$.name = $1;
        $$.is_ptr = 0;
        $$.is_array = 0;
        $$.array_size = 0;
        $$.struct_tag = NULL;
    }
    | '*' IDENTIFIER
    {
        $$.name = $2;
        $$.is_ptr = 1;
        $$.is_array = 0;
        $$.array_size = 0;
        $$.struct_tag = NULL;
    }
    | IDENTIFIER '[' INTEGER ']'
    {
        $$.name = $1;
        $$.is_ptr = 0;
        $$.is_array = 1;
        $$.array_size = atoi($3);
        $$.struct_tag = NULL;
    }
;

struct_specifier
    : STRUCT IDENTIFIER
    {
        SYM *tag = lookup_sym(sym_tab_global, $2);
        if (!tag | tag->type != SYM_STRUCT_TAG) {
            error("undefined struct '%s'", $2);
        }
        $$ = tag;
    }
;

function : function_head '(' parameter_list ')' block
{
    $$=do_func($1, $3, $5);
    scope=0;
    sym_tab_local=NULL;
}
| error
{
    error("Bad function syntax");
    $$=NULL;
}
;

function_head : IDENTIFIER
{
    $$=declare_func($1);
    scope=1;
    sym_tab_local=NULL;
}
;

parameter_list : IDENTIFIER
{
    $$=declare_para($1);
}               
| parameter_list ',' IDENTIFIER
{
    $$=join_tac($1, declare_para($3));
}               
|
{
    $$=NULL;
}
;

statement : assignment_statement ';'
| input_statement ';'
| output_statement ';'
| call_statement ';'
| return_statement ';'
| if_statement
| for_statement
| while_statement
| switch_statement 
| block
| BREAK ';'
{
    $$ = do_break();
}
| CONTINUE ';'
{
    $$ = do_continue();
}
| error
{
    error("Bad statement syntax");
    $$=NULL;
}
;

block : '{' declaration_list statement_list '}'
{
    $$=join_tac($2, $3);
}               
;

declaration_list        :
{
    $$=NULL;
}
| declaration_list declaration
{
    $$=join_tac($1, $2);
}
;

statement_list : statement
| statement_list statement
{
    $$=join_tac($1, $2);
}               
;

assignment_statement
    : lvalue_expr '=' expression
    {
        $$ = do_lvalue_assign($1, $3);
    }
    | '*' expression '=' expression
    {
        if (!$2->ret->is_ptr) error("assign to non-pointer");
        TAC *code = mk_tac(TAC_STORE, $2->ret, $4->ret, NULL);
        code->prev = join_tac($2->tac, $4->tac);
        $$ = code;
    }
;

lvalue_expr
    : IDENTIFIER access_chain
    {
        $$ = mk_lvalue($1, $2);
    }
    | IDENTIFIER
    {
        $$ = mk_lvalue($1, NULL);
    }
;

access_chain
    : access_item
    {
        $$ = $1;
    }
    | access_chain access_item
    {
        $$ = append_access($1, $2);
    }
;

access_item
    : '.' IDENTIFIER
    {
        $$ = mk_access_member($2);
    }
    | '[' expression ']'
    {
        $$ = mk_access_index($2);
    }
;

expression : expression '+' expression
{
    $$=do_bin(TAC_ADD, $1, $3);
}
| expression '-' expression
{
    $$=do_bin(TAC_SUB, $1, $3);
}
| expression '*' expression
{
    $$=do_bin(TAC_MUL, $1, $3);
}
| expression '/' expression
{
    $$=do_bin(TAC_DIV, $1, $3);
}
| '-' expression  %prec UMINUS
{
    $$=do_un(TAC_NEG, $2);
}
| expression EQ expression
{
    $$=do_cmp(TAC_EQ, $1, $3);
}
| expression NE expression
{
    $$=do_cmp(TAC_NE, $1, $3);
}
| expression LT expression
{
    $$=do_cmp(TAC_LT, $1, $3);
}
| expression LE expression
{
    $$=do_cmp(TAC_LE, $1, $3);
}
| expression GT expression
{
    $$=do_cmp(TAC_GT, $1, $3);
}
| expression GE expression
{
    $$=do_cmp(TAC_GE, $1, $3);
}
| '(' expression ')'
{
    $$=$2;
}               
| INTEGER
{
    $$=mk_exp(NULL, mk_const(atoi($1)), NULL);
}
| CHARACTER
{
    $$ = mk_exp(NULL, mk_char_const($1[0]), NULL);
}
| call_expression
{
    $$=$1;
}      
| '&' lvalue_expr
{
    $$ = do_lvalue_addr($2);
}      
| '*' expression
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
| lvalue_expr
{
    $$ = do_lvalue_access($1);
}
| error
{
    error("Bad expression syntax");
    $$=mk_exp(NULL, NULL, NULL);
}
;

argument_list           :
{
    $$=NULL;
}
| expression_list
;

expression_list : expression
|  expression_list ',' expression
{
    $3->next=$1;
    $$=$3;
}
;

input_statement : INPUT IDENTIFIER
{
    $$=do_input(get_var($2));
}
;

output_statement : OUTPUT expression
{
    TAC *output_tac = mk_tac(TAC_OUTPUT, $2->ret, NULL, NULL);
    output_tac->prev = $2->tac;
    $$ = output_tac;
}
| OUTPUT TEXT
{
    $$=do_output(mk_text($2));
}
;

return_statement : RETURN expression
{
    TAC *t=mk_tac(TAC_RETURN, $2->ret, NULL, NULL);
    t->prev=$2->tac;
    $$=t;
}               
;

if_statement : IF '(' expression ')' block
{
    $$=do_if($3, $5);
}
| IF '(' expression ')' block ELSE block
{
    $$=do_test($3, $5, $7);
}
;

loop_start : /* empty */
{
    $$ = mk_label(mk_lstr(next_label++));
    // 创建一个临时的 continue 标签（占位符，稍后会被更新）
    SYM *temp_continue = mk_label(mk_lstr(next_label++));
    push_loop_context($$, temp_continue);
}
;

loop_end : /* empty */
{
    pop_break_label();
    $$ = NULL;
}
;

for_start : /* empty */
{
    $$ = mk_label(mk_lstr(next_label++));
    // 创建一个临时的 continue 标签（占位符，稍后会被更新）
    SYM *temp_continue = mk_label(mk_lstr(next_label++));
    push_loop_context($$, temp_continue);
}
;

for_end : /* empty */
{
    pop_break_label();
    $$ = NULL;
}
;

switch_start : /* empty */
{
    $$ = mk_label(mk_lstr(next_label++));
    push_break_label($$);
}
;

switch_end : /* empty */
{
    pop_break_label();
    $$ = NULL;
}
;

call_statement : IDENTIFIER '(' argument_list ')'
{
    TAC *args_tac = NULL;
    EXP *arg = $3;
    while (arg) {
        TAC *actual = mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL);
        actual->prev = join_tac(args_tac, arg->tac);
        args_tac = actual;
        arg = arg->next;
    }
    
    SYM *func = get_func($1);
    if (!func) {
        error("undefined function '%s'", $1);
    }
    
    TAC *call_tac = mk_tac(TAC_CALL, NULL, func, NULL);
    call_tac->prev = args_tac;
    $$ = call_tac;
}
;

call_expression : IDENTIFIER '(' argument_list ')'
{
    TAC *args_tac = NULL;
    EXP *arg = $3;
    while (arg) {
        TAC *actual = mk_tac(TAC_ACTUAL, arg->ret, NULL, NULL);
        actual->prev = join_tac(args_tac, arg->tac);
        args_tac = actual;
        arg = arg->next;
    }
    
    SYM *func = get_func($1);
    if (!func) {
        error("undefined function '%s'", $1);
    }
    
    SYM *ret_var = mk_tmp();
    ret_var->data_type = TYPE_INT;
    
    TAC *call_tac = mk_tac(TAC_CALL, ret_var, func, NULL);
    call_tac->prev = args_tac;
    
    $$ = mk_exp(NULL, ret_var, call_tac);
}
;

while_statement : WHILE '(' expression ')' loop_start block loop_end
{
    $$ = do_while_with_context($3, $6, $5, $7);
}
;

for_statement : FOR '(' assignment_statement ';' expression ';' assignment_statement ')' for_start block for_end
{
    $$ = do_for_with_context($3, $5, $7, $10, $9, $11);
}
;

switch_statement : SWITCH '(' expression ')' '{' switch_start case_list default_clause switch_end '}'
{
    $$ = do_switch_with_context($3, $7, $8, $6, $9);
}
;

case_list
    : /* empty */               { $$ = NULL; }
    | case_list case_clause     { $$ = join_tac($1, $2); }
    ;

case_clause
    : CASE INTEGER ':' statement_list
    {
        $$ = do_case(atoi($2), $4);
    }
    ;

default_clause
    : /* empty */               { $$ = NULL; }
    | DEFAULT ':' statement_list
    {
        $$ = do_default($3);
    }
    ;
    
%%

void yyerror(char* msg) 
{
    fprintf(stderr, "%s: line %d\n", msg, yylineno);
    exit(0);
}
