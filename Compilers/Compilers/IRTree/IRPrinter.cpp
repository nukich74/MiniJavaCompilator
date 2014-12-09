#include <IRPrint.h>
#include <IRStm.h>
#include <IRExp.h>
#include <iostream>

namespace IRTree
{

int CPrinter::minId = 0;

void CPrinter::Print( const CIRMove* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->dst.get(), id ) );
	parents.insert( std::make_pair( node->src.get(), id ) );
	node->dst->Print( *this );
	node->src->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end() ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[dst]" << ids.find( node->dst.get() )->second << " ";
	std::cout << "[src]" << ids.find( node->src.get() )->second << " ";
	
	std::cout << "Type: " << "CIRMove";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRExp* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->exp.get( ), id ) );
	node->exp->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[exp]" << ids.find( node->exp.get( ) )->second << " ";

	std::cout << "Type: " << "CIRExp";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRJump* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[label]" << node->label->Name() << " ";

	std::cout << "Type: " << "CIRJump";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRCjump* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->left.get( ), id ) );
	parents.insert( std::make_pair( node->right.get( ), id ) );
	node->left->Print( *this );
	node->right->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[left]" << ids.find( node->left.get( ) )->second << " ";
	std::cout << "[right]" << ids.find( node->right.get( ) )->second << " ";
	std::cout << "[iftrue]" << node->iftrue->Name( ) << " ";
	std::cout << "[iffalse]" << node->iffalse->Name( ) << " ";
	std::cout << "[relop]" << node->relop << " ";

	std::cout << "Type: " << "CIRCjump";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRSeq* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->left.get( ), id ) );
	parents.insert( std::make_pair( node->right.get( ), id ) );
	node->left->Print( *this );
	node->right->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[left]" << ids.find( node->left.get( ) )->second << " ";
	std::cout << "[right]" << ids.find( node->right.get( ) )->second << " ";

	std::cout << "Type: " << "CIRSeq";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRConst* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[value]" << node->value << " ";

	std::cout << "Type: " << "CIRConst";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRName* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[label]" << node->label.Name() << " ";

	std::cout << "Type: " << "CIRName";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRTemp* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[temp]" << node->temp.Name( ) << " ";

	std::cout << "Type: " << "CIRTemp";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRBinop* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->left.get( ), id ) );
	parents.insert( std::make_pair( node->right.get( ), id ) );
	node->left->Print( *this );
	node->right->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[left]" << ids.find( node->left.get( ) )->second << " ";
	std::cout << "[right]" << ids.find( node->right.get( ) )->second << " ";
	std::cout << "[binop]" << node->binop << " ";

	std::cout << "Type: " << "CIRBinop";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRCall* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( &node->args, id ) );
	parents.insert( std::make_pair( node->func.get( ), id ) );
	node->args.Print( *this );
	node->func->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[func]" << ids.find( node->func.get( ) )->second << " ";
	std::cout << "[args]" << ids.find( &node->args )->second << " ";

	std::cout << "Type: " << "CIRCall";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRMem* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->exp.get( ), id ) );
	node->exp->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[exp]" << ids.find( node->exp.get( ) )->second << " ";

	std::cout << "Type: " << "CIRMem";
	std::cout << std::endl;
}

void CPrinter::Print( const CIREseq* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->stm.get( ), id ) );
	parents.insert( std::make_pair( node->exp.get( ), id ) );
	node->stm->Print( *this );
	node->exp->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[stm]" << ids.find( node->stm.get( ) )->second << " ";
	std::cout << "[exp]" << ids.find( node->exp.get( ) )->second << " ";

	std::cout << "Type: " << "CIREseq";
	std::cout << std::endl;
}

void CPrinter::Print( const CIRExpList* node )
{
	int id = minId++;
	ids.insert( std::make_pair( node, id ) );
	parents.insert( std::make_pair( node->head.get( ), id ) );
	parents.insert( std::make_pair( node->tail.get( ), id ) );
	node->head->Print( *this );
	node->tail->Print( *this );

	std::cout << "Parent: ";
	auto it = parents.find( this );
	if( it != parents.end( ) ) {
		std::cout << it->second;
	} else {
		std::cout << -1;
	}

	std::cout << " Values: ";

	std::cout << "[head]" << ids.find( node->head.get( ) )->second << " ";
	std::cout << "[tail]" << ids.find( node->tail.get( ) )->second << " ";

	std::cout << "Type: " << "CIRExpList";
	std::cout << std::endl;
}

}