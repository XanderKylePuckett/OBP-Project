#include "Game.h"
#include "DList.h"

unsigned int randSeed;

int main( int argc, char* argv[ ] )
{
	( void )argc;
	( void )argv;

	( void )_CrtSetDbgFlag( ( int )( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ) );
	( void )_CrtSetBreakAlloc( -1l );

	randSeed = ( unsigned int )time( nullptr );
	srand( randSeed );
	( void )rand();
	srand( ( unsigned int )rand() );
	( void )rand();

#pragma region DLIST_TEST
#if 0
	{
		try
		{
			typedef DList<char> OurDList;
			OurDList testDList; // 
			testDList.push_front( '#' ); // #
			testDList.push_back( '@' ); // #@
			testDList.clear(); // 
			testDList.push_back( 'i' ); // i
			testDList.push_front( 'r' ); // ri
			testDList.push_front( 'h' ); // hri
			testDList.push_back( 's' ); // hris
			testDList.push_front( 't' ); // thris
			testDList.erase( 2 ); // this
			testDList.erase( 0 ); // his
			testDList.erase( 2 ); // hi
			for ( int i = 0; i < testDList.getSize(); i++ )
				std::cout << testDList[ i ]; // "hi"
			testDList.erase( 0 ); // i
			testDList.erase( 60 ); // 
			testDList.push_front( '!' ); // !
			testDList.push_back( '\"' ); // !"
			testDList.erase( 1 ); // !
			for ( int i = 0; i < testDList.getSize(); i++ )
				std::cout << testDList[ i ]; // "!"
			std::cout << std::flush << std::endl;
			system( "pause" );
			testDList.erase( -3 );
}
		catch ( std::exception e )
		{
			std::cerr << "\n\n" << "exception caught: " << e.what() << std::endl;
			system( "pause" );
		}
	}
#endif
#pragma endregion

	( void )SetWindowPos( GetConsoleWindow(), nullptr, 56, 16, 0, 0, ( UINT )( SWP_NOSIZE | SWP_NOZORDER ) );
	System::Console::SetWindowSize( 176, 46 );
	System::Console::SetBufferSize( System::Console::WindowWidth(), System::Console::WindowHeight() );
	System::Console::Lock( true );
	System::Console::EOLWrap( false );
	System::Console::CursorVisible( false );
	System::Console::BackgroundColor( ( WORD )( System::ConsoleColor::Black ) );
	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::Gray ) );
	System::Console::Clear();
	System::Console::FlushKeys();
	System::Console::Lock( false );

	{
		Game g;
		g.Play();
	}

	System::Console::SetCursorPosition( 0, ( System::Console::WindowHeight() - 1 ) );
	System::Console::FlushKeys();
	System::Console::ResetColor();
	System::Console::Lock( true );
	System::Console::EOLWrap( true );
	System::Console::CursorVisible( true );
	System::Console::Clear();
	System::Console::FlushKeys();
	System::Console::Lock( false );
	return 0;
}

// ☻☺ トニー ☺☻ -- Y:2015年 //