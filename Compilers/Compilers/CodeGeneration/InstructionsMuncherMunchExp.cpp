// Автор: Фролов Николай.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <IRTRee\IRHelpers.h>

using namespace CodeGeneration;

Temp::CTemp CInstructionsMuncher::munchExp( const IRTree::IExp* exp )
{
	if( dynamic_cast<const IRTree::CMem*>( exp ) != 0 ) {
		return munchExpMem( dynamic_cast<const IRTree::CMem*>( exp ) );
	} else if( dynamic_cast<const IRTree::CBinop*>( exp ) != 0 ) {
		return munchExpBinop( dynamic_cast<const IRTree::CBinop*>( exp ) );
	} else if( dynamic_cast<const IRTree::CConst*>( exp ) != 0 ) {
		Temp::CTemp tmp;
		int constValue = dynamic_cast<const IRTree::CConst*>( exp )->value;
		emit( new COper( "mov 'd0, " + std::to_string( constValue ), std::list<Temp::CTemp>( 1, tmp ), std::list<Temp::CTemp>() ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CTemp*>( exp ) != 0 ) {
		return Temp::CTemp( dynamic_cast<const IRTree::CTemp*>( exp )->temp );
	} else {
		assert( false );
		return Temp::CTemp();
	}
}

Temp::CTemp CInstructionsMuncher::munchExpMem( const IRTree::CMem* exp )
{
	if( dynamic_cast<const IRTree::CBinop*>( exp->exp.get() ) != 0 ) {
		return munchExpBinopInMem( dynamic_cast<const IRTree::CBinop*>( exp->exp.get() ) );
	} else {
		// Кладем exp из mem во временную переменную.
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->exp.get() ) ) ) );
		// Кладем framePointer во временную переменную.
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, *frame->FramePointer() ) ) );
		// Кладем во временную переменную значение по заданному адресу.
		Temp::CTemp tmp3;
		std::list<Temp::CTemp> source = std::list<Temp::CTemp>( 1, tmp1 );
		source.push_back( tmp2 );
		emit( new COper( "mov 'd0, ['s0 + 's1]", std::list<Temp::CTemp>( 1, tmp3 ),
			source ) );
		return tmp3;
	}
}

Temp::CTemp CInstructionsMuncher::munchExpBinopInMem( const IRTree::CBinop* exp )
{
	std::string command = "mov";
	std::string binopOperation;
	if( exp->binop == IRTree::B_Plus || exp->binop == IRTree::B_Minus ) {
		binopOperation = IRTree::ToString( exp->binop );
	} else {
		// Если в binop в mem не + и не -, то значит затесалась ошибка.
		assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 && dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		// Если запрашиваем адрес по двум binop от двух констант - то что-то не так.
		assert( false );
		return Temp::CTemp();
	} else if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->right.get() ) ) ) );
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, *frame->FramePointer() ) ) );
		Temp::CTemp tmp3;
		std::list<Temp::CTemp> source = std::list<Temp::CTemp>( 1, tmp2 );
		source.push_back( tmp1 );
		emit( new COper( command + " 'd0, ['s0 + " + std::to_string( leftValue ) + binopOperation + "'s1]",
			std::list<Temp::CTemp>( 1, tmp3 ), source ) );
		return tmp3;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->left.get() ) ) ) );
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, *frame->FramePointer() ) ) );
		Temp::CTemp tmp3;
		std::list<Temp::CTemp> source = std::list<Temp::CTemp>( 1, tmp2 );
		source.push_back( tmp1 );
		emit( new COper( command + " 'd0, ['s0 + 's1 " + binopOperation + std::to_string( rightValue ) + "]",
			std::list<Temp::CTemp>( 1, tmp3 ), source ) );
		return tmp3;
	} else {
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->left.get() ) ) ) );
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, munchExp( exp->right.get() ) ) ) );
		Temp::CTemp tmp3;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp3 ), std::list<Temp::CTemp>( 1, *frame->FramePointer() ) ) );
		Temp::CTemp tmp4;
		std::list<Temp::CTemp> source = std::list<Temp::CTemp>( 1, tmp3 );
		source.push_back( tmp1 );
		source.push_back( tmp2 );
		emit( new COper( command + " 'd0, ['s0 + 's1 " + binopOperation + "'s2]",
			std::list<Temp::CTemp>( 1, tmp4 ), source ) );
		return tmp4;
	}
}

Temp::CTemp CInstructionsMuncher::munchExpBinop( const IRTree::CBinop* exp )
{
	std::string command;
	switch( exp->binop ) {
		case IRTree::B_Plus:
			command = "add";
			break;
		case IRTree::B_Minus:
			command = "sub";
			break;
		case IRTree::B_Mul:
			command = "mul";
			break;
		case IRTree::B_Division:
			command = "div";
			break;
		case IRTree::B_Xor:
			command = "xor";
			break;
		default:
			assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 && dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp tmp;
		emit( new COper( "mov 'd0, " + std::to_string( leftValue ) + "\n", std::list<Temp::CTemp>( 1, tmp ), std::list<Temp::CTemp>() ) );
		emit( new COper( command + " 'd0, " + std::to_string( rightValue ), std::list<Temp::CTemp>( 1, tmp ), std::list<Temp::CTemp>() ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->right.get() ) ) ) );
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, "  + std::to_string( leftValue ), std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>() ) );
		emit( new COper( command + " 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, tmp1 ) ) );
		return tmp2;
	} else if( dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp tmp;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp ), std::list<Temp::CTemp>( 1, munchExp( exp->left.get() ) ) ) );
		emit( new COper( command + " 'd0, " + std::to_string( rightValue ), std::list<Temp::CTemp>( 1, tmp ), std::list<Temp::CTemp>() ) );
		return tmp;
	} else {
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, munchExp( exp->left.get() ) ) ) );
		Temp::CTemp tmp2;
		emit( new COper( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, munchExp( exp->right.get() ) ) ) );
		emit( new COper( command + " 'd0, 's0",	std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, tmp2 ) ) );
		return tmp1;
	}
}