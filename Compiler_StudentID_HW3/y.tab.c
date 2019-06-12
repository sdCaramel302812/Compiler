/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 3 "compiler_hw3.y"
#include <stdio.h>
#include <stdlib.h>
#include "define.h"
extern int yylineno;
extern int yylex();
extern char* yytext;    /*Get current token from lex*/
extern char buf[256];   /*Get current code line from lex*/

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


#line 70 "compiler_hw3.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    int i_val;
    double f_val;
    char* string;
    int b_val;
    struct variable var;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 96 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define PRINT 257
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define SEMICOLON 262
#define RETURN 263
#define INC 264
#define DEC 265
#define MOD 266
#define MTE 267
#define LTE 268
#define EQ 269
#define NE 270
#define ADDASGN 271
#define SUBASGN 272
#define MULASGN 273
#define DIVASGN 274
#define MODASGN 275
#define AND 276
#define OR 277
#define NOT 278
#define I_CONST 279
#define F_CONST 280
#define STR_CONST 281
#define TRUE 282
#define FALSE 283
#define VOID 284
#define INT 285
#define FLOAT 286
#define BOOL 287
#define STRING 288
#define ID 289
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,   20,   20,   23,   21,   24,   21,   21,   21,
    5,    4,    4,    3,    2,    2,    2,    2,    2,   26,
   22,   22,   25,   25,   27,   27,    1,    1,    1,    1,
    1,    1,    1,   34,   17,   36,   17,   35,   35,   31,
   31,   30,   29,   33,   33,   37,   37,   19,   38,   19,
    6,    6,    6,    6,    6,    6,    8,    8,    9,    9,
   10,   10,   10,   11,   11,   11,   11,   11,   12,   12,
   12,   13,   13,   13,   13,   14,   14,   14,   14,   15,
   15,   15,   16,   16,   16,   28,   28,    7,   18,   18,
   18,   18,   18,   32,   32,   32,   39,   32,
};
static const YYINT yylen[] = {                            2,
    2,    1,    1,    1,    0,    7,    0,    6,    6,    5,
    1,    3,    1,    2,    1,    1,    1,    1,    1,    0,
    4,    2,    2,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    0,    5,    0,    4,    3,    1,    3,
    2,    2,    5,    5,    7,    1,    1,    1,    0,    4,
    1,    1,    1,    1,    1,    1,    1,    3,    1,    3,
    1,    3,    3,    1,    3,    3,    3,    3,    1,    3,
    3,    1,    3,    3,    3,    1,    2,    2,    2,    1,
    2,    2,    1,    1,    1,    5,    3,    1,    1,    1,
    3,    1,    1,    5,    5,    5,    0,    8,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,   89,   90,   92,
   93,   19,   15,   16,   17,   18,    0,    0,    0,    4,
    0,    0,    0,    0,    0,    0,    0,   72,    0,   80,
    0,   83,    0,    2,    3,   27,   28,   29,   30,   31,
   32,    0,    0,    0,   41,    0,    0,   85,   77,   78,
   79,    0,    0,    0,    0,    1,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   81,   82,   33,   42,    0,    0,    0,    0,    0,    0,
   40,    0,    0,   52,   53,   54,   55,   56,   51,    0,
   91,   87,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   75,   73,   74,    0,    0,    0,
   97,    0,    0,    0,    0,   37,    0,    0,    0,   13,
    0,    0,    0,   95,   96,   94,    0,    0,    0,   43,
   35,    0,   10,    0,   14,    0,    0,   86,    0,   22,
    0,    0,    0,    8,    9,    0,   12,    0,   26,    0,
    0,   24,   25,   46,   47,   45,    6,   98,    0,   21,
   23,
};
static const YYINT yydgoto[] = {                         19,
   20,   21,  120,  121,    0,   90,  122,   22,   23,   24,
   25,   26,   27,   28,   29,   30,   48,   32,   33,   34,
   35,  129,  146,  134,  151,  141,  152,   36,   37,   38,
   39,   40,   41,   52,  115,   53,  156,   54,  127,
};
static const YYINT yysindex[] = {                        13,
  -22,  -15,   39,   58,   78,   78,   78,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -244,   13,    0,
 -240, -226, -223, -198,   81,  -23,  -32,    0, -191,    0,
 -201,    0, -196,    0,    0,    0,    0,    0,    0,    0,
    0,   -7,   86,   86,    0,    0, -248,    0,    0,    0,
    0,   43,   44,  -59,   34,    0,  -27,   78,   78,   78,
   78,   78,   78,   78,   78,   78,   78,   78,   78,   78,
    0,    0,    0,    0,   45,   47,   48, -194,   55,   56,
    0,   78,   59,    0,    0,    0,    0,    0,    0,   78,
    0,    0,   28,   78, -223, -198,   81,   81,  -23,  -23,
  -23,  -23,  -32,  -32,    0,    0,    0, -177, -163, -161,
    0,  -18,  -18, -226,   -3,    0, -226, -159, -185,    0,
   19, -156, -226,    0,    0,    0,   73,  -17, -150,    0,
    0,   78,    0,  -18,    0, -152, -229,    0,   70,    0,
   13, -112, -226,    0,    0,  -18,    0, -149,    0, -175,
  -34,    0,    0,    0,    0,    0,    0,    0,  -58,    0,
    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  112,    0,    0,    0,
    0,  -25,  -36,  -20,  -37,  311,  158,    0,  147,    0,
  348,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  135,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   -2,   77,  264,  277,  377,  410,
  421,  432,  388,  399,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   21,    0,    0,  -24,   -8,    0,    0,
    0,    0, -146,    0,    0,    0,    0,   46,    1,    0,
    0,    0,    0,    0,    0,   -6,    0,    0,    0,    0,
    0,    0,   26,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,
};
static const YYINT yygindex[] = {                         0,
 -118,  -87,  -14,    0,    0,    0,    0,    8,   61,   63,
   15,  -19,   11,   25,    0,    0,    9,    0,   38,  105,
    0,  -94,    0,    0,    0,    0,  -26, -115,    0,    0,
    0,    0,  -13,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 709
static const YYINT yytable[] = {                         18,
   44,   89,   94,   61,   57,  119,   61,   57,   31,   69,
  128,   47,   93,   81,   70,   48,   50,   42,  130,   66,
   59,   67,  149,   59,   43,  153,   78,   31,   58,   49,
   50,   51,  149,   94,   44,  153,   55,  131,   58,  144,
  132,   58,   99,  100,  101,  102,   18,  154,   57,  119,
   58,  157,   59,  150,   12,   13,   14,   15,   16,  136,
   73,   39,  137,  150,   39,   74,   38,   91,  118,   38,
   60,   61,   71,   72,   97,   98,  103,  104,   44,   20,
   79,   80,   82,   83,  124,  108,  111,  109,  110,  114,
  160,   18,  105,  106,  107,  112,  113,  117,  125,  116,
  126,  123,  133,  135,  128,  138,  139,  140,  142,  145,
  148,   18,  158,  159,    7,   88,    5,   60,   95,   18,
   60,   96,  147,   56,  161,   44,    0,    0,  155,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  143,
   65,    0,   64,    0,    0,    2,    0,    0,    0,   31,
    0,   34,   84,   84,   84,    0,   84,    0,   84,   31,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   84,   49,   84,   34,   84,   84,   84,   84,   84,
    0,   84,    0,    0,    0,    0,    0,   76,   76,   76,
   76,   76,    0,   76,   84,    0,   84,    0,   69,    0,
   69,   69,   69,   92,    0,    0,   76,    0,   76,    0,
    0,   84,   85,   86,   87,   88,    0,   69,    0,   69,
    0,    0,    1,    2,   61,   57,    3,    0,    4,    5,
    6,   61,   61,   68,   92,    0,   48,   50,   61,   61,
   57,   59,    0,    7,    8,    9,    0,   10,   11,   12,
   13,   14,   15,   16,   17,   59,   59,   44,   44,   58,
    0,   44,    0,   44,   44,   44,    0,    0,    0,    1,
    2,   75,   76,    3,   58,    4,    5,    6,   44,   44,
   44,   77,   44,   44,   44,   44,   44,   44,   44,   44,
    7,    8,    9,    0,   10,   11,   12,   13,   14,   15,
   16,   17,   20,   20,   62,    0,   20,   62,   20,   20,
   20,   12,   13,   14,   15,   16,    0,   63,    0,   45,
   63,    5,    6,   20,   20,   20,    0,   20,   20,   20,
   20,   20,   20,   20,   20,    7,    8,    9,   60,   10,
   11,    5,    6,    0,    0,    0,   46,   62,   63,    5,
    6,   64,   60,   60,   64,    7,    8,    9,    0,   10,
   11,    0,    0,    7,    8,    9,   46,   10,   11,    0,
   64,    0,   64,   84,   17,   84,   84,   84,   84,   84,
   84,   84,   49,   49,   49,   49,   49,   84,   84,   85,
   85,    0,   85,    0,   85,    0,   84,    0,   84,   84,
   84,   84,   84,   84,   84,    0,    0,   85,   76,   85,
   84,   84,   76,   76,   76,   76,   76,   67,    0,   69,
   67,    0,   76,   76,   69,   69,   69,   69,   70,    0,
   70,   70,   70,   69,   69,    0,   67,    0,   67,   71,
    0,   71,   71,   71,    0,    0,    0,   70,    0,   70,
   68,    0,    0,   68,    0,    0,    0,    0,   71,    0,
   71,   65,    0,    0,   65,    0,    0,    0,    0,   68,
    0,   68,   66,    0,    0,   66,    0,    0,    0,    0,
   65,    0,   65,    0,    0,    0,    0,    0,    0,    0,
    0,   66,    0,   66,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   62,    0,    0,    0,    0,
    0,    0,   62,   62,    0,    0,    0,    0,   63,   62,
   62,    0,    0,    0,    0,   63,   63,    0,    0,    0,
    0,    0,   63,   63,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   64,    0,    0,    0,    0,   64,   64,   64,
   64,    0,    0,    0,    0,    0,   64,   64,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   85,   85,   85,   85,   85,   85,   85,    0,    0,
    0,    0,    0,   85,   85,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   67,    0,
    0,    0,    0,   67,   67,   67,   67,    0,    0,   70,
    0,    0,   67,   67,   70,   70,   70,   70,    0,    0,
   71,    0,    0,   70,   70,   71,   71,   71,   71,    0,
    0,   68,    0,    0,   71,   71,   68,   68,   68,   68,
    0,    0,   65,    0,    0,   68,   68,   65,   65,   65,
   65,    0,    0,   66,    0,    0,   65,   65,   66,   66,
   66,   66,    0,    0,    0,    0,    0,   66,   66,
};
static const YYINT yycheck[] = {                         34,
    0,   61,   61,   41,   41,   93,   44,   44,    0,   42,
  123,    4,   40,  262,   47,   41,   41,   40,  113,   43,
   41,   45,  141,   44,   40,  141,   34,   19,  277,    5,
    6,    7,  151,   61,   34,  151,  281,   41,   41,  134,
   44,   44,   62,   63,   64,   65,   34,  142,  289,  137,
  277,  146,  276,  141,  284,  285,  286,  287,  288,   41,
  262,   41,   44,  151,   44,  262,   41,   34,   41,   44,
  269,  270,  264,  265,   60,   61,   66,   67,   40,   34,
   43,   44,   40,   40,  262,   41,  281,   41,   41,   82,
  125,   34,   68,   69,   70,   41,   41,   90,  262,   41,
  262,   94,  262,  289,  123,  262,   34,  125,  259,  262,
   41,   34,  262,  289,  123,  262,  123,   41,   58,   34,
   44,   59,  137,   19,  151,  125,   -1,   -1,  142,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  132,
   60,   -1,   62,   -1,   -1,  258,   -1,   -1,   -1,  141,
   -1,   40,   41,   42,   43,   -1,   45,   -1,   47,  151,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   61,   62,   40,   41,   42,   43,   44,   45,
   -1,   47,   -1,   -1,   -1,   -1,   -1,   41,   42,   43,
   44,   45,   -1,   47,   60,   -1,   62,   -1,   41,   -1,
   43,   44,   45,  262,   -1,   -1,   60,   -1,   62,   -1,
   -1,  271,  272,  273,  274,  275,   -1,   60,   -1,   62,
   -1,   -1,  257,  258,  262,  262,  261,   -1,  263,  264,
  265,  269,  270,  266,  262,   -1,  262,  262,  276,  277,
  277,  262,   -1,  278,  279,  280,   -1,  282,  283,  284,
  285,  286,  287,  288,  289,  276,  277,  257,  258,  262,
   -1,  261,   -1,  263,  264,  265,   -1,   -1,   -1,  257,
  258,  279,  280,  261,  277,  263,  264,  265,  278,  279,
  280,  289,  282,  283,  284,  285,  286,  287,  288,  289,
  278,  279,  280,   -1,  282,  283,  284,  285,  286,  287,
  288,  289,  257,  258,   41,   -1,  261,   44,  263,  264,
  265,  284,  285,  286,  287,  288,   -1,   41,   -1,  262,
   44,  264,  265,  278,  279,  280,   -1,  282,  283,  284,
  285,  286,  287,  288,  289,  278,  279,  280,  262,  282,
  283,  264,  265,   -1,   -1,   -1,  289,  267,  268,  264,
  265,   41,  276,  277,   44,  278,  279,  280,   -1,  282,
  283,   -1,   -1,  278,  279,  280,  289,  282,  283,   -1,
   60,   -1,   62,  262,  289,  264,  265,  266,  267,  268,
  269,  270,  271,  272,  273,  274,  275,  276,  277,   42,
   43,   -1,   45,   -1,   47,   -1,  262,   -1,  264,  265,
  266,  267,  268,  269,  270,   -1,   -1,   60,  262,   62,
  276,  277,  266,  267,  268,  269,  270,   41,   -1,  262,
   44,   -1,  276,  277,  267,  268,  269,  270,   41,   -1,
   43,   44,   45,  276,  277,   -1,   60,   -1,   62,   41,
   -1,   43,   44,   45,   -1,   -1,   -1,   60,   -1,   62,
   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   60,   -1,
   62,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   60,
   -1,   62,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,   -1,   -1,
   -1,   -1,  269,  270,   -1,   -1,   -1,   -1,  262,  276,
  277,   -1,   -1,   -1,   -1,  269,  270,   -1,   -1,   -1,
   -1,   -1,  276,  277,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,   -1,   -1,   -1,   -1,   -1,  276,  277,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  264,  265,  266,  267,  268,  269,  270,   -1,   -1,
   -1,   -1,   -1,  276,  277,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,   -1,
   -1,   -1,   -1,  267,  268,  269,  270,   -1,   -1,  262,
   -1,   -1,  276,  277,  267,  268,  269,  270,   -1,   -1,
  262,   -1,   -1,  276,  277,  267,  268,  269,  270,   -1,
   -1,  262,   -1,   -1,  276,  277,  267,  268,  269,  270,
   -1,   -1,  262,   -1,   -1,  276,  277,  267,  268,  269,
  270,   -1,   -1,  262,   -1,   -1,  276,  277,  267,  268,
  269,  270,   -1,   -1,   -1,   -1,   -1,  276,  277,
};
#define YYFINAL 19
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 289
#define YYUNDFTOKEN 331
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'\"'",0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,0,0,"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"PRINT","IF","ELSE","FOR","WHILE","SEMICOLON","RETURN",
"INC","DEC","MOD","MTE","LTE","EQ","NE","ADDASGN","SUBASGN","MULASGN","DIVASGN",
"MODASGN","AND","OR","NOT","I_CONST","F_CONST","STR_CONST","TRUE","FALSE",
"VOID","INT","FLOAT","BOOL","STRING","ID",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : program transition",
"program : transition",
"transition : func",
"transition : stat",
"$$1 :",
"func : type ID '(' argument_list ')' $$1 compound_stat",
"$$2 :",
"func : type ID '(' ')' $$2 compound_stat",
"func : type ID '(' argument_list ')' SEMICOLON",
"func : type ID '(' ')' SEMICOLON",
"func_name : ID",
"argument_list : argument_list ',' argument",
"argument_list : argument",
"argument : type ID",
"type : INT",
"type : FLOAT",
"type : BOOL",
"type : STRING",
"type : VOID",
"$$3 :",
"compound_stat : '{' $$3 block_list '}'",
"compound_stat : '{' '}'",
"block_list : block_list block_item",
"block_list : block_item",
"block_item : declaration",
"block_item : stat",
"stat : declaration",
"stat : loop",
"stat : expression_stat",
"stat : return_stat",
"stat : print_func",
"stat : select",
"stat : func_call SEMICOLON",
"$$4 :",
"func_call : ID $$4 '(' para_list ')'",
"$$5 :",
"func_call : ID $$5 '(' ')'",
"para_list : para_list ',' or_expression",
"para_list : or_expression",
"return_stat : RETURN or_expression SEMICOLON",
"return_stat : RETURN SEMICOLON",
"expression_stat : expression SEMICOLON",
"loop : WHILE '(' expression ')' compound_stat",
"select : IF '(' expression ')' compound_stat",
"select : IF '(' expression ')' compound_stat ELSE multi_select",
"multi_select : compound_stat",
"multi_select : select",
"expression : or_expression",
"$$6 :",
"expression : ID $$6 assign_symbol or_expression",
"assign_symbol : '='",
"assign_symbol : ADDASGN",
"assign_symbol : SUBASGN",
"assign_symbol : MULASGN",
"assign_symbol : DIVASGN",
"assign_symbol : MODASGN",
"or_expression : and_expression",
"or_expression : or_expression OR and_expression",
"and_expression : equal_expression",
"and_expression : and_expression AND equal_expression",
"equal_expression : relation_expression",
"equal_expression : equal_expression EQ relation_expression",
"equal_expression : equal_expression NE relation_expression",
"relation_expression : add_expression",
"relation_expression : relation_expression '>' add_expression",
"relation_expression : relation_expression '<' add_expression",
"relation_expression : relation_expression MTE add_expression",
"relation_expression : relation_expression LTE add_expression",
"add_expression : multi_expression",
"add_expression : add_expression '+' multi_expression",
"add_expression : add_expression '-' multi_expression",
"multi_expression : unary_expression",
"multi_expression : multi_expression '*' unary_expression",
"multi_expression : multi_expression '/' unary_expression",
"multi_expression : multi_expression MOD unary_expression",
"unary_expression : postfix_expression",
"unary_expression : INC unary_expression",
"unary_expression : DEC unary_expression",
"unary_expression : NOT unary_expression",
"postfix_expression : simple_expression",
"postfix_expression : postfix_expression INC",
"postfix_expression : postfix_expression DEC",
"simple_expression : const",
"simple_expression : ID",
"simple_expression : func_call",
"declaration : type ID '=' initialzer SEMICOLON",
"declaration : type ID SEMICOLON",
"initialzer : or_expression",
"const : I_CONST",
"const : F_CONST",
"const : '\"' STR_CONST '\"'",
"const : TRUE",
"const : FALSE",
"print_func : PRINT '(' ID ')' SEMICOLON",
"print_func : PRINT '(' I_CONST ')' SEMICOLON",
"print_func : PRINT '(' F_CONST ')' SEMICOLON",
"$$7 :",
"print_func : PRINT '(' '\"' STR_CONST $$7 '\"' ')' SEMICOLON",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 861 "compiler_hw3.y"

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
#line 782 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 5:
#line 118 "compiler_hw3.y"
	{ 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, yystack.l_mark[-3].string);
        char *tmp = new_node->name;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "function");
        strcpy(new_node->d_type, yystack.l_mark[-4].string);
        strcpy(new_node->parameter, yystack.l_mark[-1].string);
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
     }
