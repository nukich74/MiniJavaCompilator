int yyparse( void**, int* );

#include <fstream>
#include <iostream>
#include <common.h>
#include <memory>
#include <PrettyPrinterVisitor.h>
#include <SymbolTableConstructor.h>

int main() {
	void* ptr;
	int hasError = 0;
	while( yyparse( &ptr, &hasError ) != 0 );
	if( hasError == 0 ) {
		std::unique_ptr<CProgram> astRoot( static_cast<CProgram*>( ptr ) );
		CPrettyPrinterVisitor printer;
		astRoot->accept( printer );
		CSymbolTableConstructor tableConstructor;
		astRoot->accept( tableConstructor );
		if( !tableConstructor.errors.errors.empty() ) {
			tableConstructor.errors.WriteErrors();
			return 0;
		}
	}
	return 0;
}