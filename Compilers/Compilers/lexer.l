%option noyywrap

%{
#include <iostream>
#include <cmath>
#include <cstring>
#include "parser.tab.hpp"
#define YY_DECL extern "C" int yylex()
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}
%option yylineno

%%
"class"				{ return CLASS; }

"extends"			{ return EXTENDS; }

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

[a-zA-Z][a-zA-Z0-9]*		{ strcpy_s( yylval.sval, yytext ); return ID; }

[0-9]+ 				{ yylval.ival = atoi(yytext); return INTEGER_LITERAL; }

"/*"((("*"[^/])?)|[^*])*"*/"	{}

"//"[^"\n"]+			{}

[\t\r\n\ ]+			{}

[\[\]\)\(\{\}\;\/\*\-\+\<\=\,\.]		{ return yytext[0]; }

"&&"					{ return yytext[0]; }

.						{}

%%
extern int YYText();