break;
case 6:
#line 159 "compiler_hw3.y"
	{
         fprintf(file, ".end method\n");
     }
break;
case 7:
#line 162 "compiler_hw3.y"
	{ 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, yystack.l_mark[-2].string);
        char *tmp = new_node->name;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "function");
        strcpy(new_node->d_type, yystack.l_mark[-3].string);
        strcpy(new_node->parameter, "");
        push(new_node);
        int type = find_type(new_node->name);
        fprintf(file, ".method public static %s([Ljava/lang/String;)%s\n", new_node->name, type == -1 ? "V" : (type == 0 ? "I" : "F"));
        fprintf(file, ".limit stack 50\n");
        fprintf(file, ".limit locals 50\n");
     }
break;
case 8:
#line 181 "compiler_hw3.y"
	{
         fprintf(file, ".end method\n");
     }
break;
case 9:
#line 184 "compiler_hw3.y"
	{ }
break;
case 11:
#line 189 "compiler_hw3.y"
	{ char *tmp = malloc(30); strcpy(tmp, yystack.l_mark[0].string); yyval.string = tmp; }
break;
case 12:
#line 193 "compiler_hw3.y"
	{
        char *tmp = malloc(sizeof(yystack.l_mark[-2].string) + sizeof(yystack.l_mark[0].string));
        strcat(tmp, yystack.l_mark[-2].string);
        strcat(tmp, ", ");
        strcat(tmp, yystack.l_mark[0].string);
        yyval.string = tmp;
     }
