#include "IRTreeToDigraphConverter.h"
#include <IRStm.h>
#include <IRExp.h>
#include <sstream>
#include <iostream>

using namespace std;

namespace IRTree {

int CIRTreeToDigraphConverter::minId = 0;

void CIRTreeToDigraphConverter::Visit( const CMove* node )
{
	node->dst->Visit( *this );
	string destString = lastNodeName;

	node->src->Visit( *this );
	string srcString = lastNodeName;

	nextNameWithId( "move" );

	treeRepresentation.AddEdge( lastNodeName, destString, "dest" );
	treeRepresentation.AddEdge( lastNodeName, srcString, "src" );
}

void CIRTreeToDigraphConverter::Visit( const CExp* node )
{
	node->exp->Visit( *this );
	string prevString = lastNodeName;

	nextNameWithId( "exp" );
	treeRepresentation.AddEdge( lastNodeName, prevString );
}

void CIRTreeToDigraphConverter::Visit( const CJump* node )
{
	nextNameWithId( "jump" );
	treeRepresentation.AddEdge( lastNodeName, node->label->Name(), "to_label" );
}

void CIRTreeToDigraphConverter::Visit( const CCjump* node )
{
	node->right->Visit( *this );
	string rightString = lastNodeName;
	node->left->Visit( *this );
	string leftString = lastNodeName;

	nextNameWithId( "Cjump" );
	
	treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
	treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
	treeRepresentation.AddEdge( lastNodeName, node->iftrue->Name(), "iftrue" );
	treeRepresentation.AddEdge( lastNodeName, node->iffalse->Name(), "iffalse" );
}

void CIRTreeToDigraphConverter::Visit( const CSeq* node )
{
	if( node->left != nullptr ) {
		node->left->Visit( *this );
		string leftString = lastNodeName;
		if( node->right != nullptr ) {
			node->right->Visit( *this );
			string rightString = lastNodeName;
			nextNameWithId( "seq" );
			treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
			treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
		} else {
			nextNameWithId( "seq" );
			treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
		}
	} else {
		nextNameWithId( "seq" );
	}
}

void CIRTreeToDigraphConverter::Visit( const CConst* node )
{
	nextNameWithId( string( "const_" ) + to_string( node->value ) );
}

void CIRTreeToDigraphConverter::Visit( const CName* node )
{
	nextNameWithId( string( "name_" ) + node->label->Name() );
}

void CIRTreeToDigraphConverter::Visit( const CTemp* node )
{
	nextNameWithId( string( "temp_" ) + node->temp.Name() );
}

void CIRTreeToDigraphConverter::Visit( const CBinop* node )
{
	node->left->Visit( *this );
	string leftString = lastNodeName;
	node->right->Visit( *this );
	string rightString = lastNodeName;
	nextNameWithId( "binop" );
	treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
	treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
}

void CIRTreeToDigraphConverter::Visit( const CMem* node )
{
	node->exp->Visit( *this );
	string prevString = lastNodeName;
	nextNameWithId( "mem" );
	treeRepresentation.AddEdge( lastNodeName, prevString, "mem" );
}

void CIRTreeToDigraphConverter::Visit( const CCall* node )
{
	nextNameWithId( "call" );
}

void CIRTreeToDigraphConverter::Visit( const CEseq* node )
{
	nextNameWithId( "eseq" );
}

void CIRTreeToDigraphConverter::Visit( const CExpList* node )
{
	nextNameWithId( "expList" );
}

void CIRTreeToDigraphConverter::Visit( const CLabel* node )
{
	nextNameWithId( string( "label:" ) + node->label->Name() );
}

void CIRTreeToDigraphConverter::nextNameWithId( std::string label )
{
	lastNodeName = label + "__id_"+ to_string( minId++ );
	treeRepresentation.SetNodeLabel( lastNodeName, label );
}

} //namespace IRTree 