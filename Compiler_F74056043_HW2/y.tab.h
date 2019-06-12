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
extern YYSTYPE yylval;
