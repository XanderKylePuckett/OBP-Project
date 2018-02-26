#include "GameState.h"
#include "Cell.h"

std::vector< BaseObject* > GameState::objects;

GameState::GameState()
{

}

GameState::~GameState()
{
	for ( int i = 0; i < ( int )objects.size(); ++i )
		delete objects[ i ];
}

void GameState::Enter( void )
{
	// < Reset Objects > //
	for ( int i = 0; i < ( int )objects.size(); ++i ) delete objects[ i ];
	objects.resize( 2 );
	objects[ 0 ] = new Player( BaseObject::ToCells( "LOLOL\nOLOLO\nLOLOL", System::ConsoleColor::Green, System::ConsoleColor::DarkGreen ), "missing objectscfg.txt" );
	objects[ 1 ] = new Enemy( BaseObject::ToCells( " ROFL \nCOPTER", System::ConsoleColor::Red, System::ConsoleColor::DarkRed ) );
	// ^ Reset Objects ^ //

	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::GAME_BACKGROUND );
	int i = 0;
	for ( ; i < TRANSITION; ++i )
	{
		System::Console::SetCursorPosition( rand() % System::Console::WindowWidth(),
											rand() % System::Console::WindowHeight() );
		std::cout << ' ';
	}

	Choose();

	// TODO : THE NOTHING FILE
#if 0
	std::ofstream fout;
	fout.open( "choices.txt", std::ios_base::out | std::ios_base::trunc );
	if ( fout.is_open() )
	{
		Player* player = dynamic_cast< Player* >( objects[ 0 ] );
		fout << ( int )objects.size() << '\n'
			<< player->GetText() << '\t'
			<< ( int )( player->GetForeground() ) << '\t'
			<< ( int )( player->GetBackground() ) << '\t'
			<< player->GetX() << '\t'
			<< player->GetY() << '\t'
			<< player->GetName() << '\t'
			<< player->GetScore() << '\t'
			<< player->GetDifficulty() << '\n';
		for ( i = 1; i < ( int )objects.size(); ++i )
			fout << objects[ i ]->GetText() << '\t'
			<< ( int )( objects[ i ]->GetForeground() ) << '\t'
			<< ( int )( objects[ i ]->GetBackground() ) << '\t'
			<< objects[ i ]->GetX() << '\t'
			<< objects[ i ]->GetY() << '\n';
		fout.close();
	}
