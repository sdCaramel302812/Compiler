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

#line 3 "compiler_hw2.y"
#include <stdio.h>
extern int yylineno;
extern int yylex();
extern char* yytext;    /*Get current token from lex*/
extern char buf[256];   /*Get current code line from lex*/

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


#line 53 "compiler_hw2.y"
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
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 78 "y.tab.c"

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
#define MTE 266
#define LTE 267
#define EQ 268
#define NE 269
#define ADDASGN 270
#define SUBASGN 271
#define MULASGN 272
#define DIVASGN 273
#define MODASGN 274
#define AND 275
#define OR 276
#define NOT 277
#define I_CONST 278
#define F_CONST 279
#define STR_CONST 280
#define TRUE 281
#define FALSE 282
#define VOID 283
#define INT 284
#define FLOAT 285
#define BOOL 286
#define STRING 287
#define ID 288
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    6,    6,    7,    7,    7,    7,    5,    4,
    4,    3,    2,    2,    2,    2,    2,   10,    8,    8,
    9,    9,   11,   11,    1,    1,    1,    1,    1,    1,
    1,   19,   18,   21,   18,   20,   20,   15,   14,   13,
   17,   17,   23,   23,   24,   24,   24,   24,   24,   24,
   22,   22,   25,   25,   26,   26,   26,   27,   27,   27,
   27,   27,   28,   28,   28,   29,   29,   29,   29,   30,
   30,   30,   30,   31,   31,   31,   32,   32,   12,   12,
   34,   33,   33,   33,   33,   33,   35,   16,   16,
};
static const YYINT yylen[] = {                            2,
    2,    1,    1,    1,    6,    5,    6,    5,    1,    3,
    1,    2,    1,    1,    1,    1,    1,    0,    4,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    0,    6,    0,    5,    3,    1,    3,    2,    5,
    5,    7,    1,    3,    1,    1,    1,    1,    1,    1,
    1,    3,    1,    3,    1,    3,    3,    1,    3,    3,
    3,    3,    1,    3,    3,    1,    3,    3,    3,    1,
    2,    2,    2,    1,    2,    2,    1,    1,    5,    3,
    1,    1,    1,    3,    1,    1,    0,    6,    7,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,   82,   83,   85,
   86,   17,   13,   14,   15,   16,    0,    0,    0,    4,
    0,    2,    3,   25,   26,   27,   28,   29,   30,   31,
    0,    0,    0,    0,    0,    0,    0,   66,    0,   74,
   77,    0,    0,    0,   78,    0,   71,   72,   73,   46,
   47,   48,   49,   50,   45,    0,    0,    0,    0,    1,
    0,    0,   39,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   75,   76,   87,    0,    0,
    0,    0,   38,    0,    0,    0,   84,   80,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   67,   68,   69,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   11,    0,    0,    0,    0,    0,    0,    0,
   40,    0,    0,   35,    8,    6,   12,    0,    0,   79,
   88,    0,   20,    0,    0,   33,    0,    7,    5,   10,
   89,   24,    0,    0,   22,   23,   42,    0,   19,   21,
};
static const YYINT yydgoto[] = {                         19,
   20,   21,  113,  114,    0,   22,   23,  120,  144,  134,
  145,   24,   25,   26,   27,   28,   29,   30,   56,  108,
   57,   31,   32,   58,   33,   34,   35,   36,   37,   38,
   39,   40,   41,  116,  104,
};
static const YYINT yysindex[] = {                        33,
   21,   29,   30,   90,   90,   90,   90,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -52, -238,   33,    0,
 -217,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -204, -187, -199, -242,    6,  -23,  -14,    0, -234,    0,
    0,  -32,   98,   98,    0, -244,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   39,   40,   90,   43,    0,
  -37,   90,    0,   90,   90,   90,   90,   90,   90,   90,
   90,   90,   90,   90,   90,    0,    0,    0, -195,  -52,
   45,   46,    0,   90,   48, -204,    0,    0,  -16,   90,
 -199, -242,    6,    6,  -23,  -23,  -23,  -23,  -14,  -14,
    0,    0,    0,   49,   58,  -30,  -30,    8, -204, -167,
 -117, -192,    0,   10, -204, -165, -164,   59,  -24, -157,
    0, -159,   90,    0,    0,    0,    0, -116, -239,    0,
    0, -158,    0,   33,  -30,    0, -204,    0,    0,    0,
    0,    0, -183,  -34,    0,    0,    0,  -57,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  123,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -36,    0,   -1,  108,  260,  233,  172,    0,  134,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  150,
    0,    0,    0,    0,    0,  -29,    0,    0,    0,    0,
   37,  145,  291,  316,  265,  367,  389,  412,  195,  296,
    0,    0,    0,    0,    0,    0,    0,    0,   12,    0,
    0,    0,    0,    0, -156,    0,    0,    0,   65,    1,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   16,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
 -123,  -79,  -22,    0,    0,   89,    0,  -94,    0,    0,
  -35, -115,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    4,   15,    0,   50,   47,   -2,  -31,    2,    9,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 688
static const YYINT yytable[] = {                         18,
   41,   79,   89,   90,   43,  119,  119,   46,   55,  112,
  142,   44,  121,   47,   48,   49,  126,   83,  146,   71,
  142,   72,   75,   90,  111,   65,   66,   73,  146,   76,
   77,   62,   74,  139,   41,   95,   96,   97,   98,   51,
  147,   59,   51,   12,   13,   14,   15,   16,  122,  112,
  128,  123,   37,  129,  143,   37,   36,   81,   82,   36,
   42,   86,   93,   94,  143,   70,   18,   69,   43,   44,
   61,   62,   99,  100,   63,   64,   87,   52,   84,   85,
   52,  101,  102,  103,  105,  106,  107,  109,  110,  117,
  149,  118,  119,  115,  124,  127,  130,  131,   18,  132,
  133,  135,  136,  141,  148,   81,  140,   60,  150,    0,
   92,   91,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   18,    0,   41,  137,    0,    0,    0,
    0,   18,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  125,  138,    0,    0,   53,    0,
    0,   53,    0,    0,    0,    0,    0,    0,    0,   78,
    0,    0,   32,    0,   78,   78,    0,   78,    0,   78,
   70,    0,    0,    0,   70,   70,   70,   70,   70,    0,
   70,    0,   78,    0,   78,   54,   78,    0,   54,    0,
   78,   78,   78,   70,   78,   70,   78,    0,    0,    0,
    0,    0,    0,    0,   88,    0,    0,    0,    0,   78,
    0,   78,   63,    0,   63,   63,   63,   50,   51,   52,
   53,   54,    1,    2,   88,   43,    3,    0,    4,    5,
    6,   63,   44,   63,    0,   64,    0,   64,   64,   64,
    0,    0,    7,    8,    9,    0,   10,   11,   12,   13,
   14,   15,   16,   17,   64,   78,   64,   41,   41,    0,
   51,   41,    0,   41,   41,   41,   12,   13,   14,   15,
   16,   67,   68,   58,   51,    0,   58,   41,   41,   41,
    0,   41,   41,   41,   41,   41,   41,   41,   41,    1,
    2,    0,   58,    3,   58,    4,    5,    6,   52,    0,
   55,    0,    0,   55,    0,   61,    0,    0,   61,    7,
    8,    9,   52,   10,   11,   12,   13,   14,   15,   16,
   17,   18,   18,    0,   61,   18,   61,   18,   18,   18,
    0,   56,    0,    0,   56,    0,   65,    0,   65,   65,
   65,   18,   18,   18,    0,   18,   18,   18,   18,   18,
   18,   18,   18,    5,    6,   65,   57,   65,    0,   57,
    0,    5,    6,    0,    0,    0,    7,    8,    9,   53,
   10,   11,    0,    0,    7,    8,    9,   45,   10,   11,
    0,    0,   53,   53,   78,   80,   78,   78,   78,   78,
   78,   78,    0,    0,    0,   70,    0,   78,   78,   70,
   70,   70,   70,    0,    0,    0,   54,   62,   70,   70,
   62,    0,    0,   78,   78,   78,   78,   78,   78,   54,
   54,    0,    0,    0,   78,   78,   62,    0,   62,   59,
    0,    0,   59,   63,    0,    0,    0,   63,   63,   63,
   63,    0,    0,    0,    0,    0,   63,   63,   59,    0,
   59,    0,   60,    0,    0,   60,   64,    0,    0,    0,
   64,   64,   64,   64,    0,    0,    0,    0,    0,   64,
   64,   60,    0,   60,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   58,    0,    0,    0,   58,   58,
   58,   58,    0,    0,    0,    0,    0,   58,   58,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   55,    0,    0,    0,    0,   61,   55,   55,    0,
   61,   61,   61,   61,   55,   55,    0,    0,    0,   61,
   61,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   56,    0,    0,    0,    0,   65,   56,   56,
    0,   65,   65,   65,   65,   56,   56,    0,    0,    0,
   65,   65,    0,    0,    0,    0,    0,   57,    0,    0,
    0,    0,    0,   57,   57,    0,    0,    0,    0,    0,
   57,   57,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   62,    0,
    0,    0,   62,   62,   62,   62,    0,    0,    0,    0,
    0,   62,   62,    0,    0,    0,    0,    0,    0,    0,
   59,    0,    0,    0,   59,   59,   59,   59,    0,    0,
    0,    0,    0,   59,   59,    0,    0,    0,    0,    0,
    0,    0,    0,   60,    0,    0,    0,   60,   60,   60,
   60,    0,    0,    0,    0,    0,   60,   60,
};
static const YYINT yycheck[] = {                         34,
    0,   34,   40,   61,   41,  123,  123,    4,   61,   89,
  134,   41,  107,    5,    6,    7,  111,  262,  134,   43,
  144,   45,   37,   61,   41,  268,  269,   42,  144,  264,
  265,  276,   47,  128,   34,   67,   68,   69,   70,   41,
  135,  280,   44,  283,  284,  285,  286,  287,   41,  129,
   41,   44,   41,   44,  134,   44,   41,   43,   44,   44,
   40,   58,   65,   66,  144,   60,   34,   62,   40,   40,
  288,  276,   71,   72,  262,  275,   34,   41,   40,   40,
   44,   73,   74,   75,  280,   41,   41,   84,   41,   41,
  125,   34,  123,   90,  262,  288,  262,  262,   34,   41,
  125,  259,  262,  262,  288,  262,  129,   19,  144,   -1,
   64,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   34,   -1,  125,  123,   -1,   -1,   -1,
   -1,   34,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  262,  262,   -1,   -1,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   37,
   -1,   -1,   40,   -1,   42,   43,   -1,   45,   -1,   47,
   37,   -1,   -1,   -1,   41,   42,   43,   44,   45,   -1,
   47,   -1,   60,   -1,   62,   41,   37,   -1,   44,   -1,
   41,   42,   43,   60,   45,   62,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  262,   -1,   -1,   -1,   -1,   60,
   -1,   62,   41,   -1,   43,   44,   45,  270,  271,  272,
  273,  274,  257,  258,  262,  262,  261,   -1,  263,  264,
  265,   60,  262,   62,   -1,   41,   -1,   43,   44,   45,
   -1,   -1,  277,  278,  279,   -1,  281,  282,  283,  284,
  285,  286,  287,  288,   60,  288,   62,  257,  258,   -1,
  262,  261,   -1,  263,  264,  265,  283,  284,  285,  286,
  287,  266,  267,   41,  276,   -1,   44,  277,  278,  279,
   -1,  281,  282,  283,  284,  285,  286,  287,  288,  257,
  258,   -1,   60,  261,   62,  263,  264,  265,  262,   -1,
   41,   -1,   -1,   44,   -1,   41,   -1,   -1,   44,  277,
  278,  279,  276,  281,  282,  283,  284,  285,  286,  287,
  288,  257,  258,   -1,   60,  261,   62,  263,  264,  265,
   -1,   41,   -1,   -1,   44,   -1,   41,   -1,   43,   44,
   45,  277,  278,  279,   -1,  281,  282,  283,  284,  285,
  286,  287,  288,  264,  265,   60,   41,   62,   -1,   44,
   -1,  264,  265,   -1,   -1,   -1,  277,  278,  279,  262,
  281,  282,   -1,   -1,  277,  278,  279,  288,  281,  282,
   -1,   -1,  275,  276,  262,  288,  264,  265,  266,  267,
  268,  269,   -1,   -1,   -1,  262,   -1,  275,  276,  266,
  267,  268,  269,   -1,   -1,   -1,  262,   41,  275,  276,
   44,   -1,   -1,  264,  265,  266,  267,  268,  269,  275,
  276,   -1,   -1,   -1,  275,  276,   60,   -1,   62,   41,
   -1,   -1,   44,  262,   -1,   -1,   -1,  266,  267,  268,
  269,   -1,   -1,   -1,   -1,   -1,  275,  276,   60,   -1,
   62,   -1,   41,   -1,   -1,   44,  262,   -1,   -1,   -1,
  266,  267,  268,  269,   -1,   -1,   -1,   -1,   -1,  275,
  276,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  262,   -1,   -1,   -1,  266,  267,
  268,  269,   -1,   -1,   -1,   -1,   -1,  275,  276,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  262,   -1,   -1,   -1,   -1,  262,  268,  269,   -1,
  266,  267,  268,  269,  275,  276,   -1,   -1,   -1,  275,
  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  262,   -1,   -1,   -1,   -1,  262,  268,  269,
   -1,  266,  267,  268,  269,  275,  276,   -1,   -1,   -1,
  275,  276,   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,
   -1,   -1,   -1,  268,  269,   -1,   -1,   -1,   -1,   -1,
  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  262,   -1,
   -1,   -1,  266,  267,  268,  269,   -1,   -1,   -1,   -1,
   -1,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  262,   -1,   -1,   -1,  266,  267,  268,  269,   -1,   -1,
   -1,   -1,   -1,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,   -1,   -1,   -1,  266,  267,  268,
  269,   -1,   -1,   -1,   -1,   -1,  275,  276,
};
#define YYFINAL 19
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 288
#define YYUNDFTOKEN 326
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'\"'",0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,0,0,"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,
"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,"PRINT","IF","ELSE","FOR","WHILE","SEMICOLON",
"RETURN","INC","DEC","MTE","LTE","EQ","NE","ADDASGN","SUBASGN","MULASGN",
"DIVASGN","MODASGN","AND","OR","NOT","I_CONST","F_CONST","STR_CONST","TRUE",
"FALSE","VOID","INT","FLOAT","BOOL","STRING","ID",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : program transition",
"program : transition",
"transition : func",
"transition : stat",
"func : type ID '(' argument_list ')' compound_stat",
"func : type ID '(' ')' compound_stat",
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
"$$1 :",
"compound_stat : '{' $$1 block_list '}'",
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
"stat : func_call",
"$$2 :",
"func_call : ID $$2 '(' para_list ')' SEMICOLON",
"$$3 :",
"func_call : ID $$3 '(' ')' SEMICOLON",
"para_list : para_list ',' or_expression",
"para_list : or_expression",
"return_stat : RETURN or_expression SEMICOLON",
"expression_stat : expression SEMICOLON",
"loop : WHILE '(' expression ')' compound_stat",
"select : IF '(' expression ')' compound_stat",
"select : IF '(' expression ')' compound_stat ELSE compound_stat",
"expression : or_expression",
"expression : ID assign_symbol or_expression",
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
"multi_expression : multi_expression '%' unary_expression",
"unary_expression : postfix_expression",
"unary_expression : INC unary_expression",
"unary_expression : DEC unary_expression",
"unary_expression : NOT unary_expression",
"postfix_expression : simple_expression",
"postfix_expression : postfix_expression INC",
"postfix_expression : postfix_expression DEC",
"simple_expression : const",
"simple_expression : ID",
"declaration : type ID '=' initialzer SEMICOLON",
"declaration : type ID SEMICOLON",
"initialzer : or_expression",
"const : I_CONST",
"const : F_CONST",
"const : '\"' STR_CONST '\"'",
"const : TRUE",
"const : FALSE",
"$$4 :",
"print_func : PRINT '(' ID $$4 ')' SEMICOLON",
"print_func : PRINT '(' '\"' STR_CONST '\"' ')' SEMICOLON",

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
#line 388 "compiler_hw2.y"

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
#line 686 "y.tab.c"

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
#line 98 "compiler_hw2.y"
	{ struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, yystack.l_mark[-4].string);
                char *tmp = new_node->name;
                for(; tmp != NULL; ++tmp){
                    if (*tmp == ' ' || *tmp == '('){
                        *tmp = NULL;
                        break;
                    }
                }
                new_node->scope_level = scope;
                strcpy(new_node->e_type, "function");
                strcpy(new_node->d_type, yystack.l_mark[-5].string);
                strcpy(new_node->parameter, yystack.l_mark[-2].string);
                push(new_node);
             }