break;
case 13:
#line 200 "compiler_hw3.y"
	{
        char *tmp = malloc(sizeof(yystack.l_mark[0].string + 1));
        strcpy(tmp, yystack.l_mark[0].string);
        yyval.string = tmp;
     }
break;
case 14:
#line 208 "compiler_hw3.y"
	{
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, yystack.l_mark[0].string);
        new_node->scope_level = scope + 1;
        strcpy(new_node->e_type, "parameter");
        strcpy(new_node->d_type, yystack.l_mark[-1].string);
        push(new_node);
        yyval.string = yystack.l_mark[-1].string;
     }
break;
case 15:
#line 221 "compiler_hw3.y"
	{ yyval.string = "int"; }
break;
case 16:
#line 222 "compiler_hw3.y"
	{ yyval.string = "float"; }
break;
case 17:
#line 223 "compiler_hw3.y"
	{ yyval.string = "bool"; }
break;
case 18:
#line 224 "compiler_hw3.y"
	{ yyval.string = "string"; }
break;
case 19:
#line 225 "compiler_hw3.y"
	{ yyval.string = "void"; }
break;
case 20:
#line 229 "compiler_hw3.y"
	{ scope += 1; }
break;
case 21:
#line 229 "compiler_hw3.y"
	{ scope -= 1; leave_scope(back()); }
