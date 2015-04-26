// Автор: Азат Давлетшин
// Описание: Интерфейс инструкции ассемблера (OPER, LABEL, MOVE)

#pragma once

#include <list>
#include <string>
#include <map>
#include <memory>
#include <Temp.h>

namespace CodeGeneration {

class IInstruction {
public:
	std::string Assem;

	IInstruction( const std::string& _Assem, std::list<Temp::CTemp*>* _dst, std::list<Temp::CTemp*>* _src,
		std::list<Temp::CLabel>* _labelList );

	const std::list<Temp::CTemp*>* UsedVars( ) const { return src.get( ); }

	const std::list<Temp::CTemp*>* DefinedVars( ) const { return dst.get( ); }

	const std::list<Temp::CLabel>* JumpTargets( ) const { return labelList.get( ); }

	std::string Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const;

	// Для того, чтобы сделать класс абстрактным
	virtual ~IInstruction() = 0 {}
protected:
	const std::unique_ptr< std::list<Temp::CTemp*> > dst;

	const std::unique_ptr< std::list<Temp::CTemp*> > src;

	const std::unique_ptr< std::list<Temp::CLabel> > labelList;
};

class COper : public IInstruction {
public:
	COper( const std::string& _Assem, std::list<Temp::CTemp*>* _dst, std::list<Temp::CTemp*>* _src,
		std::list<Temp::CLabel>* _labelList = 0 );
};

class CMove : public IInstruction {
public:
	CMove( const std::string& _Assem, std::list<Temp::CTemp*>* _dst, std::list<Temp::CTemp*>* _src );
};

class CLabel : public IInstruction {
public:
	CLabel( const Temp::CLabel& _labelList );
};

} // namespace CodeGeneration