#endif

	PlaySound( TEXT( "song.wav" ), NULL, SND_FILENAME | SND_ASYNC );
}
void GameState::Input( void )
{
	if ( GetAsyncKeyState( VK_ESCAPE ) )
		Game::ChangeState( MENU_STATE );

	for ( int i = 0; i < ( int )objects.size(); ++i )
		if ( objects[ i ]->IsAlive() )
			objects[ i ]->Input();
}
void GameState::Update( Frame _frame )
{
	for ( int i = 0; i < ( int )objects.size(); ++i )
		if ( objects[ i ]->IsAlive() )
			objects[ i ]->Update( _frame );

	std::vector< BaseObject* >::iterator iter = objects.begin();
	while ( iter != objects.end() )
		if ( !( *iter )->IsAlive() )
		{
			delete *iter;
			iter = objects.erase( iter );
		}
		else ++iter;
}
void GameState::Render( void ) const
{
	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::GAME_BACKGROUND );
	System::Console::Clear();
	std::vector< Cell<> > stars = Game::GetStars();

	int i = 0;
	for ( ; i < ( int )stars.size(); ++i )
		stars[ i ].Show( 0, 0 );

	for ( i = 0; i < ( int )objects.size(); ++i )
		if ( objects[ i ]->IsAlive() )
			objects[ i ]->Render();

	int _console_height_m1 = System::Console::WindowHeight() - 1;
	int _console_width_m1 = System::Console::WindowWidth() - 1;

	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::HUD_COLOR ) );
	System::Console::BackgroundColor( ( WORD )( System::ConsoleColor::GAME_BACKGROUND ) );
	for ( i = 0, System::Console::SetCursorPosition( 1, 0 ); i < _console_width_m1 - 1; ++i )
		std::cout << _box_hor;
	for ( i = 0, System::Console::SetCursorPosition( 1, _console_height_m1 ); i < _console_width_m1 - 1; ++i )
		std::cout << _box_hor;
	for ( i = 1; i < _console_height_m1; ++i )
	{
		System::Console::SetCursorPosition( 0, i );
		std::cout << _box_ver;
		System::Console::SetCursorPosition( _console_width_m1, i );
		std::cout << _box_ver;
	}
	System::Console::SetCursorPosition( 0, 0 );
	std::cout << _box_corner;
	System::Console::SetCursorPosition( 0, _console_height_m1 );
	std::cout << _box_corner;
	System::Console::SetCursorPosition( _console_width_m1, 0 );
	std::cout << _box_corner;
	System::Console::SetCursorPosition( _console_width_m1, _console_height_m1 );
	std::cout << _box_corner;

	System::Console::ResetColor();
}
void GameState::Exit( void )
{
	PlaySound( NULL, NULL, SND_FILENAME | SND_ASYNC );
	System::Console::Lock( true );
	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::GAME_BACKGROUND );
	System::Console::ForegroundColor( ( WORD )System::ConsoleColor::HUD_COLOR );
	System::Console::Clear();

	Player* p = dynamic_cast< Player* >( objects[ 0 ] );

	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 8,
										( System::Console::WindowHeight() >> 1 ) - 3 );
	std::cout << "Game Over";

	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 8,
										( System::Console::WindowHeight() >> 1 ) - 1 );
	std::cout << "Player: " << p->GetName();

	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 8,
										( System::Console::WindowHeight() >> 1 ) );
	std::cout << "Score: " << p->GetScore();

	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 8,
										( System::Console::WindowHeight() >> 1 ) + 1 );
	std::cout << "Difficulty: " << p->GetDifficulty();



	std::ofstream scoresOut;
	scoresOut.open( "scores.txt", std::ios_base::out | std::ios_base::app );
	if ( scoresOut.is_open() )
	{
		scoresOut << "Name: " << p->GetName() << '\t'
			<< "Score: " << p->GetScore() << '\t'
			<< "Difficulty: " << p->GetDifficulty() << '\n';
		scoresOut.close();
	}

	scoresOut.open( "SCORES.BIN", std::ios_base::out | std::ios_base::app | std::ios_base::binary );
	if ( scoresOut.is_open() )
	{
		PlayerInfo info;
		strcpy_s( info.name, 32, p->GetName() );
		info.score = p->GetScore();
		info.diff = p->GetDifficulty();
		scoresOut.write( ( char* )&info, sizeof( PlayerInfo ) );
		scoresOut.close();
	}


	System::Console::Lock( false );
	Sleep( 450 );
	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 12,
										System::Console::WindowHeight() - 3 );
	std::cout << "Press Enter to Continue";
	System::Console::FlushKeys();

	bool keyPressed = true;
	for ( ;; )
		if ( GetAsyncKeyState( VK_RETURN ) )
		{
			if ( !keyPressed ) return;
		}
		else keyPressed = false;
}

void GameState::Init( void )
{
	objects.resize( 2 );

	objects[ 0 ] = new Player( BaseObject::ToCells( "LOLOL\nOLOLO\nLOLOL",
							   System::ConsoleColor::Green,
							   System::ConsoleColor::DarkGreen ),
							   "missing objectscfg.txt" );

	objects[ 1 ] = new Enemy( BaseObject::ToCells( " ROFL \nCOPTER",
							  System::ConsoleColor::Red,
							  System::ConsoleColor::DarkRed ) );
}

