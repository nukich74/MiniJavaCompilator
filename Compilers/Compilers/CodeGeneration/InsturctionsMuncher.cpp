// Автор: Николай Фролов.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <list>

using namespace CodeGeneration;

void CInstructionsMuncher::CodeGen()
{
	for( auto& stm : reorderedStmList ) {
		munchStm( stm.get() );
	}
}

void CInstructionsMuncher::munchStm( const IRTree::IStm* stm )
{
	// MOVE(...)
	const IRTree::CMove* asMove = dynamic_cast<const IRTree::CMove*>(stm);
	if( asMove != 0 ) {
		return munchMove( asMove->dst.get(), asMove->src.get() );
	}

	// Seq
	const IRTree::CSeq* asSeq = dynamic_cast< const IRTree::CSeq* >(stm);
	if( asSeq != nullptr ) {
		munchStm( asSeq->left.get( ) );
		munchStm( asSeq->right.get( ) );
	}

	// Label
	const IRTree::CLabel* asLabel = dynamic_cast< const IRTree::CLabel* >(stm);
	if( asLabel != nullptr ) {
		emit( new CodeGeneration::CLabel( *asLabel->label ) );
	}

	// Jump
	const IRTree::CJump* asJump = dynamic_cast< const IRTree::CJump* >(stm);
	if( asJump != nullptr ) {
		emit( new CodeGeneration::COper( std::string( "jmp 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), std::list<Temp::CLabel>( 1, *asJump->label ) ) );
	}

	// Exp (тот который забывает про результат)
	const IRTree::CExp* asExp = dynamic_cast<const IRTree::CExp*>( stm );
	if( asExp != nullptr ) {
		munchExp( asExp->exp.get() );
	}

	// CJump
	const IRTree::CCjump* asCjump = dynamic_cast<const IRTree::CCjump*>(stm);
	if( asCjump != nullptr ) {
		auto left = munchExp( asCjump->left.get() );
		auto right = munchExp( asCjump->right.get() );
		std::list<Temp::CTemp> cmp;
		std::list<Temp::CLabel> labelList;
		labelList.push_back( *(asCjump->iftrue) );
		cmp.push_back( left );
		cmp.push_back( right );
		emit( new CodeGeneration::COper( std::string( "cmp 's0, 's1" ), std::list<Temp::CTemp>(), cmp, std::list<Temp::CLabel>() ) );
		switch( asCjump->relop ) {
		case IRTree::CJ_Less:
			emit( new CodeGeneration::COper( std::string( "jl 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		case IRTree::CJ_Greater:
			emit( new CodeGeneration::COper( std::string( "jg 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		case IRTree::CJ_EqLess:
			emit( new CodeGeneration::COper( std::string( "jle 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		case IRTree::CJ_EqGreater:
			emit( new CodeGeneration::COper( std::string( "jge 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		case IRTree::CJ_Equal:
			emit( new CodeGeneration::COper( std::string( "je 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		case IRTree::CJ_NotEqual:
			emit( new CodeGeneration::COper( std::string( "jne 'l0" ), std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), labelList ) );
			break;
		default:
			assert( false );
			break;
		}
	}

}

void CInstructionsMuncher::emit( IInstruction* instruction )
{
	instructionsList.emplace_back( std::unique_ptr<IInstruction>( instruction ) );
#ifdef _DEBUG
	debugInfo.push_back( instruction->DebugInfo() );
#endif
}

void CInstructionsMuncher::FetchStoreSpilledVars( const std::unordered_set<Temp::CTemp>& spilledVars )
{
	std::vector< std::unique_ptr<IInstruction> > newInstructionList;
	for ( auto iter = instructionsList.begin(); iter != instructionsList.end(); ++iter ) {
		const std::list<Temp::CTemp>& defs = iter->get()->DefinedVars();
		const std::list<Temp::CTemp>& used = iter->get()->UsedVars();
		std::unordered_map<Temp::CTemp, Temp::CTemp> exchangeMap;
		std::unordered_map<Temp::CTemp, Temp::CTemp> storedMap;		
		for ( auto usedVar = used.begin(); usedVar != used.begin(); ++usedVar ) {
			if ( spilledVars.find( *usedVar ) != spilledVars.end() ) {
				exchangeMap[*usedVar] =  Temp::CTemp();
				IInstruction* fetchInstruction = new CMove("mov 'd0 's0", std::list<Temp::CTemp>(1, exchangeMap[*usedVar]), 
						std::list<Temp::CTemp>(1, *usedVar));
				newInstructionList.emplace_back( fetchInstruction );
			}
		}
		//для начала надо вставить модифицированную инструкцию, только потом store команды.
		for ( auto defVar = defs.begin(); defVar != defs.begin(); ++defVar ) {
			if ( spilledVars.find( *defVar ) != spilledVars.end() ) {
				Temp::CTemp newTempVar =  Temp::CTemp();
				exchangeMap[*defVar] = newTempVar;
				storedMap[*defVar] = newTempVar;
			}
		}
		iter->get()->ChangeVars( exchangeMap );
		newInstructionList.emplace_back( iter->release() );
		//вставка store команд
		for ( auto storeParams = storedMap.begin(); storeParams != storedMap.end(); ++storeParams ) {
			IInstruction* storeComand = new CMove("mov 'd0 's0", std::list<Temp::CTemp>(1, storeParams->first), 
					std::list<Temp::CTemp>(1, storeParams->second) );
			newInstructionList.emplace_back( storeComand );
		}
	}
}