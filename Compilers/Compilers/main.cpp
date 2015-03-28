#include <fstream>
#include <iostream>
#include <common.h>
#include <memory>
#include <PrettyPrinterVisitor.h>
#include <SymbolTableConstructor.h>
#include <TypeChecker.h>
#include "IRTree\IRForestBuilder.h"
#include "IRTree\IRTreeToDigraphConverter.h"
#include "IRTreeCallLifter.h"
#include "IRTreeEseqLifter.h"

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

		Translate::CIRForestBuilder irForestBuilder( tableConstructor.symbolTable );
		astRoot->Accept( irForestBuilder );

		/*for( const auto& frame : irForestBuilder.Methods ) {
			// Печатаем деревья для отдельной функции
			IRTree::CIRTreeToDigraphConverter irTreeToDigraphConverter( std::string( "IRTree_" ) 
				+ frame->Name + std::string( ".dot" ) );
			frame->Stm->Accept( irTreeToDigraphConverter );
			irTreeToDigraphConverter.Flush();
		}*/

		IRTree::CIRTreeCallLifter callLifter;
		vector<const Frame::CFrame* > liftedCallMethods;
		for( auto& frame : irForestBuilder.Methods ) {
			frame->Stm->Accept( callLifter );
			Frame::CFrame* tmp = new Frame::CFrame( frame->Name );
			tmp->Stm = callLifter.GetLastStm();
			liftedCallMethods.push_back( tmp );
			callLifter.ReInit();
		}

		vector<const Frame::CFrame*> liftedEseqMethods;
		IRTree::CIRTreeEseqLifter eseqLifter;
		for( auto& frame : liftedCallMethods ) {
			frame->Stm->Accept( eseqLifter );
			Frame::CFrame* tmp = new Frame::CFrame( frame->Name );
			tmp->Stm = eseqLifter.getResultTree();
			liftedEseqMethods.push_back( tmp );
		}

		for( const auto& frame : liftedCallMethods ) {
			// Вывод деревьев с заменой call на спец. конструкцию.
			IRTree::CIRTreeToDigraphConverter irTreeToDigraphConverter( std::string( "IRTree_Eseq_" ) 
				+ frame->Name + std::string( ".dot" ) );
			frame->Stm->Accept( irTreeToDigraphConverter );
			irTreeToDigraphConverter.Flush();
		}

		for( const auto& frame : liftedEseqMethods ) {
			// Вывод деревьев с заменой eseq на спец. конструкцию.
			IRTree::CIRTreeToDigraphConverter irTreeToDigraphConverter( std::string( "IRTree_" ) 
				+ frame->Name + std::string( ".dot" ) );
			frame->Stm->Accept( irTreeToDigraphConverter );
			irTreeToDigraphConverter.Flush();
		}
	}

	return 0;
}