#pragma once
#include "BaseState.h"
#include "BaseObject.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"

class GameState : public BaseState
{
private:
	static std::vector< BaseObject* > objects;
	const unsigned char _box_hor = ( unsigned char )205;
	const unsigned char _box_ver = ( unsigned char )186;
	const unsigned char _box_corner = ( unsigned char )219;
public:
	GameState();
	~GameState();

	static std::vector< BaseObject* >& GetObjects( void )
	{
		return objects;
	}

	void Enter( void );
	void Input( void );
	void Update( Frame _frame );
	void Render( void ) const;
	void Exit( void );
	void Init( void );

private:
	void Choose( void );
};

// ☻☺ トニー ☺☻ -- Y:2015年 //