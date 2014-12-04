// Описание: Класс, описывающий вершину AST, отвечающую объявлению переменной.

#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CVarDecl : public IVarDecl, public CLocationStorage {
public:
	CVarDecl( IType* _pVarType, const std::string& _varName, const CLocation& location ) 
		: CLocationStorage( location )
		, varName( _varName )
		, pVarType( _pVarType )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IType* VarType() const { return pVarType.get(); }

	const std::string& VarName() const { return varName; }

private:
	std::shared_ptr<IType> pVarType;
	std::string varName;
};