#pragma once

#include "Frame.h"

namespace Frame {

const IAccess* CFrame::GetFormal( std::string name ) const
{
	auto result = formals.find( name );
	if (result == formals.end()) {
		return 0;
	}
	return result->second;
}

void CFrame::AddFormal(const std::string _name, const IAccess* _var)
{
	formals.insert( std::make_pair( _name, _var ) );
}

const IAccess* CFrame::GetLocal( std::string name ) const
{
	auto result = locals.find(name);
	if (result == locals.end()) {
		return 0;
	}
	return result->second;
}

void CFrame::AddLocal(const std::string _name, const IAccess* _var)
{
	locals.insert(std::make_pair(_name, _var ) );
}

const IAccess* CFrame::GetAccess( std::string _name ) const
{
	//ищем внутри функции и в полях
	return 0;
}

} // namespace Frame