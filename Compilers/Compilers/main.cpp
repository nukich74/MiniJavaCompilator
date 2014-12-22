#include <fstream>
#include <iostream>
#include <common.h>
#include <memory>
#include <PrettyPrinterVisitor.h>
#include <SymbolTableConstructor.h>
#include <TypeChecker.h>
#include "IRTree\IRTreeVisitor.h"
#include "IRTree\IRPrint.h"

int yyparse( std::shared_ptr<CProgram>& astRoot, int* );

int main()
{
	std::shared_ptr<CProgram> astRoot;
	int hasError = 0;
	
	while( yyparse( astRoot, &hasError ) != 0 );

	if( hasError == 0 ) {
		CPrettyPrinterVisitor printer;
		astRoot->Accept( printer );
		
		CSymbolTableConstructor tableConstructor;
		astRoot->Accept( tableConstructor );

		CTypeChecker typeChecker( tableConstructor.symbolTable );
		astRoot->Accept( typeChecker );

		if( tableConstructor.errors.HasErrors() || typeChecker.errors.HasErrors() ) {
			tableConstructor.errors.WriteErrors();
			typeChecker.errors.WriteErrors();
			return 0;
		}

		/*
		Translate::CIRTreeVisitor irTreeVisitor( tableConstructor.symbolTable );
		astRoot->Accept( irTreeVisitor );

		for( const auto& frame : irTreeVisitor.Methods ) {
			// Печатаем деревья для отдельной функции
			//IRTree::CPrinter irPrinter;
			//frame->Stm->Print( irPrinter );
		}
		*/
	}

	return 0;
}