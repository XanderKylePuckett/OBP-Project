#include "HighScoresState.h"
#include "Game.h"

namespace HS_Sort
{
	bool Name_Des( PlayerInfo& _a, PlayerInfo& _b )
	{
		return strcmp( _b.name, _a.name ) < 0;
	}
	bool Name_Asc( PlayerInfo& _a, PlayerInfo& _b )
	{
		return strcmp( _a.name, _b.name ) < 0;
	}
	bool Score_Des( PlayerInfo& _a, PlayerInfo& _b )
	{
		return _b.score < _a.score;
	}
	bool Score_Asc( PlayerInfo& _a, PlayerInfo& _b )
	{
		return _a.score < _b.score;
	}
	bool Diff_Des( PlayerInfo& _a, PlayerInfo& _b )
	{
		return _b.diff < _a.diff;
	}
	bool Diff_Asc( PlayerInfo& _a, PlayerInfo& _b )
	{
		return _a.diff < _b.diff;
	}
}

HighScoresState::HighScoresState()
{
}

HighScoresState::~HighScoresState()
{
}

void HighScoresState::Enter( void )
{
	System::Console::BackgroundColor( ( WORD )System::ConsoleColor::SCORES_BACKGROUND );
	System::Console::ForegroundColor( ( WORD )System::ConsoleColor::SCORES_FOREGROUND );
	for ( int i = 0; i < TRANSITION; ++i )
	{
		System::Console::SetCursorPosition( rand() % System::Console::WindowWidth(),
											rand() % System::Console::WindowHeight() );
		std::cout << ' ';
	}

	System::Console::FlushKeys();

#define SINGLEREAD 1
#if SINGLEREAD
	int size = 0;

	std::ifstream bin;
	bin.open( "SCORES.BIN", std::ios_base::in | std::ios_base::binary );
	if ( bin.is_open() )
	{
		bin.seekg( 0, std::ios_base::end );
		size = ( int )bin.tellg() / ( int )( sizeof( PlayerInfo ) );
		bin.seekg( 0, std::ios_base::beg );

		if ( size > 0 )
		{
			scores.resize( ( size_t )size );
			bin.read( ( char* )&scores[ 0 ], size * sizeof( PlayerInfo ) );
			bin.close();
		}
		else
		{
			System::Console::BackgroundColor( ( WORD )System::ConsoleColor::SCORES_BACKGROUND );
			System::Console::Clear();
			std::string err = "No Highscore Data";
			System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
												- ( ( int )err.length() >> 1 ),
												System::Console::WindowHeight() >> 1 );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::ERROR_COLOR );
			std::cout << err;
			System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 2 );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::SCORES_FOREGROUND );
			system( "pause" );
			System::Console::ResetColor();
			bin.close();
			Game::ChangeState( MENU_STATE );
		}
	}
	else
	{
		System::Console::BackgroundColor( ( WORD )System::ConsoleColor::SCORES_BACKGROUND );
		System::Console::Clear();
		std::string err = "Error reading highscores file: SCORES.BIN";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
											- ( ( int )err.length() >> 1 ),
											System::Console::WindowHeight() >> 1 );
		System::Console::ForegroundColor( ( WORD )System::ConsoleColor::ERROR_COLOR );
		std::cout << err;
		System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 2 );
		System::Console::ForegroundColor( ( WORD )System::ConsoleColor::SCORES_FOREGROUND );
		system( "pause" );
		System::Console::ResetColor();
		Game::ChangeState( MENU_STATE );
	}