break;
case 6:
#line 113 "compiler_hw2.y"
	{ struct node *new_node = malloc(sizeof(*new_node));
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
                strcpy(new_node->parameter, "");
                push(new_node);
             }
break;
case 7:
#line 128 "compiler_hw2.y"
	{ char *tmp = yystack.l_mark[-2].string;
                pop();
                for(;*tmp != '\0'; ++tmp){
                    if(*tmp == ','){
                        pop();
                    }
                } }
break;
case 9:
#line 139 "compiler_hw2.y"
	{ char *tmp = malloc(30); strcpy(tmp, yystack.l_mark[0].string); yyval.string = tmp; }
break;
case 10:
#line 143 "compiler_hw2.y"
	{ char *tmp = malloc(sizeof(yystack.l_mark[-2].string) + sizeof(yystack.l_mark[0].string));
                strcat(tmp, yystack.l_mark[-2].string);
                strcat(tmp, ", ");
                strcat(tmp, yystack.l_mark[0].string);
                yyval.string = tmp; }
break;
case 11:
#line 148 "compiler_hw2.y"
	{ char *tmp = malloc(sizeof(yystack.l_mark[0].string + 1));
                strcpy(tmp, yystack.l_mark[0].string);
                yyval.string = tmp; }
break;
case 12:
#line 154 "compiler_hw2.y"
	{ struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, yystack.l_mark[0].string);
                new_node->scope_level = scope + 1;
                strcpy(new_node->e_type, "parameter");
                strcpy(new_node->d_type, yystack.l_mark[-1].string);
                push(new_node);
                yyval.string = yystack.l_mark[-1].string;
             }
