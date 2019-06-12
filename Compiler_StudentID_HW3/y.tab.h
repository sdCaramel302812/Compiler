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
extern YYSTYPE yylval;