#else
	std::ifstream bin;
	bin.open( "SCORES.BIN", std::ios_base::in | std::ios_base::binary );
	if ( bin.is_open() )
	{
		bin.seekg( 0, std::ios_base::end );
		if ( ( int )bin.tellg() == 0 )
		{
			System::Console::BackgroundColor( ( WORD )System::ConsoleColor::SCORES_BACKGROUND );
			System::Console::Clear();
			std::string err = "No Highscore Data";
			System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
												- ( ( int )err.length() >> 1 ),
												System::Console::WindowHeight() >> 1 );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::ERROR_COLOR );
			std::cout << err;
			System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 2 );
			System::Console::ForegroundColor( ( WORD )System::ConsoleColor::SCORES_FOREGROUND );
			system( "pause" );
			System::Console::ResetColor();
			bin.close();
			Game::ChangeState( MENU_STATE );
		}
		else
		{
			scores.resize( ( int )bin.tellg() / ( int )( sizeof( PlayerInfo ) ) );
			bin.seekg( 0, std::ios_base::beg );
			for ( int i = 0; !bin.eof(); i++ )
				bin.read( ( char* )&scores[ i ], sizeof( PlayerInfo ) );
			bin.close();
		}
	}
	else
	{
		System::Console::BackgroundColor( ( WORD )System::ConsoleColor::SCORES_BACKGROUND );
		System::Console::Clear();
		std::string err = "Error reading highscores file: SCORES.BIN";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 )
											- ( ( int )err.length() >> 1 ),
											System::Console::WindowHeight() >> 1 );
		System::Console::ForegroundColor( ( WORD )System::ConsoleColor::ERROR_COLOR );
		std::cout << err;
		System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 2 );
		System::Console::ForegroundColor( ( WORD )System::ConsoleColor::SCORES_FOREGROUND );
		system( "pause" );
		System::Console::ResetColor();
		Game::ChangeState( MENU_STATE );
	}