break;
case 34:
#line 254 "compiler_hw3.y"
	{err_type = 1; strcpy(err_func_name, yystack.l_mark[0].string);}
break;
case 35:
#line 254 "compiler_hw3.y"
	{
        err_type = 0;
        write_tab();
        char *tmp = yystack.l_mark[-4].string;
        for(; *tmp != '\0'; ++tmp){
            if (*tmp == ' ' || *tmp == '('){
                *tmp = '\0';
                break;
            }
        }
        fprintf(file, "invokstatic compiler_hw3/%s(", yystack.l_mark[-4].string);
        char *tmp2 = malloc(100);
        strcpy(tmp2, find_parameter(yystack.l_mark[-4].string));
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
        int type = find_type(yystack.l_mark[-4].string);
        fprintf(file, ")%s\n", type == -1 ? "V" : (type == 0 ? "I" : "F"));
     }
break;
case 36:
#line 289 "compiler_hw3.y"
	{err_type = 1; strcpy(err_func_name, yystack.l_mark[0].string);}
break;
case 37:
#line 289 "compiler_hw3.y"
	{err_type = 0;}
break;
case 40:
#line 298 "compiler_hw3.y"
	{
        int type = 0;
        if (strcmp(yystack.l_mark[-1].var.type, "float") == 0) {
            type = 1;
        }
        write_tab();
        if (type == 0){
            fprintf(file, "ireturn\n");
        } else if (type == 1){
            fprintf(file, "freturn\n");
        }
    }
