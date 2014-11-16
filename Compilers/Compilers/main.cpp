extern "C" int yyparse();

#include <fstream>
#include <iostream>

int main() {
	std::ofstream out( "results.txt" );
	std::streambuf *coutBuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf( out.rdbuf() ); //redirect std::cout to outputFile

	while( yyparse() != 0 );

	out.flush();
	out.close();
	std::cout.rdbuf( coutBuf ); //reset to standard output again
	return 0;
}