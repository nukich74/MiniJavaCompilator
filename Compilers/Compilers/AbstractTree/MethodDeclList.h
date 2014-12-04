// Описание: Класс, описывающий вершину AST, отвечающую набору описаний методов.

#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CMethodDeclList : public IMethodDeclList, public CLocationStorage {
public:
	CMethodDeclList( CMethodDeclList* pMethodDeclList, IMethodDecl* _pMethodDecl, const CLocation& location ) : CLocationStorage( location )
	{ 
		if( pMethodDeclList != 0 ) {
			methodDeclList = pMethodDeclList->methodDeclList;
		}
		methodDeclList.emplace_back( std::shared_ptr<IMethodDecl>( _pMethodDecl ) ); 
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::shared_ptr<IMethodDecl> >& MethodDeclList() const { return methodDeclList; }

private:
	std::list< std::shared_ptr<IMethodDecl> > methodDeclList;
};