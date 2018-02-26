#include "Game.h"

//States
#include "MenuState.h"
#include "GameState.h"
#include "HighScoresState.h"

BaseState** Game::allStates;
BaseState* Game::currentState;
std::vector<Cell<> > Game::stars;
byte Game::cheats;

Game::Game()
{
	stars.resize( ( ( ( size_t )rand() % 6 + 5 ) << 1 ) );
	CreateStars();

	//Set up the states
	allStates = new BaseState*[ NUMSTATES ];

	allStates[ MENU_STATE ] = new MenuState();
	allStates[ GAME_STATE ] = new GameState();
	allStates[ HIGHSCORES_STATE ] = new HighScoresState();

	for ( int i = 0; i < NUMSTATES; ++i )
	{
		allStates[ i ]->Init();
	}

	currentState = allStates[ MENU_STATE ];

	frame = ( Frame )0;
	//isPlaying = false;
	cheats &= ~CHEAT_ISPLAYING;

	keyPressed = false;
}

void Game::CreateStars()
{
	int i = 0, newX, newY;

	for ( ; i < ( int )stars.size(); i++ )
	{
		stars[ i ].bg = ( System::ConsoleColor )( rand() % 16 );
		do
		{
			stars[ i ].fg = ( System::ConsoleColor )( rand() % 16 );
		} while ( stars[ i ].fg == stars[ i ].bg );
		stars[ i ].sym = ( rand() % 2 == 1 ? '*' : 'o' );
		stars[ i ].oX = stars[ i ].oY = 0;
	}
	for ( i = 0; i < ( int )stars.size(); i++ )
	{
		for ( ;; )
		{
			newX = rand() % System::Console::WindowWidth();
			newY = rand() % System::Console::WindowHeight();

			if ( isUnique( i, newX, newY ) )
				break;
		}
		stars[ i ].oX = newX;
		stars[ i ].oY = newY;
	}
}

bool Game::isUnique( int _i, int _x, int _y )
{
	for ( int j = 0; j < _i; j++ )
	{
		if ( stars[ j ].oX == _x && stars[ j ].oY == _y )
			return false;
	}
	return true;
}

Game::~Game()
{

	for ( int i = 0; i < NUMSTATES; ++i )
	{
		delete allStates[ i ];
	}
	delete[ ] allStates;
}

void Game::Play( void )
{
	currentState->Enter();
	//for ( isPlaying = true; isPlaying; ++frame )
	for ( cheats |= CHEAT_ISPLAYING; cheats & CHEAT_ISPLAYING; ++frame )
	{
		Input();
		Update( frame );
		Render();
	}
	currentState->Exit();
}

void Game::Input()
{
	if ( GetAsyncKeyState( '1' ) || GetAsyncKeyState( VK_NUMPAD1 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			cheats ^= CHEAT_DISABLE_ENEMY_MOVEMENT;
		}
	}
	else if ( GetAsyncKeyState( '2' ) || GetAsyncKeyState( VK_NUMPAD2 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			cheats ^= CHEAT_DISABLE_ENEMY_SHOOT_MISSILES;
		}
	}
	else if ( GetAsyncKeyState( '3' ) || GetAsyncKeyState( VK_NUMPAD3 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			cheats ^= CHEAT_INCREMENT_SCORE;
		}
	}
	else if ( GetAsyncKeyState( '4' ) || GetAsyncKeyState( VK_NUMPAD4 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			cheats ^= CHEAT_DISABLE_ENEMY_COLLISION;
		}
	}
	else if ( GetAsyncKeyState( '5' ) || GetAsyncKeyState( VK_NUMPAD5 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			//cheats ^= CHEAT_UNUSED_32;
		}
	}
	else if ( GetAsyncKeyState( '6' ) || GetAsyncKeyState( VK_NUMPAD6 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			//cheats ^= CHEAT_UNUSED_64;
		}
	}
	else if ( GetAsyncKeyState( '7' ) || GetAsyncKeyState( VK_NUMPAD7 ) )
	{
		if ( !keyPressed )
		{
			keyPressed = true;
			//cheats ^= CHEAT_UNUSED_128;
		}
	}
	else keyPressed = false;

	currentState->Input();
}
void Game::Update( Frame _frame )
{
	currentState->Update( _frame );
}
void Game::Render()
{
	System::Console::Lock( true );
	currentState->Render();
	System::Console::SetCursorPosition( System::Console::WindowWidth() - 20, 0 );
	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::CHEATS_BG );
	System::Console::ForegroundColor( ( WORD )System::ConsoleColor::CHEATS_FG );
	std::cout << "Cheats: ";
	for ( short i = 7; i >= 0; --i ) std::cout << ( ( cheats & ( 1 << i ) ) ? '1' : '0' );
	System::Console::Lock( false );
}

void Game::ChangeState( STATE_ID _state )
{
	currentState->Exit();
	currentState = allStates[ _state ];
	System::Console::FlushKeys();
	currentState->Enter();
}

// ☻☺ トニー ☺☻ -- Y:2015年 //