#endif

	if ( 6u <= scores.size() )
	{
		char numberSix[ 32 ] = "Number Six";

		std::ofstream bout; bout.open( "SCORES.BIN", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
		if ( bout.is_open() )
		{
			bout.write( ( char* )&scores[ 0 ], ( long long )scores.size() * sizeof( PlayerInfo ) );

			bout.seekp( 5 * sizeof( PlayerInfo ) );
			bout.write( ( char* )&numberSix, 32 );

			bout.close();
		}

		strcpy_s( scores[ 5 ].name, 32, numberSix );
	}

#if 0
	// Randomize Scores
	std::ofstream bout;
	bout.open( "SCORES.BIN", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
	PlayerInfo tempInfo;
	int _r_;
	strcpy_s( tempInfo.name, 32, "Player" );
	tempInfo.diff = 0;
	WORD _l_ = ( WORD )( rand() % 51 + 50 );
	if ( bout.is_open() )
	{
		for ( WORD _b_ = 0; _b_ < _l_; ++_b_ )
		{
			tempInfo.score = ( int )( ( ( ( ( long long )rand() << 3 ) - ( ( long long )rand() >> 2 ) ) << 8 ) >> 16 ) + ( rand() << 1 ) - ( rand() >> 2 );
			_r_ = rand() % 3 - 1;
			if ( _r_ < 0 ) tempInfo.score *= ( rand() % 3 ) ? 1 : -1;
			if ( 0 == _r_ ) tempInfo.score = ( rand() % 3 ) ? 0 : tempInfo.score;
			bout.write( ( char* )&tempInfo, sizeof( PlayerInfo ) );
		}
		bout.close();
	}
#endif

	sort = 1;
	SetStats();
	keyPressed = true;
	currPage = 0;
	numPages = ( unsigned int )scores.size() / MAXSCORES;
	if ( scores.size() % MAXSCORES ) ++numPages;
	if ( 0u < scores.size() ) std::sort( scores.begin(), scores.end(), HS_Sort::Score_Des );
}
void HighScoresState::Input( void )
{
	if ( 0u < scores.size() )
	{
		System::Console::FlushKeys();
		if ( GetAsyncKeyState( VK_F1 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Score_Des );
			sort = 1;
		}
		if ( GetAsyncKeyState( VK_F2 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Score_Asc );
			sort = 2;
		}
		if ( GetAsyncKeyState( VK_F3 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Name_Des );
			sort = 3;
		}
		if ( GetAsyncKeyState( VK_F4 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Name_Asc );
			sort = 4;
		}
		if ( GetAsyncKeyState( VK_F5 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Diff_Des );
			sort = 5;
		}
		if ( GetAsyncKeyState( VK_F6 ) )
		{
			std::sort( scores.begin(), scores.end(), HS_Sort::Diff_Asc );
			sort = 6;
		}
		if ( GetAsyncKeyState( VK_F9 ) ) SaveScores();
	}

	System::Console::FlushKeys();
	if ( GetAsyncKeyState( VK_ESCAPE ) )
	{
		System::Console::FlushKeys();
		Game::ChangeState( MENU_STATE );
	}

#if 1

	System::Console::FlushKeys();
	if ( GetAsyncKeyState( VK_DOWN ) || GetAsyncKeyState( VK_RIGHT ) )
	{
		System::Console::FlushKeys();
		if ( !keyPressed )
		{
			keyPressed = true;
			++currPage;
			if ( ( int )numPages <= currPage ) currPage = 0;
		}
	}
	else if ( GetAsyncKeyState( VK_UP ) || GetAsyncKeyState( VK_LEFT ) )
	{
		System::Console::FlushKeys();
		if ( !keyPressed )
		{
			keyPressed = true;
			--currPage;
			if ( currPage < 0 ) currPage = ( int )numPages - 1;
		}
	}
	else keyPressed = false;
#endif
}
void HighScoresState::Update( Frame _frame )
{
	( void )_frame;
}
void HighScoresState::Render( void ) const
{
	System::Console::BackgroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) );
	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	System::Console::Clear();

	System::Console::SetCursorPosition( 11, 2 );
	std::cout << "< Scores >";
	System::Console::SetCursorPosition( 11, 3 );
	std::cout << "<< " << currPage + 1 << '/' << numPages << " >>";
	System::Console::SetCursorPosition( 10, 5 );
	std::cout << "Player Name";
	System::Console::SetCursorPosition( 40, 5 );
	std::cout << "Score";
	System::Console::SetCursorPosition( 60, 5 );
	std::cout << "Difficulty";

	unsigned int size = ( unsigned int )scores.size();
	if ( MAXSCORES < size ) size = MAXSCORES;
	size += MAXSCORES * ( unsigned int )currPage;
	for ( int i = ( int )MAXSCORES * currPage; i < ( int )size; ++i )
	{
		if ( i >= ( int )scores.size() ) break;
		System::Console::SetCursorPosition( 2, 7 + i - ( ( int )MAXSCORES * currPage ) );
		std::cout << i + 1 << ':';
		System::Console::SetCursorPosition( 10, 7 + i - ( ( int )MAXSCORES * currPage ) );
		std::cout << scores[ i ].name;
		System::Console::SetCursorPosition( 40, 7 + i - ( ( int )MAXSCORES * currPage ) );
		std::cout << scores[ i ].score;
		System::Console::SetCursorPosition( 60, 7 + i - ( ( int )MAXSCORES * currPage ) );
		std::cout << scores[ i ].diff;
	}

	if ( 1 == sort || 2 == sort )
	{
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 1, 9 );
		std::cout << "SCORE";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 11 );
		if ( 2 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
		else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "MIN: " << minScore << " (" << minScoreName << ")";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 10 );
		if ( 1 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
		else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "MAX: " << maxScore << " (" << maxScoreName << ")";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 12 );
		System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "AVG: " << avgScore;
	}
	else if ( 5 == sort || 6 == sort )
	{
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 1, 9 );
		std::cout << "DIFFICULTY";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 11 );
		if ( 6 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
		else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "MIN: " << minDiff << " (" << minDiffName << ")";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 10 );
		if ( 5 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
		else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "MAX: " << maxDiff << " (" << maxDiffName << ")";
		System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) + 1, 12 );
		System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
		std::cout << "AVG: " << avgDiff;
	}

	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 11 );
	if ( 1 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F1 to sort by Score (Descending)";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 10 );
	if ( 2 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F2 to sort by Score (Ascending)";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 9 );
	if ( 3 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F3 to sort by Name (Descending)";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 8 );
	if ( 4 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F4 to sort by Name (Ascending)";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 7 );
	if ( 5 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F5 to sort by Difficulty (Descending)";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 6 );
	if ( 6 == sort ) System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );
	else System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	std::cout << "Press F6 to sort by Difficulty (Ascending)";

	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) ^ FOREGROUND_INTENSITY );

	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 4 );
	std::cout << "Press F9 to save highscores to a .txt file";
	System::Console::SetCursorPosition( 1, System::Console::WindowHeight() - 2 );
	std::cout << "Press Esc key to go back to the Main Menu";

	System::Console::ResetColor();
}
void HighScoresState::Exit( void )
{
	while ( 0 < scores.size() ) scores.pop_back();
}
void HighScoresState::Init( void )
{
}

