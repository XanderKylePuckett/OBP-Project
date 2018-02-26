#pragma once
#include "stdafx.h"
#include "Cell.h"
#if DLIST_CELLS
#include "DList.h"
#endif

class GameState;

enum OBJECT_ID
{
	Obj_BaseObject,
	Obj_Player,
	Obj_Enemy,
	Obj_Missile,
	Obj_NumObjIDs
};

class BaseObject
{
private:

	unsigned short width, height;
	int x, y;
	bool alive;
#if VECTOR_CELLS
	std::vector< Cell<> > shape;
#elif DLIST_CELLS
	DList< Cell<> > shape;
#endif
	OBJECT_ID objectID;

public:

	// Constructors
	BaseObject();
#if VECTOR_CELLS
	BaseObject( std::vector< Cell<> > _shape );
#elif DLIST_CELLS
	BaseObject( DList< Cell<> > _shape );
#endif

	// Trilogy of Evil for BaseObject class

	BaseObject( const BaseObject& _obj ); // Copy Constructor
	BaseObject& operator=( const BaseObject& _obj ); // Assignment Operator
	virtual ~BaseObject(); // Destructor


	// Accessors
	unsigned short GetWidth() const
	{
		return width;
	}
	unsigned short GetHeight() const
	{
		return height;
	}
	int GetX() const
	{
		return x;
	}
	int GetY() const
	{
		return y;
	}
	bool IsAlive() const
	{
		return alive;
	}
#if VECTOR_CELLS
	std::vector< Cell<> > GetShape( void ) const
	{
		return shape;
	}
#elif DLIST_CELLS
	DList< Cell<> > GetShape( void ) const
	{
		return shape;
	}
#endif
	OBJECT_ID GetObjectID( void ) const
	{
		return objectID;
	}

	// Mutators
	void SetX( int _x )
	{
		x = _x;
	}
	void SetY( int _y )
	{
		y = _y;
	}
	void IsAlive( bool _alive )
	{
		alive = _alive;
	}
#if VECTOR_CELLS
	void SetShape( std::vector< Cell<> > _shape );
#elif DLIST_CELLS
	void SetShape( DList< Cell<> > _shape );
#endif
	void SetObjectID( OBJECT_ID _objectID )
	{
		objectID = _objectID;
	}

	// Methods

private:
	void CalculateDimensions( void ); // Calculate width and height for BaseObject class

protected:
	bool OutOfBounds( Direction& _dir, int _vel ) const;
	bool Collides( Direction _dir, int _vel ) const;
	bool CellsCollision( int _newX, int _newY, BaseObject* _other ) const;

public:
	virtual void Move( Direction _dir = 0, int _vel = 1 );
	virtual void Input();
	virtual void Update( Frame _frame );
	virtual void Render() const;
	virtual void Show( void ) const; // Show method for BaseObject class

#if VECTOR_CELLS
	static std::vector< Cell<> > ToCells( const char * const _text, System::ConsoleColor _fg, System::ConsoleColor _bg );
	static std::vector< Cell<> > ToCells( std::string _text, System::ConsoleColor _fg, System::ConsoleColor _bg )
	{
		return ToCells( _text.c_str(), _fg, _bg );
	}
#elif DLIST_CELLS
	static DList< Cell<> > ToCells( const char * const _text, System::ConsoleColor _fg, System::ConsoleColor _bg );
	static DList< Cell<> > ToCells( std::string _text, System::ConsoleColor _fg, System::ConsoleColor _bg )
	{
		return ToCells( _text.c_str(), _fg, _bg );
	}
#endif

};

// ☻☺ トニー ☺☻ -- Y:2015年 //