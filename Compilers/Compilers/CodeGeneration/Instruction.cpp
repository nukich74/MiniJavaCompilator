// Автор: Азат Давлетшин
// Описание: Реализация функции Format (подстановка в строку инструкции названий регистров)

#include <CodeGeneration\Instruction.h>
#include <assert.h>

using namespace CodeGeneration;

std::string IInstruction::Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const
{
	assert( false );

	return std::string();
}

