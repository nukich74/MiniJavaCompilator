extern "C" int yyparse();

#include <fstream>
#include <iostream>

int main() {
	while( yyparse() != 0 );
	return 0;
}