break;
case 41:
#line 310 "compiler_hw3.y"
	{ write_tab(); fprintf(file, "return\n"); }
break;
case 48:
#line 332 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 49:
#line 333 "compiler_hw3.y"
	{
        char *tmp = yystack.l_mark[0].string;
        for(; *tmp != '\0'; ++tmp){
            if (*tmp == ' ' || *tmp == '=' || *tmp == '+' || *tmp == '-' || *tmp == '*' || *tmp == '/' || *tmp == '%'){
                *tmp = '\0';
                break;
            }
        }
        assign_data_type = find_type(yystack.l_mark[0].string);
        assign_id = find_index(yystack.l_mark[0].string);
        write_tab();
        if (assign_data_type == 0){
            fprintf(file, "iload %d\n", assign_id);
        } else {
            fprintf(file, "fload %d\n", assign_id);
        }
    }
break;
case 50:
#line 349 "compiler_hw3.y"
	{
        char *symbol = malloc(3);
        strcpy(symbol, yystack.l_mark[-1].string);
        int right_type;
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            right_type = 0;
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
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
break;
case 51:
#line 412 "compiler_hw3.y"
	{yyval.string = "="; }
break;
case 52:
#line 413 "compiler_hw3.y"
	{yyval.string = "+="; }
break;
case 53:
#line 414 "compiler_hw3.y"
	{yyval.string = "-="; }
break;
case 54:
#line 415 "compiler_hw3.y"
	{yyval.string = "*="; }
break;
case 55:
#line 416 "compiler_hw3.y"
	{yyval.string = "/="; }
break;
case 56:
#line 417 "compiler_hw3.y"
	{yyval.string = "%="; }
break;
case 57:
#line 421 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 59:
#line 426 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 61:
#line 431 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 62:
#line 432 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifeq %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 63:
#line 446 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifne %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 64:
#line 463 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 65:
#line 464 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifgt %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 66:
#line 478 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "iflt %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 67:
#line 492 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifge %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 68:
#line 506 "compiler_hw3.y"
	{
        strcpy(yystack.l_mark[-2].var.type, "bool");
        yyval.var = yystack.l_mark[-2].var;
        write_tab();
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0){
            fprintf(file, "isub\n");
        } else if (strcmp(yystack.l_mark[0].var.type, "float") == 0){
            fprintf(file, "fsub\n");
        }
        write_tab();
        fprintf(file, "ifle %s\n", label_generator());
        write_tab();
        fprintf(file, "goto %s\n", label_generator());
    }