void GameState::Choose()
{
	std::ifstream fin;
	fin.open( "objectscfg.txt", std::ios_base::in );
	if ( fin.is_open() )
	{
		fin.seekg( std::ios_base::end );
		unsigned int length = ( unsigned int )( fin.tellg() );
		if ( 0 != length )
		{
			fin.seekg( std::ios_base::beg );

			int numFileObjects = 0;
			fin >> numFileObjects;
			fin.ignore( INT_MAX, '\n' );
			char buffer[ 64 ];
			int fg, bg;

			const int __numFileObjects = numFileObjects;
			BaseObject** fileObjects = new BaseObject*[ __numFileObjects ];
			int i = 0;
			for ( ; i < __numFileObjects; ++i )
			{
				fin.getline( buffer, INT_MAX, '\t' );
				fin >> fg >> bg;
				fin.ignore( INT_MAX, '\n' );

				fileObjects[ i ] = new BaseObject( BaseObject::ToCells( buffer,
												   ( System::ConsoleColor )fg,
												   ( System::ConsoleColor )bg ) );

				fileObjects[ i ]->SetX( ( System::Console::WindowWidth() >> 1 )
										- ( fileObjects[ i ]->GetWidth() >> 1 ) );
				fileObjects[ i ]->SetY( System::Console::WindowHeight() / 3 + 4 );
			}

			bool pickingShip = true, keyPressed = false, keyPressed2 = false;
			int currItem = 0;

			for ( int x = 0; x < 2; ) // x=0 >> player /// x=1 >> enemy
				for ( pickingShip = true, currItem = 0, keyPressed = true, keyPressed2 = true; pickingShip; )
				{
					System::Console::FlushKeys();
					if ( GetAsyncKeyState( VK_DOWN ) || GetAsyncKeyState( VK_RIGHT ) )
					{
						System::Console::FlushKeys();
						if ( !keyPressed )
						{
							keyPressed = true;
							++currItem;
							if ( __numFileObjects <= currItem ) currItem = 0;
						}
					}
					else if ( GetAsyncKeyState( VK_UP ) || GetAsyncKeyState( VK_LEFT ) )
					{
						System::Console::FlushKeys();
						if ( !keyPressed )
						{
							keyPressed = true;
							--currItem;
							if ( currItem < 0 ) currItem = __numFileObjects - 1;
						}
					}
					else keyPressed = false;


					System::Console::FlushKeys();
					if ( GetAsyncKeyState( VK_RETURN ) )
					{
						System::Console::FlushKeys();
						if ( !keyPressed2 )
						{
							keyPressed2 = true;
							if ( 0 == x && currItem < __numFileObjects )
							{
								std::string nameBuffer;
								delete objects[ x ];

								objects[ x ] = new Player( fileObjects[ currItem ]->GetShape(), "NO_NAME" );

								for ( ;; )
								{
									System::Console::Lock( true );
									System::Console::BackgroundColor( ( WORD )System::ConsoleColor::GAME_BACKGROUND );
									System::Console::ForegroundColor( ( WORD )( ( System::ConsoleColor::HUD_COLOR )
																	  & ~( FOREGROUND_INTENSITY ) ) );
									System::Console::Clear();
									System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 6,
																		System::Console::WindowHeight() >> 1 );
									std::cout << "ENTER NAME:";
									System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 10,
																		( System::Console::WindowHeight() >> 1 ) + 2 );
									System::Console::CursorVisible( true );
									System::Console::FlushKeys();
									System::Console::Lock( false );

									std::cin.get( buffer, 30, '\n' );
									if ( !std::cin.good() )
									{
										std::cin.clear();
										std::cin.ignore( INT_MAX, '\n' );
										//continue;
										//strcpy_s( buffer, 30, "Player" ); // DefaultName: "Player"
										nameBuffer = "Player";
										break;
									}
									else nameBuffer = buffer;
									std::cin.ignore( INT_MAX, '\n' );
									break;
								}
								System::Console::CursorVisible( false );
								unsigned int o = 0;
								for ( ; o < nameBuffer.length(); ++o )
									if ( '\t' == nameBuffer[ o ] ) nameBuffer[ o ] = ' ';
								dynamic_cast< Player* >( objects[ x ] )->SetName( nameBuffer );

								// if name is all spaces, set name to default "Player"
								bool empty = true;
								for ( o = 0; o < nameBuffer.length(); ++o )
									if ( ' ' != nameBuffer[ o ] ) empty = false;
								if ( empty ) dynamic_cast< Player* >( objects[ x ] )->SetName( "Player" );
							}
							else if ( currItem < __numFileObjects && x < ( int )objects.size() )
							{
								delete objects[ x ];

								objects[ x ] = new Enemy( fileObjects[ currItem ]->GetShape() );
							}

							currItem = 0; ++x;
							pickingShip = false;
						}
					}
					else keyPressed2 = false;


					System::Console::Lock( true );
					System::Console::BackgroundColor( ( WORD )System::ConsoleColor::GAME_BACKGROUND );
					System::Console::ForegroundColor( ( WORD )System::ConsoleColor::HUD_COLOR );
					System::Console::Clear();

					static const char* const playerLine = "Pick your ship", *enemyLine = "Pick the enemy ship";

					System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
														- ( ( int )strlen( 0 == x ? playerLine : enemyLine ) >> 1 ),
														System::Console::WindowHeight() / 3 );
					std::cout << ( 0 == x ? playerLine : enemyLine );
					System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 15,
														System::Console::WindowHeight() / 3 + 2 );
					std::cout << " << prev              next >> ";
					System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
														- ( currItem < 11 ? 2 : 3 ),
														System::Console::WindowHeight() / 3 + 2 );
					std::cout << currItem + 1;
					System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ),
														System::Console::WindowHeight() / 3 + 2 );
					std::cout << "/ " << __numFileObjects;
					fileObjects[ currItem ]->Show();
					System::Console::ResetColor();
					System::Console::Lock( false );
				}


			for ( i = 0; i < __numFileObjects; ++i )
				delete fileObjects[ i ];
			delete[ ] fileObjects;
		}
		fin.close();
	}

	objects[ 0 ]->SetX( System::Console::WindowWidth() / 6 );
	objects[ 0 ]->SetY( System::Console::WindowHeight() >> 1 );

	objects[ 1 ]->SetX( System::Console::WindowWidth() * 5 / 6 );
	objects[ 1 ]->SetY( System::Console::WindowHeight() >> 1 );
}

// ☻☺ トニー ☺☻ -- Y:2015年 //