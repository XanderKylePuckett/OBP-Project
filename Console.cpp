#include "stdafx.h"

namespace System
{

	HANDLE Console::out = GetStdHandle( STD_OUTPUT_HANDLE );
	WORD Console::defColors = Console::BackgroundColor() << 4 | Console::ForegroundColor();
	HWND Console::hwnd = GetConsoleWindow();

	void Console::Show( wchar_t symbol )
	{
		std::wcout << symbol;
	}

	WORD Console::ForegroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return info.wAttributes & 0x0F;
	}

	void Console::ForegroundColor( WORD attr )
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		SetConsoleTextAttribute( out, info.wAttributes & 0xF0 | attr );
	}

	WORD Console::BackgroundColor()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return ( info.wAttributes & 0xF0 ) >> 4;
	}

	void Console::BackgroundColor( WORD attr )
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		SetConsoleTextAttribute( out, info.wAttributes & 0x0F | attr << 4 );
	}

	void Console::ResetColor()
	{
		SetConsoleTextAttribute( out, defColors );
	}

	int Console::WindowWidth()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return info.srWindow.Right - info.srWindow.Left + 1;
	}

	int Console::WindowHeight()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return info.srWindow.Bottom - info.srWindow.Top + 1;
	}

	void Console::SetWindowSize( int columns, int rows )
	{
		COORD c = GetLargestConsoleWindowSize( out );
		if ( columns < 1 || c.X < ( SHORT )columns )
			columns = ( int )c.X;
		if ( rows < 1 || c.Y < ( SHORT )rows )
			rows = ( int )c.Y;

		SMALL_RECT dim = { 0, 0, ( SHORT )( columns - 1 ), ( SHORT )( rows - 1 ) };
		SetConsoleWindowInfo( out, TRUE, &dim );
	}

	void Console::SetBufferSize( int columns, int rows )
	{
		COORD c = { ( SHORT )columns, ( SHORT )rows };
		SetConsoleScreenBufferSize( out, c );
	}

	void Console::CursorVisible( bool visible )
	{
		CONSOLE_CURSOR_INFO curs;
		GetConsoleCursorInfo( out, &curs );
		if ( TRUE == curs.bVisible  && visible || FALSE == curs.bVisible  && !visible ) return;
		curs.bVisible = ( visible ) ? TRUE : FALSE;
		SetConsoleCursorInfo( out, &curs );
	}

	void Console::Clear()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );

		DWORD len = ( DWORD )( info.dwSize.X ), num;
		COORD c = { 0, 0 };
		for ( SHORT i = 0; i < info.dwSize.Y; ++i )
		{
			c.Y = i;
			FillConsoleOutputAttribute( out, info.wAttributes, len, c, &num );
			FillConsoleOutputCharacter( out, ( WCHAR )( ' ' ), len, c, &num );
		}

		SetCursorPosition( 0, 0 );
	}

	int Console::CursorLeft()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return info.dwCursorPosition.X;
	}

	int Console::CursorTop()
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );
		return info.dwCursorPosition.Y;
	}

	void Console::SetCursorPosition( int left, int top )
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo( out, &info );

		if ( info.dwSize.X <= left ) left = info.dwSize.X - 1;
		else if ( left < 0 ) left = 0;
		if ( info.dwSize.Y <= top ) top = info.dwSize.Y - 1;
		else if ( top < 0 ) top = 0;

		COORD cp = { ( SHORT )left, ( SHORT )top, };
		SetConsoleCursorPosition( out, cp );
	}

	void Console::Lock( bool lock )
	{
		if ( lock ) LockWindowUpdate( hwnd );
		else
		{
			LockWindowUpdate( nullptr );
			Sleep( 2 );
		}
	}

	void Console::EOLWrap( bool on )
	{
		DWORD mode;
		GetConsoleMode( out, &mode );
		if ( on ) mode |= ENABLE_WRAP_AT_EOL_OUTPUT;
		else mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
		SetConsoleMode( out, mode );
	}

	void Console::FlushKeys()
	{
		for ( int i = 0; i < 256; ++i ) GetAsyncKeyState( i );
		while ( _kbhit() ) ( void )_getch();
	}

	void Console::Show( int x, int y, wchar_t symbol )
	{
		static bool imbued;
		if ( !imbued )
		{
			std::wcout.imbue( std::locale( ".OCP" ) );
			imbued = true;
		}
		SetCursorPosition( x, y );
		Show( symbol );
	}

	void Console::DrawBox( int left, int top, int width, int height, bool dbl )
	{
		wchar_t const * SingleLine = L"┌─┐│└┘",
			*DoubleLine = L"╔═╗║╚╝",
			*Set = dbl ? DoubleLine : SingleLine;
		int row = 0, col = 0;
		Show( left, top, Set[ 0 ] );
		for ( ; col < width - 2; ++col ) Show( Set[ 1 ] );
		Show( Set[ 2 ] );

		int x = left + width - 1, y = top + 1;
		for ( ; row < height - 2; ++row, ++y )
		{
			Show( left, y, Set[ 3 ] );
			Show( x, y, Set[ 3 ] );
		}

		y = top + height - 1;
		Show( left, y, Set[ 4 ] );
		for ( col = 0; col < width - 2; ++col ) Show( Set[ 1 ] );
		Show( Set[ 5 ] );
	}

	char const * Console::RandomName()
	{
		const int Min = 3, Max = 7;
		static char name[ Max + 1 ];

		const char *Cons = "bcdfghjklmnpqrstvwxyz", *Vows = "aeiouy";
		const int NumCons = ( int )strlen( Cons ), NumVows = ( int )strlen( Vows );

		int nameLen = rand() % ( Max - Min + 1 ) + Min;
		bool putAConsHere = 0 != rand() % 2;
		for ( int i = 0; i < nameLen; ++i, putAConsHere = !putAConsHere )
			name[ i ] = putAConsHere ? Cons[ rand() % NumCons ] : Vows[ rand() % NumVows ];

		name[ nameLen ] = '\0';
		name[ 0 ] = name[ 0 ] - 'a' + 'A';
		return name;
	}

	void Console::WordWrap( int x, int y, int w, char const * const t )
	{
		auto count = strlen( t );
		for ( decltype( count ) i = ( ( decltype( count ) )( 0u ) ), j; i < count; i = j )
		{
			for ( j = i + w; j < count && ' ' != t[ j ]; --j );
			if ( count < j ) j = count;

			Console::SetCursorPosition( x, y++ );
			for ( auto k = i; k < j; ++k ) std::cout << t[ k ];
			while ( ' ' == t[ j ] ) ++j;
		}
	}

	PC::PC( bool go )
	{
		QueryPerformanceFrequency( ( LARGE_INTEGER * )&freq );
		if ( go ) Start();
	}

	void PC::Start()
	{
		QueryPerformanceCounter( ( LARGE_INTEGER * )&start );
	}

	double PC::Finish() const
	{
		long long finish;
		QueryPerformanceCounter( ( LARGE_INTEGER * )&finish );
		return ( finish - start ) / ( double )freq;
	}

}

// ☻☺ トニー ☺☻ -- Y:2015年 //