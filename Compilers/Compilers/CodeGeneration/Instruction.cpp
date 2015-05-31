// Автор: Азат Давлетшин
// Описание: Реализация функции Format (подстановка в строку инструкции названий регистров)

#include <CodeGeneration\Instruction.h>
#include "FineAssert.h"
#include <cctype>

using namespace CodeGeneration;

IInstruction::IInstruction( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
	const std::list<Temp::CLabel>& _labelList ) :
	Assem( _Assem ),
	dst( _dst ),
	src( _src ),
	labelList( _labelList )
{ }

std::string IInstruction::Format( const std::unordered_map<Temp::CTemp, std::string>& varsMapping ) const
{
	if( !labelList.empty() ) {
		return Assem;
	}
	std::string result( Assem );
	// Не нужно до распределения регистров.
	for( size_t i = 0; i < result.size(); ++i ) {
		if( result[i] == '\'' ) {
			int start = i + 1;
			int end = start;
			std::string type = std::string( 1, result[start] );
			std::string number;
			while( std::isdigit( result[++end] ) ) {
				number.push_back( result[end] );
			}
			const std::list<Temp::CTemp>* from = nullptr;
			if( type == "d" ) {
				from = &dst;
			} else if( type == "s" ) {
				from = &src;
			} else {
				assert( false );
			}
			int posInArray = std::stoi( number );
			auto iter = from->begin();
			for( int j = 0; j < posInArray; ++j, ++iter ) { }
			result.replace( result.begin() + i, result.begin() + end, varsMapping.find( *iter )->second );
		}
	}
	return result;
}

void IInstruction::ChangeVars( std::unordered_map<Temp::CTemp, Temp::CTemp>& exchangeMap )
{
	for( auto iter = dst.begin(); iter != dst.end(); ++iter ) {
		if ( exchangeMap.find( *iter ) != exchangeMap.end() ) {
			*iter = exchangeMap[*iter];
		}
	}
	for( auto iter = src.begin(); iter != src.end(); ++iter ) {
		if ( exchangeMap.find( *iter ) != exchangeMap.end() ) {
			*iter = exchangeMap[*iter];
		}
	}
}

COper::COper( const std::string& _Assem, const std::list<Temp::CTemp>& _dst, const std::list<Temp::CTemp>& _src,
	const std::list<Temp::CLabel> _labelList ) :
	IInstruction( _Assem, _dst, _src, _labelList )
{ }

CMove::CMove( const std::string& _Assem, const std::list<Temp::CTemp>& _dst,  const std::list<Temp::CTemp>& _src ) :
	IInstruction( _Assem, _dst, _src, std::list<Temp::CLabel>() )
{ }

CLabel::CLabel( const Temp::CLabel& _label ) :
	IInstruction( "'l0:", std::list<Temp::CTemp>( ), std::list<Temp::CTemp>( ), std::list<Temp::CLabel>( 1, _label ) )
{ }