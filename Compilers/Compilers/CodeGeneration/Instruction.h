// Автор: Азат Давлетшин
// Описание: Интерфейс инструкции ассемблера (OPER, LABEL, MOVE)

#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <map>
#include <memory>
#include <Temp.h>

namespace CodeGeneration {

class IInstruction {
public:
	std::string Assem;

	IInstruction( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
		const std::list<Temp::CLabel>& _labelList );

	const std::list<Temp::CTemp>& UsedVars( ) const { return src; }
	const std::list<Temp::CTemp>& DefinedVars( ) const { return dst; }
	const std::list<Temp::CLabel>& JumpTargets( ) const { return labelList; }

	void ChangeVars( std::unordered_map<Temp::CTemp, Temp::CTemp>& excahngeMap );

	std::string Format( const std::unordered_map<Temp::CTemp, std::string>& varsMapping ) const;

#ifdef _DEBUG
	std::string DebugInfo() const
	{ 
		std::string result = "; Destinations: ";
		for( auto& tmp : dst ) { result += tmp.Name(); result += ", "; }
		result += "Sources: ";
		for( auto& tmp : src ) { result += tmp.Name(); result += ", "; }
		result += "Labels: ";
		for( auto& lbl: labelList ) { result += lbl.Name(); result += ", "; }
		return result;
	}	
#endif

	// Для того, чтобы сделать класс абстрактным
	virtual ~IInstruction() = 0 {}

protected:
	std::list<Temp::CTemp> dst;
	std::list<Temp::CTemp> src;
	std::list<Temp::CLabel> labelList;

	static bool isUseless( std::string );
};

class COper : public IInstruction {
public:
	COper( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
		const std::list<Temp::CLabel> _labelList = std::list<Temp::CLabel>() );
};

class CMove : public IInstruction {
public:
	CMove( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src );
};

class CLabel : public IInstruction {
public:
	CLabel( const Temp::CLabel& _labelList );

};

} // namespace CodeGeneration
