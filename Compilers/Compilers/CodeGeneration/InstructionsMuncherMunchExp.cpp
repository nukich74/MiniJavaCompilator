// Автор: Фролов Николай.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <IRTRee\IRHelpers.h>

using namespace CodeGeneration;

Temp::CTemp* CInstructionsMuncher::munchExp( const IRTree::IExp* exp )
{
	if( dynamic_cast<const IRTree::CMem*>( exp ) != 0 ) {
		return munchExpMem( dynamic_cast<const IRTree::CMem*>( exp ) );
	} else if( dynamic_cast<const IRTree::CBinop*>( exp ) != 0 ) {
		return munchExpBinop( dynamic_cast<const IRTree::CBinop*>( exp ) );
	} else if( dynamic_cast<const IRTree::CConst*>( exp ) != 0 ) {
		Temp::CTemp* tmp = new Temp::CTemp();
		int constValue = dynamic_cast<const IRTree::CConst*>( exp )->value;
		emit( new COper( "MOVE d0 <- " + std::to_string( constValue ) + "\n", new std::list<Temp::CTemp*>( 1, tmp ), 0 ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CTemp*>( exp ) != 0 ) {
		return new Temp::CTemp( dynamic_cast<const IRTree::CTemp*>( exp )->temp );
	} else {
		assert( false );
		return 0;
	}
}

Temp::CTemp* CInstructionsMuncher::munchExpMem( const IRTree::CMem* exp )
{
	if( dynamic_cast<const IRTree::CBinop*>( exp->exp.get() ) != 0 ) {
		return munchExpBinopInMem( dynamic_cast<const IRTree::CBinop*>( exp->exp.get() ) );
	} else if( dynamic_cast<const IRTree::CConst*>( exp->exp.get() ) != 0 ) {
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( "MOVE d0 <- M[i]\n", new std::list<Temp::CTemp*>( 1, tmp ), 0 ) );
		return tmp;
	} else {
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( "MOVE d0 <- M[s0]\n", new std::list<Temp::CTemp*>( 1, tmp ),
			new std::list<Temp::CTemp*>( 1, munchExp( exp->exp.get() ) ) ) );
		return tmp;
	}
}

Temp::CTemp* CInstructionsMuncher::munchExpBinopInMem( const IRTree::CBinop* exp )
{
	std::string command = "MOVE";
	std::string binopOperation;
	switch( exp->binop ) {
		case IRTree::B_Plus:
			binopOperation = "+";
			break;
		case IRTree::B_Minus:
			binopOperation = "-";
			break;
		default:
			// смещение только по + и -.
			assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 && dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- M[" + std::to_string( leftValue ) + binopOperation + std::to_string( rightValue ) + "]\n",
			new std::list<Temp::CTemp*>( 1, tmp ), 0 ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- M[" + std::to_string( leftValue ) + binopOperation + "s0]\n",
			new std::list<Temp::CTemp*>( 1, tmp ), new std::list<Temp::CTemp*>( 1, munchExp( exp->right.get() ) ) ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- M[s0"+ binopOperation + std::to_string( rightValue ) + "]\n",
			new std::list<Temp::CTemp*>( 1, tmp ), new std::list<Temp::CTemp*>( 1, munchExp( exp->left.get() ) ) ) );
		return tmp;
	} else {
		Temp::CTemp* tmp = new Temp::CTemp();
		std::list<Temp::CTemp*>* src = new std::list<Temp::CTemp*>( 1, munchExp( exp->left.get() ) );
		src->push_back( munchExp( exp->right.get() ) ); 
		emit( new COper( command + " d0 <- M[s0" + binopOperation + "s1]\n",
			new std::list<Temp::CTemp*>( 1, tmp ), src ) );
		return tmp;
	}
}

Temp::CTemp* CInstructionsMuncher::munchExpBinop( const IRTree::CBinop* exp )
{
	std::string command;
	std::string binopOperation;
	switch( exp->binop ) {
		case IRTree::B_Plus:
			command = "ADD";
			binopOperation = "+";
			break;
		case IRTree::B_Minus:
			command = "SUB";
			binopOperation = "-";
			break;
		case IRTree::B_Mul:
			command = "MUL";
			binopOperation = "*";
			break;
		case IRTree::B_Division:
			command = "DIV";
			binopOperation = "/";
			break;
		default:
			// смещение только по + и -.
			assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 && dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- " + std::to_string( leftValue ) + binopOperation + std::to_string( rightValue ) + "\n",
			new std::list<Temp::CTemp*>( 1, tmp ), 0 ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- " + std::to_string( leftValue ) + binopOperation + "s0\n",
			new std::list<Temp::CTemp*>( 1, tmp ), new std::list<Temp::CTemp*>( 1, munchExp( exp->right.get() ) ) ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( command + " d0 <- s0"+ binopOperation + std::to_string( rightValue ) + "\n",
			new std::list<Temp::CTemp*>( 1, tmp ), new std::list<Temp::CTemp*>( 1, munchExp( exp->left.get() ) ) ) );
		return tmp;
	} else {
		Temp::CTemp* tmp = new Temp::CTemp();
		std::list<Temp::CTemp*>* src = new std::list<Temp::CTemp*>( 1, munchExp( exp->left.get() ) );
		src->push_back( munchExp( exp->right.get() ) ); 
		emit( new COper( command + " d0 <- s0" + binopOperation + "s1\n",
			new std::list<Temp::CTemp*>( 1, tmp ), src ) );
		return tmp;
	}
}