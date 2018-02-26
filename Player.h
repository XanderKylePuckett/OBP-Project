#pragma once
#include "BaseObject.h"

struct PlayerInfo
{
	char name[ 32 ];
	int score;
	int diff;
};

class Player : public BaseObject
{
private:

	std::string name;
	int score, diff;
	Direction dir;

public:

	Player();
#if VECTOR_CELLS
	Player( std::vector< Cell<> > _shape, char const * const name, int score = 0, int diff = 0 );
#elif DLIST_CELLS
	Player( DList< Cell<> > _shape, char const * const name, int score = 0, int diff = 0 );
#endif

	Player( const Player& _obj ); // Copy constructor
	Player& operator=( const Player& _obj ); // Assignment operator
	~Player(); // Destructor


	// Accessors

	const char* const GetName() const
	{
		return name.c_str();
	}
	int GetScore() const
	{
		return score;
	}
	int GetDifficulty() const
	{
		return diff;
	}


	// Mutators

	void SetName( const char * const _name )
	{
		name = _name;
	}
	void SetName( std::string _name )
	{
		name = _name;
	}
	void SetScore( int _score )
	{
		score = _score;
	}
	void SetDifficulty( int _diff )
	{
		diff = _diff;
	}


	// Methods

	void Show() const;
	void Input();
	void Update( Frame _frame );
	void Render() const;

	void Shoot( Direction _dir ) const;

};

// ☻☺ トニー ☺☻ -- Y:2015年 //