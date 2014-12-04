// Описание: Класс, описывающий вершину AST, отвечающую определению класса.

#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CClassDecl : public IClassDecl, public CLocationStorage {
public:
	CClassDecl( const std::string& _classId, IVarDeclList* _pVarDeclList, IMethodDeclList* _pMethodDeclList,
				const std::string& _parrentId, const CLocation& location )
			: CLocationStorage( location )
			, classId( _classId )
			, pVarDeclList( _pVarDeclList )
			, pMethodDeclList( _pMethodDeclList )
			, parentId( _parrentId )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::string& ClassId() const { return classId; }

	const IVarDeclList* VarDeclList() const { return pVarDeclList.get(); }

	const IMethodDeclList* MethodDeclList() const { return pMethodDeclList.get(); }

	const std::string& ParendId() const { return parentId; }

private:
	std::string classId;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IMethodDeclList> pMethodDeclList;
	std::string parentId;
};