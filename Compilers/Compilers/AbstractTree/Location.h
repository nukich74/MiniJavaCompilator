// Автор: Николай Фролов.

// Описание: структура с описанием местоположения токена.

#pragma once

struct CLocation {
public:
	// Линия, в которой содержится первый символ токена.
	const int startLine;
	// Позиция первого символа токена внутри линии.
	const int startColumn;
	// Линия, в которой содержится последний символ токена.
	const int endLine;
	// Позиция последнего символа токена внутри линии.
	const int endColumn;

	CLocation( int _startLine, int _startColumn, int _endLine, int _endColumn )
		: startLine( _startLine )
		, startColumn( _startColumn )
		, endLine( _endLine )
		, endColumn( _endColumn )
	{ }
};