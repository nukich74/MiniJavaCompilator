﻿// Автор: Азат Давлетшин
// Описание: Реализация функции Format (подстановка в строку инструкции названий регистров)

#include <CodeGeneration\Instruction.h>
#include <assert.h>

using namespace CodeGeneration;

std::string IInstruction::Format( const std::map<Temp::CTemp, std::string>& varsMapping ) const
{
	// Не нужно до распределения регистров.
	assert( false );
	return std::string();
}

COper::COper( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
	const std::list<Temp::CLabel>& _labelList = std::list<Temp::CLabel>() )
		: Assem( _Assem )
		, src( _src )
		, dst( _dst )
		, labelList( _labelList )
{ }

CMove::CMove( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src )
	: Assem( _Assem )
	, dst( _dst )
	, src( _src )
{ }

CLabel::CLabel( const std::list<Temp::CLabel>& _labelList )
	: labelList( _labelList )
{ }