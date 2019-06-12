/*	Definition section */
%{
#include <stdio.h>
extern int yylineno;
extern int yylex();
extern char* yytext;    //Get current token from lex
extern char buf[256];   //Get current code line from lex

int err_type = 0;
char err_func_name[10];

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
}

/* Token without return */
%token PRINT 
%token IF ELSE FOR WHILE
%token SEMICOLON RETURN
%token INC DEC
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
%type <string> stat type argument argument_list func_name

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
    : type ID '(' argument_list ')' compound_stat { struct node *new_node = malloc(sizeof(*new_node));
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
             }
    | type ID '(' ')' compound_stat { struct node *new_node = malloc(sizeof(*new_node));
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
             }
    | type ID '(' argument_list ')' SEMICOLON { char *tmp = $4;
                pop();
                for(;*tmp != '\0'; ++tmp){
                    if(*tmp == ','){
                        pop();
                    }
                } }
    | type ID '(' ')' SEMICOLON 
;

func_name
    : ID { char *tmp = malloc(30); strcpy(tmp, $1); $$ = tmp; }
;

argument_list
    : argument_list ',' argument { char *tmp = malloc(sizeof($1) + sizeof($3));
                strcat(tmp, $1);
                strcat(tmp, ", ");
                strcat(tmp, $3);
                $$ = tmp; }
    | argument { char *tmp = malloc(sizeof($1 + 1));
                strcpy(tmp, $1);
                $$ = tmp; }
;

argument
    : type ID { struct node *new_node = malloc(sizeof(*new_node));
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
    : '{' { scope += 1; } block_list '}' { scope -= 1; if(back()->scope_level > scope){ print_at_lex=1; } }
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
    | func_call
;

func_call
    : ID {err_type = 1; strcpy(err_func_name, $1);} '(' para_list ')' SEMICOLON {err_type = 0; }
    | ID {err_type = 1; strcpy(err_func_name, $1);} '(' ')' SEMICOLON {err_type = 0;}
;

para_list
    : para_list ',' or_expression
    | or_expression
;

return_stat
    : RETURN or_expression SEMICOLON
;

expression_stat
    : expression SEMICOLON

loop
    : WHILE '(' expression ')' compound_stat
;

select
    : IF '(' expression ')' compound_stat
    | IF '(' expression ')' compound_stat ELSE compound_stat

expression
    : or_expression
    | ID assign_symbol or_expression
;

assign_symbol
    : '='
    | ADDASGN
    | SUBASGN
    | MULASGN
    | DIVASGN
    | MODASGN
;

or_expression
    : and_expression
    | or_expression OR and_expression
;

and_expression
    : equal_expression
    | and_expression AND equal_expression
;

equal_expression
    : relation_expression
    | equal_expression EQ relation_expression
    | equal_expression NE relation_expression
;

relation_expression
    : add_expression
    | relation_expression '>' add_expression
    | relation_expression '<' add_expression
    | relation_expression MTE add_expression
    | relation_expression LTE add_expression
;

add_expression
    : multi_expression
    | add_expression '+' multi_expression
    | add_expression '-' multi_expression
;

multi_expression
    : unary_expression
    | multi_expression '*' unary_expression
    | multi_expression '/' unary_expression
    | multi_expression '%' unary_expression
;

unary_expression
    : postfix_expression
    | INC unary_expression
    | DEC unary_expression
    | NOT unary_expression
;

postfix_expression
    : simple_expression
    | postfix_expression INC
    | postfix_expression DEC
;

simple_expression
    : const
    | ID {struct node *tmp = symbol_table->next;
        int nothing = 0;
        char cmp_text[30];
        strcpy(cmp_text, $1);
        char *char_iter = cmp_text;
        for(; char_iter != NULL; ++char_iter){
            if(*char_iter < 65 || *char_iter > 122 || *char_iter == '[' || *char_iter == ']'){
                *char_iter = '\0';
                break;
            }
        }
        while(tmp != symbol_table){
            if (strcmp(cmp_text, tmp->name) == 0){
                nothing = 1;
            }
            if (tmp->scope_level > scope){
                break;
            }
            tmp = tmp->next;
        }
        if (nothing == 0){
            char err[50] = "Undeclared variable ";
            strcat(err, cmp_text);
            semantic_err(err);
        } }
;

declaration
    : type ID '=' initialzer SEMICOLON { struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, $2);
                char *tmp = new_node->name;
                for(; tmp != NULL; ++tmp){
                    if (*tmp == ' ' || *tmp == '='){
                        *tmp = NULL;
                        break;
                    }
                }
                new_node->scope_level = scope;
                strcpy(new_node->e_type, "variable");
                strcpy(new_node->d_type, $1);
                push(new_node);
             }
    | type ID SEMICOLON { struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, $2);
                char *tmp = new_node->name;
                for(; tmp != NULL; ++tmp){
                    if (*tmp == ' ' || *tmp == ';'){
                        *tmp = NULL;
                        break;
                    }
                }
                new_node->scope_level = scope;
                strcpy(new_node->e_type, "variable");
                strcpy(new_node->d_type, $1);
                push(new_node);
             }
;

initialzer
    : or_expression
;

const
    : I_CONST
    | F_CONST
    | '"' STR_CONST '"'
    | TRUE
    | FALSE
;

print_func
    : PRINT '(' ID {struct node *tmp = symbol_table->next;
        int nothing = 0;
        char cmp_text[30];
        strcpy(cmp_text, $3);
        char *char_iter = cmp_text;
        for(; char_iter != NULL; ++char_iter){
            if(*char_iter < 65 || *char_iter > 122 || *char_iter == '[' || *char_iter == ']'){
                *char_iter = '\0';
                break;
            }
        }
        while(tmp != symbol_table){
            if (strcmp(cmp_text, tmp->name) == 0){
                nothing = 1;
            }
            if (tmp->scope_level > scope){
                break;
            }
            tmp = tmp->next;
        }
        if (nothing == 0){
            char err[50] = "Undeclared variable ";
            strcat(err, cmp_text);
            semantic_err(err);
        } } ')' SEMICOLON
    | PRINT '(' '"' STR_CONST '"' ')' SEMICOLON

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

    yyparse();
    if (!syntax_err){
        print_table();
        printf("\nTotal lines: %d \n",yylineno);
    }

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

void print_table(){
    dump_symbol();
    print_re(back());
    printf("\n");
}

/*
struct node *tmp = back();
    while(!is_empty()){
        tmp = back();
        int current_scope = tmp->scope_level;
        printf("%-10d%-10s%-12s%-10s%-10d%-10s\n",
                tmp->index, tmp->name, tmp->e_type, tmp->d_type, tmp->scope_level, tmp->parameter);
        pop();
        if (back()->scope_level != current_scope){
            break;
        }
    }
*/

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

/*
n->prev = symbol_table->prev;
    n->next = symbol_table;
    symbol_table->prev->next = n;
    symbol_table->prev = n;
    if (n->scope_level == n->prev->scope_level){
        n->index = n->prev->index + 1;
    }
    else {
        n->index = 0;
    }
*/

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
