%option noyywrap

%{
#include <iostream>
#include <math.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]*		{ std::cout << "Identifier "; }

[0-9]+ 				{ std::cout << "Integer "; }

"/*"((("*"[^/])?)|[^*])*"*/"	{}

"//"[^"\n"]+			{}

["&&""+""-""*"]			{ std::cout << "BinOperator "; }

[\t\r\n\ ]+			{}

%%
extern int YYText();

int main(int argc, char ** argv)
{
	while( yylex() != 0 );
	return 0;
}