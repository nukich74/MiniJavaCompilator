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
	const char* AsmCode;
	virtual const std::list<Temp::CTemp>& UsedVars() const = 0;
	virtual const std::list<Temp::CTemp>& DefinedVars() const = 0;
	virtual const std::list<Temp::CLabel>& JumpTargets() const = 0;
	std::string Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const;
};

} // namespace CodeGeneration
