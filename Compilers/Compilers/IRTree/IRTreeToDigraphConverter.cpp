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
	node->dst->Accept( *this );
	string destString = lastNodeName;

	node->src->Accept( *this );
	string srcString = lastNodeName;

	nextNameWithId( "move" );

	treeRepresentation.AddEdge( lastNodeName, destString, "dest" );
	treeRepresentation.AddEdge( lastNodeName, srcString, "src" );
}

void CIRTreeToDigraphConverter::Visit( const CExp* node )
{
	node->exp->Accept( *this );
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
	node->right->Accept( *this );
	string rightString = lastNodeName;
	node->left->Accept( *this );
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
		node->left->Accept( *this );
		string leftString = lastNodeName;
		if( node->right != nullptr ) {
			node->right->Accept( *this );
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
	node->left->Accept( *this );
	string leftString = lastNodeName;
	node->right->Accept( *this );
	string rightString = lastNodeName;
	nextNameWithId( "binop__" + ToString( node->binop ) );
	treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
	treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
}

void CIRTreeToDigraphConverter::Visit( const CMem* node )
{
	node->exp->Accept( *this );
	string prevString = lastNodeName;
	nextNameWithId( "mem" );
	treeRepresentation.AddEdge( lastNodeName, prevString, "mem" );
}

void CIRTreeToDigraphConverter::Visit( const CCall* node )
{
	node->func->Accept( *this );
	string funcString = lastNodeName;
	node->args.Accept( *this );
	string argsString = lastNodeName;
	nextNameWithId( "call" );
	treeRepresentation.AddEdge( lastNodeName, funcString, "func" );
	treeRepresentation.AddEdge( lastNodeName, argsString, "args" );
}

void CIRTreeToDigraphConverter::Visit( const CEseq* node )
{
	node->stm->Accept( *this );
	string stmString = lastNodeName;
	node->exp->Accept( *this );
	string expString = lastNodeName;
	nextNameWithId( "eseq" );
	treeRepresentation.AddEdge( lastNodeName, expString, "exp" );
	treeRepresentation.AddEdge( lastNodeName, stmString, "stm" );
}

void CIRTreeToDigraphConverter::Visit( const CExpList* node )
{
	if( node->head != nullptr ) {
		node->head->Accept( *this );
		string headString = lastNodeName;
		if( node->tail != nullptr ) {
			node->tail->Accept( *this );
			string tailString = lastNodeName;
			nextNameWithId( "expList" );
			treeRepresentation.AddEdge( lastNodeName, headString, "head" );
			treeRepresentation.AddEdge( lastNodeName, tailString, "tail" );
		} else {
			nextNameWithId( "expList" );
			treeRepresentation.AddEdge( lastNodeName, headString, "head" );
		}
	} else {
		nextNameWithId( "expList" );
	}
	
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