/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
extern int yylineno;
extern int yylex();
extern char* yytext;    //Get current token from lex
extern char buf[256];   //Get current code line from lex

int err_type = 0;
char err_func_name[10];

FILE *file;

int label_number = 0;
char *label_generator();

int assign_data_type = 0;
int assign_id = 0;

struct node {
    struct node *prev;
    struct node *next;
    int index;
    char name[30];
    char d_type[10];
    char e_type[10];
    int scope_level;
    char parameter[100];
};

void syntactic_err(char *err);

void push(struct node *);
void pop();
struct node *back();
int is_empty();
int find_index(char *id);
int find_type(char *id);
void write_tab();

int seek_prev_line();

void leave_scope(struct node *n);

void print_table();
int print_at_lex = 0;
int dont_print = 0;

struct node *symbol_table;

int scope = 0;

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();


%}


/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */


%union {
    int i_val;
    double f_val;
    char* string;
    int b_val;
    struct variable var;
}

/* Token without return */
%token PRINT 
%token IF ELSE FOR WHILE
%token SEMICOLON RETURN
%token INC DEC MOD
%token MTE LTE EQ NE
%token ADDASGN SUBASGN MULASGN DIVASGN  MODASGN
%token AND OR NOT


/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST
%token <b_val> TRUE
%token <b_val> FALSE
%token <string> VOID INT FLOAT BOOL STRING ID 

/* Nonterminal with return, which need to sepcify type */
%type <string> stat type argument argument_list func_name assign_symbol
%type <var> initialzer or_expression and_expression equal_expression relation_expression add_expression
%type <var> multi_expression unary_expression postfix_expression simple_expression func_call const expression

/* Yacc will start at this nonterminal */
%start program

/* Grammar section */
%%

program
    : program transition 
    | transition
;

transition
    : func
    | stat
;

func
    : type ID '(' argument_list ')' { 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, $2);
        char *tmp = new_node->name;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "function");
        strcpy(new_node->d_type, $1);
        strcpy(new_node->parameter, $4);
        push(new_node);
        fprintf(file, ".method public static %s(", new_node->name);
        char *tmp2 = malloc(100);
        strcpy(tmp2, new_node->parameter);
        char *param = tmp2;
        for(; *tmp2 != '\0'; ++tmp2){
            if (*tmp2 == ','){
                *tmp2 = '\0';
            }
            if (*tmp2 == ' '){
                if (strcmp(param, "int") == 0){
                    fprintf(file, "I");
                } else if (strcmp(param, "float") == 0){
                    fprintf(file, "F");
                }
                param = tmp2 + 1;
            }
        }
        if (strcmp(param, "int") == 0){
            fprintf(file, "I");
        } else if (strcmp(param, "float") == 0){
            fprintf(file, "F");
        }
        int type = find_type(new_node->name);
        fprintf(file, ")%s\n", type == -1 ? "V" : (type == 0 ? "I" : "F"));
        fprintf(file, ".limit stack 50\n");
        fprintf(file, ".limit locals 50\n");
     }  compound_stat {
         fprintf(file, ".end method\n");
     }
    | type ID '(' ')' { 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, $2);
        char *tmp = new_node->name;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "function");
        strcpy(new_node->d_type, $1);
        strcpy(new_node->parameter, "");
        push(new_node);
        int type = find_type(new_node->name);
        fprintf(file, ".method public static %s([Ljava/lang/String;)%s\n", new_node->name, type == -1 ? "V" : (type == 0 ? "I" : "F"));
        fprintf(file, ".limit stack 50\n");
        fprintf(file, ".limit locals 50\n");
     } compound_stat {
         fprintf(file, ".end method\n");
     }
    | type ID '(' argument_list ')' SEMICOLON { }
    | type ID '(' ')' SEMICOLON 
;

func_name
    : ID { char *tmp = malloc(30); strcpy(tmp, $1); $$ = tmp; }
;