break;
case 69:
#line 523 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 70:
#line 524 "compiler_hw3.y"
	{
        if (strcmp(yystack.l_mark[-2].var.type, "int") == 0 && strcmp(yystack.l_mark[0].var.type, "float") == 0){
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
            strcpy(yystack.l_mark[-2].var.type, "float");
        }
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0 && strcmp(yystack.l_mark[-2].var.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy(yystack.l_mark[0].var.type, "float");
        }
        yyval.var = yystack.l_mark[-2].var;
        write_tab(); 
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0) {
            fprintf(file, "iadd\n"); 
        } else {
            fprintf(file, "fadd\n");
        }
    }
break;
case 71:
#line 551 "compiler_hw3.y"
	{
        if (strcmp(yystack.l_mark[-2].var.type, "int") == 0 && strcmp(yystack.l_mark[0].var.type, "float") == 0){
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
            strcpy(yystack.l_mark[-2].var.type, "float");
        }
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0 && strcmp(yystack.l_mark[-2].var.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy(yystack.l_mark[0].var.type, "float");
        }
        yyval.var = yystack.l_mark[-2].var;
        write_tab(); 
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0) {
            fprintf(file, "isub\n"); 
        } else {
            fprintf(file, "fsub\n");
        }
    }
break;
case 72:
#line 581 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 73:
#line 582 "compiler_hw3.y"
	{
        if (strcmp(yystack.l_mark[-2].var.type, "int") == 0 && strcmp(yystack.l_mark[0].var.type, "float") == 0){
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
            strcpy(yystack.l_mark[-2].var.type, "float");
        }
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0 && strcmp(yystack.l_mark[-2].var.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy(yystack.l_mark[0].var.type, "float");
        }
        yyval.var = yystack.l_mark[-2].var;
        write_tab(); 
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0) {
            fprintf(file, "imul\n"); 
        } else {
            fprintf(file, "fmul\n");
        }
    }
