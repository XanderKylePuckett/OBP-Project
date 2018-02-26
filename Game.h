#pragma once

#include "stdafx.h"
#include "Cell.h"

class BaseState;
class BaseObject;

enum STATE_ID
{
	MENU_STATE, GAME_STATE, HIGHSCORES_STATE, NUMSTATES
};

class Game
{
private:

	static std::vector< Cell<> > stars;

	Frame frame;

	static BaseState** allStates;
	static BaseState* currentState;

	void CreateStars( void );
	bool isUnique( int, int, int );

	static byte cheats;

	bool keyPressed;

public:
	Game();
	~Game();

	void Play( void );

	void Input( void );
	void Update( Frame _frame );
	void Render( void );

	static void ChangeState( STATE_ID _newState );

	static void StopGame( void )
	{
		//isPlaying = false;
		cheats &= ~CHEAT_ISPLAYING;
	}

	static std::vector< Cell<> > GetStars( void )
	{
		return stars;
	}

	static byte GetCheats( void )
	{
		return cheats;
	}
};

// ☻☺ トニー ☺☻ -- Y:2015年 //