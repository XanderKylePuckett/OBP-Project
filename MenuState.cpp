#include "MenuState.h"
#include "Game.h"

MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}


void MenuState::Enter( void )
{
	keyPressed = true;
	System::Console::FlushKeys();

	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::MENU_BACKGROUND );
	for ( int i = 0; i < TRANSITION; ++i )
	{
		System::Console::SetCursorPosition( rand() % System::Console::WindowWidth(),
											rand() % System::Console::WindowHeight() );
		std::cout << ' ';
	}
}
void MenuState::Input( void )
{
	if ( GetAsyncKeyState( VK_DOWN ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			++currItem;
			if ( MAINMENU_NUMITEMS <= currItem )
				currItem = 0;
		}
	}
	else if ( GetAsyncKeyState( VK_UP ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			--currItem;
			if ( currItem < 0 )
				currItem = MAINMENU_NUMITEMS - 1;
		}
	}
	else
		keyPressed = false;
}
void MenuState::Update( Frame _frame )
{
	( void )_frame;

	System::Console::FlushKeys();
	if ( GetAsyncKeyState( VK_RETURN ) )
	{
		System::Console::FlushKeys();
		switch ( currItem )
		{
			case 0:
				Game::ChangeState( GAME_STATE );
				break;
			case 1:
				break;
			case 2:
				Game::ChangeState( HIGHSCORES_STATE );
				break;
			case 3:
				Game::StopGame();
				break;
			default:
				break;
		}
	}
}
void MenuState::Render( void ) const
{
	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::MENU_BACKGROUND );
	System::Console::Clear();

	for ( int i = 0; i < MAINMENU_NUMITEMS; ++i )
	{
		if ( i == currItem )
		{
			System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 11,
												( System::Console::WindowHeight() >> 1 ) - 3 + i );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::MENU_SELECTEDCOLOR );
			std::cout << "---> ";
		}
		else
		{
			System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 6,
												( System::Console::WindowHeight() >> 1 ) - 3 + i );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::MENU_ITEMCOLOR );
		}
		std::cout << menuItem[ i ];
	}

	System::Console::ForegroundColor( ( WORD )System::ConsoleColor::MENU_DESCCOLOR );
	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
										- ( ( int )strlen( desc[ currItem ] ) >> 1 ) - 4,
										( System::Console::WindowHeight() >> 2 ) * 3 );

	std::cout << desc[ currItem ];

	System::Console::ResetColor();
}
void MenuState::Exit( void )
{
	keyPressed = false;
}
void MenuState::Init( void )
{
	keyPressed = false;

	menuItem[ 0 ] = "Play";
	menuItem[ 1 ] = "Options";
	menuItem[ 2 ] = "Scores";
	menuItem[ 3 ] = "Exit";

	desc[ 0 ] = "Start a new game";
	desc[ 1 ] = "Options menu (currently unavailable).";
	desc[ 2 ] = "Show all scores from previous games";
	desc[ 3 ] = "Close the program";

	currItem = 0;
}

// ☻☺ トニー ☺☻ -- Y:2015年 //