break;
case 74:
#line 610 "compiler_hw3.y"
	{
        if (strcmp(yystack.l_mark[-2].var.type, "int") == 0 && strcmp(yystack.l_mark[0].var.type, "float") == 0){
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
            strcpy(yystack.l_mark[-2].var.type, "float");
        }
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0 && strcmp(yystack.l_mark[-2].var.type, "float") == 0){
            write_tab();
            fprintf(file, "i2f\n");
            strcpy(yystack.l_mark[0].var.type, "float");
        }
        yyval.var = yystack.l_mark[-2].var;
        write_tab(); 
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0) {
            fprintf(file, "idiv\n"); 
        } else {
            fprintf(file, "fdiv\n");
        }
    }
break;
case 75:
#line 637 "compiler_hw3.y"
	{
        yyval.var = yystack.l_mark[-2].var;
        write_tab(); 
        if (strcmp(yystack.l_mark[0].var.type, "int") == 0 && strcmp(yystack.l_mark[-2].var.type, "int") == 0) {
            fprintf(file, "irem\n"); 
        }
    }
break;
case 76:
#line 647 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 80:
#line 654 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 83:
#line 660 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 84:
#line 661 "compiler_hw3.y"
	{ 
        struct variable v;
        char *tmp = yystack.l_mark[0].string;
        for(char *i = tmp; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ' || *i == '=' || *i == ')' || *i == '(') {
                    *i = '\0';
                }
            }
        int id = find_index(yystack.l_mark[0].string);
        int type = find_type(yystack.l_mark[0].string);
        int variable_scope = find_scope(yystack.l_mark[0].string);
        write_tab();
        if (variable_scope == 0){
            if (type == 0){
                fprintf(file, "getstatic compiler_hw3/%s I\n", yystack.l_mark[0].string);
                strcpy(v.type, "int");
            } else if (type == 1){
                fprintf(file, "getstatic compiler_hw3/%s F\n", yystack.l_mark[0].string);
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
        yyval.var = v;
    }
break;
case 85:
#line 692 "compiler_hw3.y"
	{struct variable v; yyval.var = v; }
break;
case 86:
#line 696 "compiler_hw3.y"
	{ 
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, yystack.l_mark[-3].string);
        char *tmp_name = new_node->name;
        for(; *tmp_name != NULL; ++tmp_name){
            if (*tmp_name == ' ' || *tmp_name == '='){
                *tmp_name = NULL;
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "variable");
        strcpy(new_node->d_type, yystack.l_mark[-4].string);
        push(new_node);
        if (scope == 0) {
            char *id_name = yystack.l_mark[-3].string;
            for(char *i = id_name; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ') {
                    *i = '\0';
                }
            }
            if (yystack.l_mark[-4].string == "int"){
                int tmp = (int)yystack.l_mark[-1].var.i_val;
                fprintf(file, ".field public static %s I = %d\n", yystack.l_mark[-3].string, tmp);
            } else if (yystack.l_mark[-4].string == "float") {
                fprintf(file, ".field public static %s F = %f\n", yystack.l_mark[-3].string, yystack.l_mark[-1].var.f_val);
            } else if (yystack.l_mark[-4].string == "bool") {
                int tmp = (int)yystack.l_mark[-1].var.i_val;
                fprintf(file, ".field public static %s Z = %d\n", yystack.l_mark[-3].string, tmp);
            }
        } else {
            write_tab();
            if (yystack.l_mark[-4].string == "int" || yystack.l_mark[-4].string == "bool"){
                int tmp = (int)yystack.l_mark[-1].var.i_val;
                fprintf(file, "ldc %d\n", tmp);
                write_tab();
                fprintf(file, "istore %d\n", new_node->index);
            } else if (yystack.l_mark[-4].string == "float") {
                fprintf(file, "ldc %f\n", yystack.l_mark[-1].var.f_val);
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            }
        }
    }
