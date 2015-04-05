// �����: ��������� ���������
// ��������: ����� ����������� ����� ������, � ��������������� ��� � �������� ���������

#include "IRTreeLinearizer.h"
#include <assert.h>
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
	for( int i = 0; i < Linearized.size(); i++ ) {
		currentBlock.push_back( Linearized[i] );

		// ���� ������� ���� Jump ��� �Jump �� ��� ����� ������������ �����
		const IRTree::CJump* jumpNode = dynamic_cast<const CJump*>( Linearized[i].get() );
		const IRTree::CCjump* cjumpNode = dynamic_cast<const CCjump*>( Linearized[i].get( ) );
		if( jumpNode != nullptr || cjumpNode != nullptr ) {
			IndependentBlocks.push_back( currentBlock );
			currentBlock.clear();
			continue;
		} else {
			// ���� ��������� ���� Label, � �� �� � �������� �� ���� ���� �������� Jump �� ���� Label
			if( i + 1 < Linearized.size() ) {
				const IRTree::CLabel* labelNode = dynamic_cast<const CLabel*>( Linearized[i + 1].get() );
				if( labelNode != nullptr ) {
					currentBlock.emplace_back( shared_ptr<const IStm>( new CJump( labelNode->label ) ) );
					IndependentBlocks.push_back( currentBlock );
					currentBlock.clear();
					continue;
				}
			}
		}
		
	}
	currentBlock.emplace_back( shared_ptr<const IStm>( new CJump( new Temp::CLabel( std::string( "epilog_of__" ) + frame->Name ) ) ) );
	IndependentBlocks.push_back( currentBlock );
}

void CLinearizer::Reorder()
{
	for( auto& i = IndependentBlocks.begin(); i != IndependentBlocks.end(); i++ ) {
		const CCjump* cjumpNode = dynamic_cast<const CCjump*>( i->back().get() );
		if( cjumpNode != nullptr ) {
			// ����� ���� ���������������� �� �Jump ������ ����� ���� ��� false �����
			auto& j = i;
			j++;
			for( ; j != IndependentBlocks.end(); j++ ) {
				const CLabel* labelNode = dynamic_cast<const CLabel*>( j->front().get() );
				if( labelNode != nullptr && labelNode->label == cjumpNode->iffalse ) {
					break;
				}
			}
			if( j != IndependentBlocks.end() ) {
				i++;
				i = IndependentBlocks.insert( i, *j );
				i++;
				IndependentBlocks.erase( j );
			} else {
				assert( false );
			}
		}

		const CJump* jumpNode = dynamic_cast<const CJump*>( i->back().get() );
		if( cjumpNode != nullptr ) {
			// ����� ���� ���������������� �� Jump ������ ����� ���� ��� �����
			auto& j = i;
			j++;
			for( ; j != IndependentBlocks.end(); j++ ) {
				const CLabel* labelNode = dynamic_cast<const CLabel*>( j->front().get() );
				if( labelNode != nullptr && labelNode->label == jumpNode->label ) {
					break;
				}
			}
			if( j != IndependentBlocks.end() ) {
				// ���� ������� ����� ����� �� ������� ����� Jump
				i++;
				IndependentBlocks.insert( i, *j );
				IndependentBlocks.erase( j );
			}
		}

	}
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
		Linearized.emplace_back( shared_ptr<const IStm>( new CExp( eseq->exp.get() ) ) );
		linearize( eseq->stm );
		return;
	}
	Linearized.push_back( root );
}

} // namespace IRTree