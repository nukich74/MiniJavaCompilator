// Автор: Владислав Воротилов

#pragma once

#define assert( expr ) \
	if( !( expr ) ) \
		 __debugbreak(); \
	else \
		( ( void )1 ) 