break;
case 87:
#line 740 "compiler_hw3.y"
	{
        struct node *new_node = malloc(sizeof(*new_node));
        strcpy(new_node->name, yystack.l_mark[-1].string);
        char *tmp_name = new_node->name;
        for(; *tmp_name != '\0'; ++tmp_name){
            if (*tmp_name == ' ' || *tmp_name == ';'){
                *tmp_name = '\0';
                break;
            }
        }
        new_node->scope_level = scope;
        strcpy(new_node->e_type, "variable");
        strcpy(new_node->d_type, yystack.l_mark[-2].string);
        push(new_node);  
        if (scope == 0) {
            char *id_name = yystack.l_mark[-1].string;
            for(char *i = id_name; *i != '\0'; ++i){
                if (*i == ';' || *i == ' ') {
                    *i = '\0';
                }
            }
            if (yystack.l_mark[-2].string == "int"){
                fprintf(file, ".field public static %s I = 0\n", yystack.l_mark[-1].string);
            } else if (yystack.l_mark[-2].string == "float") {
                fprintf(file, ".field public static %s F = 0\n", yystack.l_mark[-1].string);
            } else if (yystack.l_mark[-2].string == "bool") {
                fprintf(file, ".field public static %s Z = 0\n", yystack.l_mark[-1].string);
            }
        } else {
            write_tab();
            if (yystack.l_mark[-2].string == "int" || yystack.l_mark[-2].string == "bool"){
                fprintf(file, "ldc 0\n");
                write_tab();
                fprintf(file, "istore %d\n", new_node->index);
            } else if (yystack.l_mark[-2].string == "float") {
                fprintf(file, "ldc 0\n");
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            } else if (yystack.l_mark[-2].string == "string") {
                fprintf(file, "ldc \"\"\n");
                write_tab();
                fprintf(file, "fstore %d\n", new_node->index);
            }
        }
    }
break;
case 88:
#line 788 "compiler_hw3.y"
	{ yyval.var = yystack.l_mark[0].var; }
break;
case 89:
#line 792 "compiler_hw3.y"
	{ float tmp = (float)yystack.l_mark[0].i_val; struct variable v; v.i_val = tmp; strcpy(v.type, "int"); yyval.var = v; write_tab(); fprintf(file, "ldc %d\n", yystack.l_mark[0].i_val); }
break;
case 90:
#line 793 "compiler_hw3.y"
	{ struct variable v; v.f_val = yystack.l_mark[0].f_val; strcpy(v.type, "float"); yyval.var = v; write_tab(); fprintf(file, "ldc %f\n", yystack.l_mark[0].f_val); }
break;
case 91:
#line 794 "compiler_hw3.y"
	{ }
break;
case 92:
#line 795 "compiler_hw3.y"
	{ struct variable v; v.i_val = 1; strcpy(v.type, "int"); yyval.var = v; write_tab(); fprintf(file, "ldc %d\n", 1); }
break;
case 93:
#line 796 "compiler_hw3.y"
	{ struct variable v; v.i_val = 0; strcpy(v.type, "int"); yyval.var = v; write_tab(); fprintf(file, "ldc %d\n", 0); }
break;
case 94:
#line 800 "compiler_hw3.y"
	{
        char *tmp = yystack.l_mark[-2].string;
        for(; tmp != NULL; ++tmp){
            if (*tmp == ' ' || *tmp == ')' || *tmp == ';'){
                *tmp = NULL;
                break;
            }
        }
        int id = find_index(yystack.l_mark[-2].string);
        int variable_scope = find_scope(yystack.l_mark[-2].string);
        int type = find_type(yystack.l_mark[-2].string);
        write_tab();
        if (variable_scope == 0){
            fprintf(file, "getstatic compiler_hw3/%s %s\n", yystack.l_mark[-2].string, type == 0 ? "I" : "F");
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
break;
case 95:
#line 828 "compiler_hw3.y"
	{
        write_tab();
        fprintf(file, "ldc %d\n", yystack.l_mark[-2].i_val);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(I)V\n");
    }
break;
case 96:
#line 838 "compiler_hw3.y"
	{
        write_tab();
        fprintf(file, "ldc %f\n", yystack.l_mark[-2].f_val);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(F)V\n");
    }
break;
case 97:
#line 848 "compiler_hw3.y"
	{
        write_tab();
        fprintf(file, "ldc \"%s\"\n", yytext);
        write_tab();
        fprintf(file, "getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        write_tab();
        fprintf(file, "swap\n");
        write_tab();
        fprintf(file, "invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
    }
break;
#line 1805 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