argument_list
    : argument_list ',' argument {
        char *tmp = malloc(sizeof($1) + sizeof($3));
        strcat(tmp, $1);
        strcat(tmp, ", ");
        strcat(tmp, $3);
        $$ = tmp;
     }
    | argument {
        char *tmp = malloc(sizeof($1 + 1));
        strcpy(tmp, $1);
        $$ = tmp;
     }
;

argument
    : type ID {
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, $2);
        new_node->scope_level = scope + 1;
        strcpy(new_node->e_type, "parameter");
        strcpy(new_node->d_type, $1);
        push(new_node);
        $$ = $1;
     }
;

/* actions can be taken when meet the token or rule */
type
    : INT { $$ = "int"; }
    | FLOAT { $$ = "float"; }
    | BOOL { $$ = "bool"; }
    | STRING { $$ = "string"; }
    | VOID { $$ = "void"; }
;

compound_stat
    : '{' { scope += 1; } block_list '}' { scope -= 1; leave_scope(back()); }
    | '{' '}'
;

block_list
    : block_list block_item
    | block_item
;

block_item
    : declaration
    | stat
;

stat
    : declaration 
    | loop
    | expression_stat
    | return_stat
    | print_func
    | select
    | func_call SEMICOLON
;

func_call
    : ID {err_type = 1; strcpy(err_func_name, $1);} '(' para_list ')' {
        err_type = 0;
        write_tab();
        char *tmp = $1;
        for(; *tmp != '\0'; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = '\0';
                break;
            }
        }
        fprintf(file, "invokstatic compiler_hw3/%s(", $1);
        char *tmp2 = malloc(100);
        strcpy(tmp2, find_parameter($1));
        char *param = tmp2;
        for(; *tmp2 != '\0'; ++tmp2){
            if (*tmp2 == ','){
                *tmp2 = '\0';
            }
            if (*tmp2 == ' '){
                if (strcmp(param, "int") == 0){
                    fprintf(file, "I");
                } else if (strcmp(param, "float") == 0){
                    fprintf(file, "F");
                }
                param = tmp2 + 1;
            }
        }
        if (strcmp(param, "int") == 0){
            fprintf(file, "I");
        } else if (strcmp(param, "float") == 0){
            fprintf(file, "F");
        }
        int type = find_type($1);
        fprintf(file, ")%s\n", type == -1 ? "V" : (type == 0 ? "I" : "F"));
     }
    | ID {err_type = 1; strcpy(err_func_name, $1);} '(' ')' {err_type = 0;}
;

para_list
    : para_list ',' or_expression
    | or_expression
;

return_stat
    : RETURN or_expression SEMICOLON {
        int type = 0;
        if (strcmp($2.type, "float") == 0) {
            type = 1;
        }
        write_tab();
        if (type == 0){
            fprintf(file, "ireturn\n");
        } else if (type == 1){
            fprintf(file, "freturn\n");
        }
    }
    | RETURN SEMICOLON { write_tab(); fprintf(file, "return\n"); }
;

expression_stat
    : expression SEMICOLON
;

loop
    : WHILE '(' expression ')' compound_stat
;

select
    : IF '(' expression ')' compound_stat
    | IF '(' expression ')' compound_stat ELSE multi_select
;

multi_select
    : compound_stat
    | select
;

expression
    : or_expression { $$ = $1; }
    | ID {
        char *tmp = $1;
        for(; *tmp != '\0'; ++tmp){
            if (*tmp == ' ' || *tmp == '=' || *tmp == '+' || *tmp == '-' || *tmp == '*' || *tmp == '/' || *tmp == '%'){
                *tmp = '\0';
                break;
            }
        }
        assign_data_type = find_type($1);
        assign_id = find_index($1);
        write_tab();
        if (assign_data_type == 0){
            fprintf(file, "iload %d\n", assign_id);
        } else {
            fprintf(file, "fload %d\n", assign_id);
        }
    } assign_symbol or_expression {
        char *symbol = malloc(3);
        strcpy(symbol, $3);
        int right_type;
        if (strcmp($4.type, "int") == 0){
            right_type = 0;
        } else if (strcmp($4.type, "float") == 0){
            right_type = 1;
        }
        if (assign_data_type != right_type){
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "f2i\n");
            } else {
                fprintf(file, "i2f\n");
            }
        }
        switch(*symbol){
            case '+':
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "iadd\n");
            } else {
                fprintf(file, "fadd\n");
            }
            break;
            case '-':
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "isub\n");
            } else {
                fprintf(file, "fsub\n");
            }
            break;
            case '*':
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "imul\n");
            } else {
                fprintf(file, "fmul\n");
            }
            break;
            case '/':
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "idiv\n");
            } else {
                fprintf(file, "fdiv\n");
            }
            break;
            case '%':
            write_tab();
            if (assign_data_type == 0){
                fprintf(file, "irem\n");
            }
            break;
        }
        write_tab();
        fprintf(file, "%sstore %d\n", assign_data_type == 0 ? "i" : "f", assign_id);
     }