break;
case 13:
#line 166 "compiler_hw2.y"
	{ yyval.string = "int"; }
break;
case 14:
#line 167 "compiler_hw2.y"
	{ yyval.string = "float"; }
break;
case 15:
#line 168 "compiler_hw2.y"
	{ yyval.string = "bool"; }
break;
case 16:
#line 169 "compiler_hw2.y"
	{ yyval.string = "string"; }
break;
case 17:
#line 170 "compiler_hw2.y"
	{ yyval.string = "void"; }
break;
case 18:
#line 174 "compiler_hw2.y"
	{ scope += 1; }
break;
case 19:
#line 174 "compiler_hw2.y"
	{ scope -= 1; if(back()->scope_level > scope){ print_at_lex=1; } }
break;
case 32:
#line 199 "compiler_hw2.y"
	{err_type = 1; strcpy(err_func_name, yystack.l_mark[0].string);}
break;
case 33:
#line 199 "compiler_hw2.y"
	{err_type = 0; }
break;
case 34:
#line 200 "compiler_hw2.y"
	{err_type = 1; strcpy(err_func_name, yystack.l_mark[0].string);}
break;
case 35:
#line 200 "compiler_hw2.y"
	{err_type = 0;}
break;
case 78:
#line 289 "compiler_hw2.y"
	{struct node *tmp = symbol_table->next;
        int nothing = 0;
        char cmp_text[30];
        strcpy(cmp_text, yystack.l_mark[0].string);
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
break;
case 79:
#line 317 "compiler_hw2.y"
	{ struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, yystack.l_mark[-3].string);
                char *tmp = new_node->name;
                for(; tmp != NULL; ++tmp){
                    if (*tmp == ' ' || *tmp == '='){
                        *tmp = NULL;
                        break;
                    }
                }
                new_node->scope_level = scope;
                strcpy(new_node->e_type, "variable");
                strcpy(new_node->d_type, yystack.l_mark[-4].string);
                push(new_node);
             }
break;
case 80:
#line 331 "compiler_hw2.y"
	{ struct node *new_node = malloc(sizeof(*new_node));
                strcpy(new_node->name, yystack.l_mark[-1].string);
                char *tmp = new_node->name;
                for(; tmp != NULL; ++tmp){
                    if (*tmp == ' ' || *tmp == ';'){
                        *tmp = NULL;
                        break;
                    }
                }
                new_node->scope_level = scope;
                strcpy(new_node->e_type, "variable");
                strcpy(new_node->d_type, yystack.l_mark[-2].string);
                push(new_node);
             }
break;
case 87:
#line 360 "compiler_hw2.y"
	{struct node *tmp = symbol_table->next;
        int nothing = 0;
        char cmp_text[30];
        strcpy(cmp_text, yystack.l_mark[0].string);
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
break;
#line 1097 "y.tab.c"
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
