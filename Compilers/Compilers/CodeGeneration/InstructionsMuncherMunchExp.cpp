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
	} else if( dynamic_cast<const IRTree::CCall*>( exp ) != 0 ) {
		return munchExpCall( dynamic_cast<const IRTree::CCall*>( exp ) );
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
	if( exp->binop == IRTree::B_Plus || exp->binop == IRTree::B_Minus || exp->binop == IRTree::B_Mul ) {
		binopOperation = IRTree::ToString( exp->binop );
	} else {
		// Если в binop в mem не +, не * и не -, то значит затесалась ошибка.
		assert( false );
	}
	if( dynamic_cast<const IRTree::CConst*>( exp->left.get() ) != 0 && dynamic_cast<const IRTree::CConst*>( exp->right.get() ) != 0 ) {
		int leftValue = dynamic_cast<const IRTree::CConst*>( exp->left.get() )->value;
		int rightValue = dynamic_cast<const IRTree::CConst*>( exp->right.get() )->value;
		Temp::CTemp tmp1;
		emit( new COper( "mov 'd0, " + std::to_string( rightValue ), std::list<Temp::CTemp>( 1, tmp1 ), std::list<Temp::CTemp>( 1, *frame->FramePointer() ) ) );
		Temp::CTemp tmp2;
		emit( new COper( command + " 'd0, ['s0 + " + std::to_string( leftValue ) + binopOperation + std::to_string( rightValue ) + "]",
			std::list<Temp::CTemp>( 1, tmp2 ), std::list<Temp::CTemp>( 1, tmp1 ) ) );
		return tmp2;
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
			return munchExpBinopMul( exp );
		case IRTree::B_Division:
			command = "div";
			break;
		case IRTree::B_Xor:
			command = "xor";
			break;
		case IRTree::B_Less:
			return munchExpBinopLess( exp );
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

Temp::CTemp CInstructionsMuncher::munchExpBinopMul( const IRTree::CBinop* exp )
{
	return Temp::CTemp();
}

Temp::CTemp CInstructionsMuncher::munchExpBinopLess( const IRTree::CBinop* exp )
{
	return Temp::CTemp();
}

Temp::CTemp CInstructionsMuncher::munchExpCall( const IRTree::CCall* exp )
{
	const IRTree::CName* functionName = dynamic_cast<const IRTree::CName*>( exp->func.get() );
	if( functionName == 0 ) {
		assert( false );
	}
	std::list<Temp::CTemp> source = munchArgs( exp->args );
	emit( new COper( "call " + functionName->label->Name(), std::list<Temp::CTemp>(), source ) );
	return Temp::CTemp();
}

std::list<Temp::CTemp> CInstructionsMuncher::munchArgs( const IRTree::CExpList exp )
{
	std::list<const IRTree::IExp*> args;
	IRTree::CExpList tmp = exp;
	while( tmp.tail.get() != 0 ) {
		args.push_back( tmp.head.get() );
	}
	std::list<Temp::CTemp> argsTempList;
	for( auto iter = args.rbegin(); iter != args.rend(); ++iter ) {
		Temp::CTemp tmpArg;
		emit( new COper( "mov 'd0 's0", std::list<Temp::CTemp>( 1, tmpArg ), std::list<Temp::CTemp>( 1, munchExp( *iter ) ) ) );
		emit( new COper( "push 's0" , std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, tmpArg ) ) );
		argsTempList.push_front( tmpArg );
	}
	return argsTempList;
}