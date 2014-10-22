#include "parser.tab.h"

extern "C" int yylex();

int main(int argc, char ** argv)
{
	while( yylex() != 0 );
	return 0;
}