;

assign_symbol
    : '=' {$$ = "="; }
    | ADDASGN {$$ = "+="; }
    | SUBASGN {$$ = "-="; }
    | MULASGN {$$ = "*="; }
    | DIVASGN {$$ = "/="; }
    | MODASGN {$$ = "%="; }
;

or_expression
    : and_expression { $$ = $1; }
    | or_expression OR and_expression
;

and_expression
    : equal_expression { $$ = $1; }
    | and_expression AND equal_expression
;

equal_expression
    : relation_expression { $$ = $1; }
    | equal_expression EQ relation_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifeq %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
    | equal_expression NE relation_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifne %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
;

relation_expression
    : add_expression { $$ = $1; }
    | relation_expression '>' add_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifgt %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
    | relation_expression '<' add_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "iflt %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
    | relation_expression MTE add_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifge %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
    | relation_expression LTE add_expression {
        strcpy($1.type, "bool");
        $$ = $1;
        write_tab();
        if (strcmp($3.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp($3.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifle %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
;

add_expression
    : multi_expression { $$ = $1; }
    | add_expression '+' multi_expression {
        if (strcmp($1.type, "int") == 0 && strcmp($3.type, "float") == 0){
            int num = seek_prev_line(); 
            char *s = malloc(num + 1); 
            fseek(file, -2, SEEK_CUR);
            fgets(s, num, file); 
            printf("%s\n", s);
            fseek(file, -num, SEEK_CUR);
            write_tab();
            fprintf(file, "i2f\n");
            write_tab();
            fprintf(file, "%s", s);
            strcpy($1.type, "float");
        }
        if (strcmp($3.type, "int") == 0 && strcmp($1.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy($3.type, "float");
        }
        $$ = $1;
        write_tab(); 
        if (strcmp($3.type, "int") == 0) {
            fprintf(file, "iadd\n"); 
        } else {
            fprintf(file, "fadd\n");
        }
    } 
    | add_expression '-' multi_expression {
        if (strcmp($1.type, "int") == 0 && strcmp($3.type, "float") == 0){
            int num = seek_prev_line(); 
            char *s = malloc(num + 1); 
            fseek(file, -2, SEEK_CUR);
            fgets(s, num, file); 
            printf("%s\n", s);
            fseek(file, -num, SEEK_CUR);
            write_tab();
            fprintf(file, "i2f\n");
            write_tab();
            fprintf(file, "%s", s);
            strcpy($1.type, "float");
        }
        if (strcmp($3.type, "int") == 0 && strcmp($1.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy($3.type, "float");
        }
        $$ = $1;
        write_tab(); 
        if (strcmp($3.type, "int") == 0) {
            fprintf(file, "isub\n"); 
        } else {
            fprintf(file, "fsub\n");
        }
    } 
;

multi_expression
    : unary_expression { $$ = $1; }
    | multi_expression '*' unary_expression {
        if (strcmp($1.type, "int") == 0 && strcmp($3.type, "float") == 0){
            int num = seek_prev_line(); 
            char *s = malloc(num + 1); 
            fseek(file, -2, SEEK_CUR);
            fgets(s, num, file); 
            printf("%s\n", s);
            fseek(file, -num, SEEK_CUR);
            write_tab();
            fprintf(file, "i2f\n");
            write_tab();
            fprintf(file, "%s", s);
            strcpy($1.type, "float");
        }
        if (strcmp($3.type, "int") == 0 && strcmp($1.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy($3.type, "float");
        }
        $$ = $1;
        write_tab(); 
        if (strcmp($3.type, "int") == 0) {
            fprintf(file, "imul\n"); 
        } else {
            fprintf(file, "fmul\n");
        }
    } 
    | multi_expression '/' unary_expression
     {
        if (strcmp($1.type, "int") == 0 && strcmp($3.type, "float") == 0){
            int num = seek_prev_line(); 
            char *s = malloc(num + 1); 
            fseek(file, -2, SEEK_CUR);
            fgets(s, num, file); 
            printf("%s\n", s);
            fseek(file, -num, SEEK_CUR);
            write_tab();
            fprintf(file, "i2f\n");
            write_tab();
            fprintf(file, "%s", s);
            strcpy($1.type, "float");
        }
        if (strcmp($3.type, "int") == 0 && strcmp($1.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy($3.type, "float");
        }
        $$ = $1;
        write_tab(); 
        if (strcmp($3.type, "int") == 0) {
            fprintf(file, "idiv\n"); 
        } else {
            fprintf(file, "fdiv\n");
        }
    } 
    | multi_expression MOD unary_expression {
        $$ = $1;
        write_tab(); 
        if (strcmp($3.type, "int") == 0 && strcmp($1.type, "int") == 0) {
            fprintf(file, "irem\n"); 
        }
    } 
;

unary_expression
    : postfix_expression { $$ = $1; }
    | INC unary_expression
    | DEC unary_expression
    | NOT unary_expression
;

postfix_expression
    : simple_expression { $$ = $1; }
    | postfix_expression INC
    | postfix_expression DEC
;

simple_expression
    : const { $$ = $1; }
    | ID { 
        struct variable v;
        char *tmp = $1;
        for(char *i = tmp; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ' || *i == '=' || *i == ')' || *i == '(') {
                    *i = '\0';
                }
            }
        int id = find_index($1);
        int type = find_type($1);
        int variable_scope = find_scope($1);
        write_tab();
        if (variable_scope == 0){
            if (type == 0){
                fprintf(file, "getstatic compiler_hw3/%s I\n", $1);
                strcpy(v.type, "int");
            } else if (type == 1){
                fprintf(file, "getstatic compiler_hw3/%s F\n", $1);
                strcpy(v.type, "float");
            }
        }else {
            if (type == 0) {
                fprintf(file, "iload %d\n", id);
                strcpy(v.type, "int");
            } else if (type == 1){
                fprintf(file, "fload %d\n", id);
                strcpy(v.type, "float");
            }
        }
        $$ = v;
    }
    | func_call {struct variable v; $$ = v; }
;

declaration
    : type ID '=' initialzer SEMICOLON { 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, $2);
        char *tmp_name = new_node->name;
        for(; *tmp_name != NULL; ++tmp_name){
            if (*tmp_name == ' ' || *tmp_name == '='){
                *tmp_name = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "variable");
        strcpy(new_node->d_type, $1);
        push(new_node);
        if (scope == 0) {
            char *id_name = $2;
            for(char *i = id_name; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ') {
                    *i = '\0';
                }
            }
            if ($1 == "int"){
                int tmp = (int)$4.i_val;
                fprintf(file, ".field public static %s I = %d\n", $2, tmp);
            } else if ($1 == "float") {
                fprintf(file, ".field public static %s F = %f\n", $2, $4.f_val);
            } else if ($1 == "bool") {
                int tmp = (int)$4.i_val;
                fprintf(file, ".field public static %s Z = %d\n", $2, tmp);
            }
        } else {
            write_tab();
            if ($1 == "int" || $1 == "bool"){
                int tmp = (int)$4.i_val;
                fprintf(file, "ldc %d\n", tmp);
                write_tab();
                fprintf(file, "istore %d\n", new_node->index);
            } else if ($1 == "float") {
                fprintf(file, "ldc %f\n", $4.f_val);
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            }
        }
    }
    | type ID SEMICOLON {
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, $2);
        char *tmp_name = new_node->name;
        for(; *tmp_name != '\0'; ++tmp_name){
            if (*tmp_name == ' ' || *tmp_name == ';'){
                *tmp_name = '\0';
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "variable");
        strcpy(new_node->d_type, $1);
        push(new_node);  
        if (scope == 0) {
            char *id_name = $2;
            for(char *i = id_name; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ') {
                    *i = '\0';
                }
            }
            if ($1 == "int"){
                fprintf(file, ".field public static %s I = 0\n", $2);
            } else if ($1 == "float") {
                fprintf(file, ".field public static %s F = 0\n", $2);
            } else if ($1 == "bool") {
                fprintf(file, ".field public static %s Z = 0\n", $2);
            }
        } else {
            write_tab();
            if ($1 == "int" || $1 == "bool"){
                fprintf(file, "ldc 0\n");
                write_tab();
                fprintf(file, "istore %d\n", new_node->index);
            } else if ($1 == "float") {
                fprintf(file, "ldc 0\n");
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            } else if ($1 == "string") {
                fprintf(file, "ldc \"\"\n");
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            }
        }
    }
;

initialzer
    : or_expression { $$ = $1; }
;

const
    : I_CONST { float tmp = (float)$1; struct variable v; v.i_val = tmp; strcpy(v.type, "int"); $$ = v; write_tab(); fprintf(file, "ldc %d\n", $1); }
    | F_CONST { struct variable v; v.f_val = $1; strcpy(v.type, "float"); $$ = v; write_tab(); fprintf(file, "ldc %f\n", $1); }
    | '"' STR_CONST '"' { }
    | TRUE { struct variable v; v.i_val = 1; strcpy(v.type, "int"); $$ = v; write_tab(); fprintf(file, "ldc %d\n", 1); }
    | FALSE { struct variable v; v.i_val = 0; strcpy(v.type, "int"); $$ = v; write_tab(); fprintf(file, "ldc %d\n", 0); }
;

print_func
    : PRINT '(' ID ')' SEMICOLON {
        char *tmp = $3;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == ')' || *tmp == ';'){
                *tmp = NULL;
                break;
            }
        }
        int id = find_index($3);
        int variable_scope = find_scope($3);
        int type = find_type($3);
        write_tab();
        if (variable_scope == 0){
            fprintf(file, "getstatic compiler_hw3/%s %s\n", $3, type == 0 ? "I" : "F");
        } else {
            if (type == 0){
                fprintf(file, "iload %d\n", id);
            } else if (type == 1){
                fprintf(file, "fload %d\n", id);
            }
        }
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(%s)V\n", type == 0 ? "I" : "F");
    }
    | PRINT '(' I_CONST ')' SEMICOLON {
        write_tab();
        fprintf(file, "ldc %d\n", $3);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
    }
    | PRINT '(' F_CONST ')' SEMICOLON {
        write_tab();
        fprintf(file, "ldc %f\n", $3);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(F)V\n");
    }
    | PRINT '(' '"' STR_CONST {
        write_tab();
        fprintf(file, "ldc \"%s\"\n", yytext);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    } '"' ')' SEMICOLON
;

%%

/* C code section */

int syntax_err = 0;

int main(int argc, char** argv)
{
    yylineno = 0;

    symbol_table = (struct node *)malloc(sizeof(struct node));
    symbol_table->next = symbol_table;
    symbol_table->prev = symbol_table;
    symbol_table->index = -1;
    symbol_table->scope_level = 0;

    file = fopen("compiler_hw3.j","w+");

    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");

    yyparse();

    fclose(file);


    return 0;
}

void yyerror(char *s)
{
    char *tmp = err_func_name;
    for(; tmp != NULL; ++tmp){
        if (*tmp == ' ' || *tmp == '('){
            *tmp = NULL;
            break;
        }
    }

    syntax_err = 1;
    printf("%d: %s\n", yylineno + 1, buf);
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    if (err_type == 1){
        printf("| Undeclared function ");
        printf("%s", err_func_name);
    }
    else {
        printf("| Unknown error");
    }
    printf("\n|-----------------------------------------------|\n\n");
    

    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}


void semantic_err(char *err){
    dont_print = 1;
    printf("%d: %s\n", yylineno + 1, buf);
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno + 1, buf);
    printf("| %s", err);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {}
void insert_symbol() {}
int lookup_symbol() {}
void dump_symbol() {
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
}

void print_re(struct node *n){
    struct node *tmp = n;
    pop();
    if (!is_empty() && back()->scope_level == tmp->scope_level){
        print_re(back());
    }
    printf("%-10d%-10s%-12s%-10s%-10d%-10s\n",
                tmp->index, tmp->name, tmp->e_type, tmp->d_type, tmp->scope_level, tmp->parameter);
}

void leave_scope(struct node *n){
    struct node *tmp = n;
    pop();
    if (!is_empty() && back()->scope_level == tmp->scope_level){
        leave_scope(back());
    }
}

void print_table(){
    dump_symbol();
    print_re(back());
    printf("\n");
}

void write_tab(){
    fprintf(file, "\t");
}

int seek_prev_line(){
    int num = 1;
    char *s = malloc(5); 
    fseek(file, -num, SEEK_END);
    fgets(s, 4, file);
    while(*s != '\t'){
        ++num;
        fseek(file, -num, SEEK_END);
        fgets(s, 4, file);
    } 
    return num;
}

char *label_generator(){
    char *tmp = malloc(10);
    sprintf(tmp, "LABEL_%d", label_number);
    ++label_number;
    return tmp;
}

void push(struct node * n){
    struct node *tmp = symbol_table->next;
    while(tmp != symbol_table){
        if (n->scope_level == tmp->scope_level && strcmp(n->name, tmp->name) == 0){
            char err[50] = "Redeclared variable ";
            strcat(err, n->name);
            semantic_err(err);
            return;
        }
        if (tmp->scope_level > n->scope_level){
            break;
        }
        tmp = tmp->next;
    }
    n->prev = tmp->prev;
    n->next = tmp;
    tmp->prev->next = n;
    tmp->prev = n;
    if (n->scope_level == n->prev->scope_level){
        n->index = n->prev->index + 1;
    }
    else {
        n->index = 0;
    }
}

int find_index(char *id){
    struct node *tmp = symbol_table->next;
    while(tmp != symbol_table){
        if(strcmp(id, tmp->name) == 0){
            return tmp->index;
        }
        tmp = tmp->next;
    }
}

int find_type(char *id){
    struct node *tmp = symbol_table->next;
    while(tmp != symbol_table){
        if (strcmp(id, tmp->name) == 0){
            if (strcmp(tmp->d_type, "int") == 0 || strcmp(tmp->d_type, "bool") == 0){
                return 0;
            } else if (strcmp(tmp->d_type, "float") == 0){
                return 1;
            } else if (strcmp(tmp->d_type, "void") == 0){
                return -1;
            }
        }
        tmp = tmp->next;
    }
}

int find_scope(char *id){
    struct node *tmp = symbol_table->next;
    while(tmp != symbol_table){
        if (strcmp(id, tmp->name) == 0){
            return tmp->scope_level;
        }
        tmp = tmp->next;
    }
}

char *find_parameter(char *id){
    struct node *tmp = symbol_table->next;
    while(tmp != symbol_table){
        if (strcmp(id, tmp->name) == 0){
            return tmp->parameter;
        }
        tmp = tmp->next;
    }
}

void pop(){
    struct node *tmp = symbol_table->prev;
    symbol_table->prev = symbol_table->prev->prev;
    symbol_table->prev->next = symbol_table;
    if(tmp != symbol_table){
        free(tmp);
    }
}

struct node *back(){
    return symbol_table->prev;
}

int is_empty(){
    if (symbol_table->prev == symbol_table){
        return 1;
    }
    else {
        return 0;
    }
}
