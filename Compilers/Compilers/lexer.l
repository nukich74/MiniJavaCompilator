%option noyywrap

%{
#include <iostream>
#include <math.h>
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
%}

%%
"class"				{ return CLASS; }

"public"			{ return PUBLIC; }

"static" 			{ return STATIC; }

"void"				{ return VOID; }

"main"				{ return MAIN; }

"String"			{ return STRING; }

"return"			{ return RETURN; }

"int"				{ return INT; }

"boolean"			{ return BOOLEAN; }

"else"				{ return ELSE; }

"if"				{ return IF; }

"while"				{ return WHILE; }

"System.out.println"		{ return SYSTEM_OUT_PRINTLN; }

"length"			{ return LENGTH; }

"true"				{ return TRUE; }

"false"				{ return FALSE; }

"new"				{ return NEW; }

"this"				{ return THIS; }

[a-zA-Z][a-zA-Z0-9]*		{ return ID; }

[0-9]+ 				{ yylval.ival = atoi(yytext); return INTEGER_LITERAL;}

"/*"((("*"[^/])?)|[^*])*"*/"	{}

"//"[^"\n"]+			{}

[\t\r\n\ ]+			{}

%%
extern int YYText();