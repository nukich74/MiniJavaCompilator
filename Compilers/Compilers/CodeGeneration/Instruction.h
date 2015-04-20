// Автор: Азат Давлетшин
// Описание: Интерфейс инструкции ассемблера (OPER, LABEL, MOVE)

#pragma once

#include <list>
#include <string>
#include <map>
#include <Temp.h>

namespace CodeGeneration {

class IInstruction {
public:
	virtual const std::list<Temp::CTemp>& UsedVars() const = 0;

	virtual const std::list<Temp::CTemp>& DefinedVars() const = 0;

	virtual const std::list<Temp::CLabel>& JumpTargets() const = 0;

	std::string Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const;
};

class COper : public IInstruction {
public:
	std::string Assem;

	COper( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
		const std::list<Temp::CLabel>& _labelList = std::list<Temp::CLabel>() );

	const std::list<Temp::CTemp>& UsedVars() const { return src; }

	const std::list<Temp::CTemp>& DefinedVars() const { return dst; }

	const std::list<Temp::CLabel>& JumpTargets() const { return labelList; }

private:
	const std::list<Temp::CTemp>& dst;

	const std::list<Temp::CTemp>& src;

	const std::list<Temp::CLabel>& labelList;
};

class CMove : public IInstruction {
public:
	std::string Assem;

	CMove( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src );

	const std::list<Temp::CTemp>& UsedVars() const { return src; }

	const std::list<Temp::CTemp>& DefinedVars() const { return dst; }

	const std::list<Temp::CLabel>& JumpTargets() const { return std::list<Temp::CLabel>(); }

private:
	const std::list<Temp::CTemp>& dst;

	const std::list<Temp::CTemp>& src;
};

class CLabel : public IInstruction {
public:
	CLabel( const std::list<Temp::CLabel>& _labelList );

	const std::list<Temp::CTemp>& UsedVars() const { return std::list<Temp::CTemp>(); }

	const std::list<Temp::CTemp>& DefinedVars() const { return std::list<Temp::CTemp>(); }

	const std::list<Temp::CLabel>& JumpTargets() const { return labelList; }

private:
	const std::list<Temp::CLabel>& labelList;
};

} // namespace CodeGeneration
