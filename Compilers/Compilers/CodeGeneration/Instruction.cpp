// Автор: Азат Давлетшин
// Описание: Реализация функции Format (подстановка в строку инструкции названий регистров)

#include <CodeGeneration\Instruction.h>
#include <assert.h>

using namespace CodeGeneration;

IInstruction::IInstruction( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
	const std::list<Temp::CLabel>& _labelList ) :
	Assem( _Assem ),
	dst( _dst ),
	src( _src ),
	labelList( _labelList )
{ }

std::string IInstruction::Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const
{
	// Не нужно до распределения регистров.
	assert( false );
	return std::string();
}

COper::COper( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
	const std::list<Temp::CLabel> _labelList ) :
	IInstruction( _Assem, _dst, _src, _labelList )
{ }

CMove::CMove( const std::string& _Assem, const std::list<Temp::CTemp>& _dst,  const std::list<Temp::CTemp>& _src ) :
	IInstruction( _Assem, _dst, _src, std::list<Temp::CLabel>() )
{ }

CLabel::CLabel( const Temp::CLabel& _label ) :
	IInstruction( "", std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), std::list<Temp::CLabel>( 1, _label ) )
{ }