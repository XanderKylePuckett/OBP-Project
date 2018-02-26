#pragma once
#include "BaseObject.h"

class Missile : public BaseObject
{
private:

	std::vector<int> vel;
	bool enemyMissile;

public:
	Missile();
	Missile( System::ConsoleColor _color );
	~Missile();

	void Input( void );
	void Update( Frame _frame );
	void Render( void ) const;

	int GetVelX( void ) const
	{
		return vel[ 0 ];
	}
	int GetVelY( void ) const
	{
		return vel[ 1 ];
	}

	bool IsEnemyMissile( void )
	{
		return enemyMissile;
	}
	void IsEnemyMissile( bool _enemyMissile )
	{
		enemyMissile = _enemyMissile;
	}

	void SetVelX( int _x )
	{
		vel[ 0 ] = _x;
	}
	void SetVelY( int _y )
	{
		vel[ 1 ] = _y;
	}
	void SetVel( int _x, int _y )
	{
		SetVelX( _x );
		SetVelY( _y );
	}

	Direction GetDir( void ) const;
};

// ☻☺ トニー ☺☻ -- Y:2015年 //