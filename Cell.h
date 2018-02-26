#pragma once
#include "stdafx.h"

template<typename Offset = int, typename Symbol = char>
struct Cell
{
	Offset oX, oY;
	System::ConsoleColor fg, bg;
	Symbol sym;

	Cell()
	{
	}
	Cell( Offset _x, Offset _y, System::ConsoleColor _fg, System::ConsoleColor _bg, Symbol _sym )
	{
		oX = _x;
		oY = _y;
		fg = _fg;
		bg = _bg;
		sym = _sym;
	}
	bool Show( int _left, int _top ) const
	{
		int x = _left + oX;
		int y = _top + oY;
		if ( x < 0 ||
			 System::Console::WindowWidth() <= x ||
			 y < 0 ||
			 System::Console::WindowHeight() <= y )
			return false;
		System::Console::SetCursorPosition( x, y );
		System::Console::BackgroundColor( ( WORD )bg );
		System::Console::ForegroundColor( ( WORD )fg );
		std::cout << sym;
		return true;
	}
};

// ☻☺ トニー ☺☻ -- Y:2015年 //