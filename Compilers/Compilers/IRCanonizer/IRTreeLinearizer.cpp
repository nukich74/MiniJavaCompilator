// �����: ��������� ���������
// ��������: ����� ����������� ����� ������, � ��������������� ��� � �������� ���������

#include "IRTreeLinearizer.h"
#include "FineAssert.h"
#include <IRExp.h>

using namespace std;

namespace IRTree {

void CLinearizer::Linearize( )
{
	linearize( std::shared_ptr<const IRTree::IStm>( frame->Stm ) );
}

void CLinearizer::SplitByLabelAndJump()
{
	// ������� �������������� ����������� ����
	vector< std::shared_ptr<const IStm> > currentBlock;
	// ������� ���������� �� ������������ Label. Jump �� ���� �� �������
	currentBlock.emplace_back( shared_ptr<IStm>( new CLabel( new Temp::CLabel( std::string( "start_of_function__" ) + frame->Name ) ) ) );
	// �������� �� ���������������� ������ � ����� �� CJump � CLabel �������� �����������
	for( int i = 0; i < linearized.size(); i++ ) {
		currentBlock.push_back( linearized[i] );

		// ���� ������� ���� Jump ��� �Jump �� ��� ����� ������������ �����
		const IRTree::CJump* jumpNode = dynamic_cast<const CJump*>( linearized[i].get() );
		const IRTree::CCjump* cjumpNode = dynamic_cast<const CCjump*>( linearized[i].get( ) );
		if( jumpNode != nullptr || cjumpNode != nullptr ) {
			independentBlocks.push_back( currentBlock );
			currentBlock.clear();
			continue;
		} else {
			// ���� ��������� ���� Label, � �� �� � �������� �� ���� ���� �������� Jump �� ���� Label
			if( i + 1 < linearized.size() ) {
				const IRTree::CLabel* labelNode = dynamic_cast<const CLabel*>( linearized[i + 1].get() );
				if( labelNode != nullptr ) {
					currentBlock.emplace_back( shared_ptr<const IStm>( new CJump( labelNode->label ) ) );
					independentBlocks.push_back( currentBlock );
					currentBlock.clear();
					continue;
				}
			}
		}
		
	}
	currentBlock.emplace_back( shared_ptr<const IStm>( new CJump( new Temp::CLabel( std::string( "epilog_of__" ) + frame->Name ) ) ) );
	independentBlocks.push_back( currentBlock );
}

void CLinearizer::Reorder()
{
	for( auto i = independentBlocks.begin(); i != independentBlocks.end(); i++ ) {
		const CCjump* cjumpNode = dynamic_cast<const CCjump*>( i->back().get() );
		if( cjumpNode != nullptr ) {
			// ����� ���� ��������������� �� �Jump ������ ����� ���� ��� false �����
			auto j = i;
			j++;
			for( ; j != independentBlocks.end(); j++ ) {
				const CLabel* labelNode = dynamic_cast<const CLabel*>( j->front().get() );
				if( labelNode != nullptr && labelNode->label->Name() == cjumpNode->iffalse->Name() ) {
					break;
				}
			}
			if( j != independentBlocks.end() ) {
				i++;
				i = independentBlocks.insert( i, *j );
				independentBlocks.erase( j );
				i--;
			} else {
				assert( false );
			}
			continue;
		}

		const CJump* jumpNode = dynamic_cast<const CJump*>( i->back().get() );
		if( jumpNode != nullptr ) {
			// ����� ���� ���������������� �� Jump ������ ����� ���� ��� �����
			auto j = i;
			j++;
			for( ; j != independentBlocks.end(); j++ ) {
				const CLabel* labelNode = dynamic_cast<const CLabel*>( j->front().get() );
				if( labelNode != nullptr && labelNode->label->Name() == jumpNode->label->Name() ) {
					break;
				}
			}
			if( j != independentBlocks.end() ) {
				// ���� ������� ����� ����� �� ������� ����� Jump
				i++;
				i = independentBlocks.insert( i, *j );
				independentBlocks.erase( j );
				i--;
			}
			continue;
		}

	}
}

std::vector< std::shared_ptr<const IStm> > CLinearizer::GetReordered()
{
	std::vector< std::shared_ptr<const IStm> > reordered;
	for( auto i : independentBlocks ) {
		for( auto j : i ) {
			reordered.push_back( j );
		}
	}
	return reordered;
}

void CLinearizer::linearize( std::shared_ptr<const IStm> root )
{
	const CSeq* seq = dynamic_cast<const CSeq*>( root.get() );
	if( seq != nullptr ) {
		linearize( seq->left );
		linearize( seq->right );
		return;
	}
	const CEseq* eseq = dynamic_cast<const CEseq*>( root.get() );
	if( eseq != nullptr ) {
		linearized.emplace_back( shared_ptr<const IStm>( new CExp( eseq->exp.get() ) ) );
		linearize( eseq->stm );
		return;
	}
	linearized.push_back( root );
}

} // namespace IRTree