/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>

	int is_string = 0;
	int line_count = 0;
	int comment_line_count = 0;
%}

/* Define regular expression label */

space [ \t]
letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
string ({letter|{space}|{digit})+
number {digit}+
int_number {number}+
float_number {number}+[.]{number}+
quata ["]
cppcomment "//"({letter}|{space}|{digit})*
ccomment "/*"({letter}|{space}|{digit}|[\n*])*"*/"

/* Rules section */
%%

\n	{ ++line_count; }
{cppcomment}	{printf("%s \t C++ Comment\n", yytext);
			++comment_line_count;
			 }
{ccomment}	{ for(int i = 0; *(yytext + i) != '\0'; ++i) {
				if(*(yytext + i) == '\n') {
					++comment_line_count;
					++line_count;
				}
			}
			++comment_line_count;
			printf("%s \t C Comment\n", yytext); }
{quata}	{ if(is_string)
			{
				is_string = 0;
				printf("\t STR_CONST\n%s \t QUOTA\n", yytext);
			}
		else
			{
				is_string = 1;
				printf("%s \t QUOTA\n", yytext); }}
"+" 	{ printf("%s \t ADD\n", yytext); }
" " 	{; }
"-"		{ printf("%s \t SUB\n", yytext); }
"*"		{ printf("%s \t MUL\n", yytext); }
"/"		{ printf("%s \t DIV\n", yytext); }
"%"		{ printf("%s \t MOD\n", yytext); }
"++"	{ printf("%s \t INC\n", yytext); }
"--"	{ printf("%s \t DEC\n", yytext); }
">"		{ printf("%s \t MT\n", yytext); }
"<"		{ printf("%s \t LT\n", yytext); }
"="		{ printf("%s \t ASGN\n", yytext); }
">="	{ printf("%s \t MTE\n", yytext); }
"<="	{ printf("%s \t LTE\n", yytext); }
"=="	{ printf("%s \t EQ\n", yytext); }
"!="	{ printf("%s \t NE\n", yytext); }
"+="	{ printf("%s \t ADDASGN\n", yytext); }
"-="	{ printf("%s \t SUBASGN\n", yytext); }
"*="	{ printf("%s \t MULASGN\n", yytext); }
"/="	{ printf("%s \t DIVASGN\n", yytext); }
"%="	{ printf("%s \t MODASGN\n", yytext); }
"&&"	{ printf("%s \t AND\n", yytext); }
"||"	{ printf("%s \t OR\n", yytext); }
"!"		{ printf("%s \t NOT\n", yytext); }
"("		{ printf("%s \t LB\n", yytext); }
")"		{ printf("%s \t RB\n", yytext); }
"{"		{ printf("%s \t LCB\n", yytext); }
"}"		{ printf("%s \t RCB\n", yytext); }
"int"	{ printf("%s \t INT\n", yytext); }
"float"	{ printf("%s \t FLOAT\n", yytext); }
"if"	{ printf("%s \t IF\n", yytext); }
"else"	{ printf("%s \t ELSE\n", yytext); }
"for"	{ printf("%s \t FOR\n", yytext); }
"while"	{ printf("%s \t WHILE\n", yytext); }
"void"	{ printf("%s \t VOID\n", yytext); }
"string"	{ printf("%s \t STRING\n", yytext); }
"bool"	{ printf("%s \t BOOL\n", yytext); }
"true"	{ printf("%s \t TRUE\n", yytext); }
"false"	{ printf("%s \t FALSE\n", yytext); }
"return"	{ printf("%s \t RET\n", yytext); }
"continue"	{ printf("%s \t CONT\n", yytext); }
"break"	{ printf("%s \t BREAK\n", yytext); }
"["		{ printf("%s \t LSB\n", yytext); }
"]"		{ printf("%s \t RSB\n", yytext); }
","		{ printf("%s \t COMMA\n", yytext); }
";"		{ printf("%s \t SEMICOLON\n", yytext); }
"print" { printf("%s \t PRINT\n", yytext); }
{id}	{ if(is_string)
			{ printf("%s ", yytext); }
		else
			{ printf("%s \t ID\n", yytext); } }
{int_number}	{ printf("%s \t I_CONST\n", yytext); }
{float_number}	{ printf("%s \t F_CONST\n", yytext); }

%%

/*	C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc,char *argv[])
{
	yyin = fopen(argv[1],"r");
	yylex();
	printf("\nParse over, the line number is %d.\n\n", line_count);
	printf("comment: %d lines\n\n", comment_line_count);

	return 0;
}