void HighScoresState::SaveScores( void ) const
{
	System::Console::BackgroundColor( ( WORD )( System::ConsoleColor::SCORES_BACKGROUND ) );
	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::SCORES_FOREGROUND ) );
	int numScores = 0;
	char filename[ 64 ] = "scores.txt";

	for ( ;; )
	{
		System::Console::Clear();
		System::Console::SetCursorPosition( System::Console::WindowWidth() >> 2, ( System::Console::WindowHeight() >> 1 ) - 1 );
		std::cout << "How many highscores would you like to save? ";
		std::cin >> numScores;
		if ( std::cin.good() )
		{
			std::cin.ignore( INT_MAX, '\n' );
			break;
		}
		std::cin.clear();
		std::cin.ignore( INT_MAX, '\n' );
		numScores = 0;
	}

	System::Console::Clear();
	System::Console::SetCursorPosition( System::Console::WindowWidth() >> 2, ( System::Console::WindowHeight() >> 1 ) - 1 );
	std::cout << "Enter a name for the .txt file: ";
	std::cin.getline( filename, 64 );

	if ( numScores < 0 ) numScores = -numScores; // ignore sign of numScores
	if ( numScores > ( int )scores.size() ) numScores = ( int )scores.size(); // numScores will max out at scores.size()
	strcat_s( filename, 64, ".txt" );
	std::ofstream fout;
	fout.open( filename, std::ios_base::out | std::ios_base::trunc );

	System::Console::Clear();
	System::Console::SetCursorPosition( System::Console::WindowWidth() >> 2, ( System::Console::WindowHeight() >> 1 ) - 1 );
	if ( fout.is_open() )
	{
		fout << "Name: Score (Difficulty)\n\n";
		int i = 0;
		while ( i < numScores )
		{
			fout << i + 1 << ". ";
			fout << scores[ i ].name << ": ";
			fout << scores[ i ].score;
			fout << " (" << scores[ i ].diff << ")\n";
			++i;
		}

		std::cout << "Saved " << numScores << " highscores to " << filename;
		fout.close();
	}
	else std::cout << "Failed to write out to " << filename;

	System::Console::SetCursorPosition( System::Console::WindowWidth() >> 2, ( System::Console::WindowHeight() >> 1 ) + 1 );
	system( "pause" );
}
void HighScoresState::SetStats( void )
{
	maxScore = maxDiff = INT_MIN;
	minScore = minDiff = INT_MAX;
	int iAvgScore, iAvgDiff, i, tScore, tDiff, size = ( int )scores.size();
	iAvgScore = iAvgDiff = i = 0;
	while ( i < size )
	{
		tScore = scores[ i ].score;
		tDiff = scores[ i ].diff;
		iAvgScore += tScore;
		iAvgDiff += tDiff;
		if ( maxScore < tScore )
		{
			maxScore = tScore;
			strcpy_s( maxScoreName, 32, scores[ i ].name );
		}
		if ( tScore < minScore )
		{
			minScore = tScore;
			strcpy_s( minScoreName, 32, scores[ i ].name );
		}
		if ( maxDiff < tDiff )
		{
			maxDiff = tDiff;
			strcpy_s( maxDiffName, 32, scores[ i ].name );
		}
		if ( tDiff < minDiff )
		{
			minDiff = tDiff;
			strcpy_s( minDiffName, 32, scores[ i ].name );
		}
		++i;
	}

	if ( 0 < size )
	{
		avgScore = ( double )iAvgScore / size;
		avgDiff = ( double )iAvgDiff / size;
	}
	else maxScore = minScore = maxDiff = minDiff = 0;
}

// ☻☺ トニー ☺☻ -- Y:2015年 //