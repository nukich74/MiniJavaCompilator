#pragma once

#include <string>

namespace Temp
{
// Метка - точка перехода в коде
class CLabel {
public:
	// Создать метку с уникальным именем
	CLabel();
	CLabel( const CLabel& src ) : name( src.name ) {}
	// Создать метку с заданным именем
	explicit CLabel( const std::string& name );

	const std::string& Name() const { return name; }

	bool operator == (const CLabel& other) const
		{ return name == other.name; }
	bool operator != (const CLabel& other) const
		{ return !this->operator==( other ); }

private:
	// Счётчик для создания уникальных идентификаторов
	static int nextUniqueId;
	std::string name;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Временная переменная
class CTemp {
public:
	// Новая переменная с уникальным именем
	CTemp();
	CTemp( const CTemp& src ) : name( src.name ) {}
	// Новая переменная с заданным именем
	explicit CTemp( const std::string& name );

	const std::string& Name() const { return name; }

	bool operator == (const CTemp& other) const
		{ return name == other.name; }
	bool operator != (const CTemp& other) const
		{ return !this->operator==( other ); }

private:
	// Счётчик для создания уникальных имён
	static int nextUniqueId;
	std::string name;
};
}

namespace std
{

template <> 
struct hash<Temp::CTemp> {
	size_t operator()( const Temp::CTemp& value ) const
	{
		return hash<std::string>()( value.Name() );
	}
};

template <>
struct hash<Temp::CLabel> {
	size_t operator()( const Temp::CLabel& value ) const
	{
		return hash<std::string>()( value.Name() );
	}
};

} // namespace std