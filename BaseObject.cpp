#include "BaseObject.h"
#include "GameState.h"

BaseObject::BaseObject()
{
	SetObjectID( Obj_BaseObject );
	SetX( System::Console::CursorLeft() );
	SetY( System::Console::CursorTop() );
	SetShape( ToCells( "|O|", ( System::ConsoleColor )System::Console::ForegroundColor(), ( System::ConsoleColor )System::Console::BackgroundColor() ) );
	IsAlive( false );
}

#if VECTOR_CELLS
BaseObject::BaseObject( std::vector< Cell<> > _shape )
{
	SetObjectID( Obj_BaseObject );
	SetX( System::Console::CursorLeft() );
	SetY( System::Console::CursorTop() );
	SetShape( _shape );
	IsAlive( false );
}
#elif DLIST_CELLS
BaseObject::BaseObject( DList< Cell<> > _shape )
{
	SetObjectID( Obj_BaseObject );
	SetX( System::Console::CursorLeft() );
	SetY( System::Console::CursorTop() );
	SetShape( _shape );
	IsAlive( false );
}
#endif

// Trilogy of Evil for BaseObject class : Copy Constructor
BaseObject::BaseObject( const BaseObject& _obj )
{
	SetObjectID( Obj_BaseObject );
	SetX( _obj.x );
	SetY( _obj.y );
	SetShape( _obj.shape );
	IsAlive( false );
}

// Trilogy of Evil for BaseObject class : Assignment Operator
BaseObject& BaseObject::operator=( const BaseObject& _obj )
{
	if ( this != &_obj )
	{
		SetX( _obj.x );
		SetY( _obj.y );
		SetShape( _obj.shape );
		IsAlive( _obj.alive );
	}

	return *this;
}

// Trilogy of Evil for BaseObject class : Destructor
BaseObject::~BaseObject()
{
}

// Show method for BaseObject class
void BaseObject::Show( void ) const
{
#if VECTOR_CELLS
	for ( unsigned int i = 0; i < shape.size(); ++i ) shape[ i ].Show( x, y );
#elif DLIST_CELLS
	for ( int i = 0; i < shape.getSize(); ++i ) shape[ i ].Show( x, y );
#endif
	System::Console::ResetColor();
}

// Calculate width and height for BaseObject class
#if VECTOR_CELLS
void BaseObject::CalculateDimensions( void )
{
	int xMin = USHRT_MAX, xMax = 0, yMin = USHRT_MAX, yMax = 0;
	for ( unsigned int i = 0; i < shape.size(); ++i )
	{
		xMin = shape[ i ].oX < xMin ? shape[ i ].oX : xMin;
		xMax = shape[ i ].oX > xMax ? shape[ i ].oX : xMax;
		yMin = shape[ i ].oY < yMin ? shape[ i ].oY : yMin;
		yMax = shape[ i ].oY > yMax ? shape[ i ].oY : yMax;
	}
	if ( 0u == shape.size() ) width = height = 0;
	else
	{
		width = ( unsigned short )xMax - ( unsigned short )xMin + 1;
		height = ( unsigned short )yMax - ( unsigned short )yMin + 1;
	}
}
#elif DLIST_CELLS
void BaseObject::CalculateDimensions( void )
{
	int xMin = USHRT_MAX, xMax = 0, yMin = USHRT_MAX, yMax = 0;
	for ( int i = 0; i < shape.getSize(); ++i )
	{
		xMin = shape[ i ].oX < xMin ? shape[ i ].oX : xMin;
		xMax = shape[ i ].oX > xMax ? shape[ i ].oX : xMax;
		yMin = shape[ i ].oY < yMin ? shape[ i ].oY : yMin;
		yMax = shape[ i ].oY > yMax ? shape[ i ].oY : yMax;
	}
	if ( 0 == shape.getSize() ) width = height = 0;
	else
	{
		width = ( unsigned short )xMax - ( unsigned short )xMin + 1;
		height = ( unsigned short )yMax - ( unsigned short )yMin + 1;
	}
}
#endif

void BaseObject::Move( Direction _dir, int _vel )
{
	if ( ( _dir << 4 ) && _vel )
	{
		Direction inDir = _dir;

		if ( !OutOfBounds( _dir, _vel ) )
		{
			if ( !Collides( _dir, _vel ) )
			{
				if ( _dir & DIR_RIGHT ) x += _vel;
				if ( _dir & DIR_DOWN ) y += _vel;
				if ( _dir & DIR_LEFT ) x -= _vel;
				if ( _dir & DIR_UP ) y -= _vel;
			}
			Move( inDir, _vel - 1 );
		}
		else Move( inDir, _vel - 1 );
	}
}

bool BaseObject::OutOfBounds( Direction& _dir, int _vel ) const
{
	if ( _dir & DIR_RIGHT ) if ( System::Console::WindowWidth() - 1 < x + width + _vel ) _dir &= ~DIR_RIGHT;
	if ( _dir & DIR_DOWN ) if ( System::Console::WindowHeight() - 3 < y + height + _vel ) _dir &= ~DIR_DOWN;
	if ( _dir & DIR_LEFT ) if ( x - _vel < 1 ) _dir &= ~DIR_LEFT;
	if ( _dir & DIR_UP ) if ( y - _vel < 1 ) _dir &= ~DIR_UP;
	return 0 == ( _dir << 4 );
}

bool BaseObject::Collides( Direction _dir, int _vel ) const
{
	if ( ( _dir << 4 ) && _vel )
	{
		std::vector< BaseObject* > objects = GameState::GetObjects();

		int newX = x + _vel * ( ( 0 == ( _dir & DIR_RIGHT ) ? 0 : 1 ) - ( 0 == ( _dir & DIR_LEFT ) ? 0 : 1 ) );
		int newY = y + _vel * ( ( ( ( _dir & DIR_DOWN ) == 0 ) ? ( 0 ) : ( 1 ) ) - ( ( ( _dir & DIR_UP ) == 0 ) ? ( 0 ) : ( 1 ) ) );
		//    x += v * (   right  -  left   )    //
		//    y += v * (   down   -   up    )    //

		for ( int i = 0; i < ( int )objects.size(); ++i )
			if ( this == objects[ i ] || Obj_Missile == objects[ i ]->GetObjectID() ) // ignore self collision and missile collision
				continue;
			else if ( ( Game::GetCheats() & CHEAT_DISABLE_ENEMY_COLLISION ) &&
				( ( Obj_Player == this->GetObjectID() && Obj_Enemy == objects[ i ]->GetObjectID() ) ||
					  ( Obj_Enemy == this->GetObjectID() && Obj_Player == objects[ i ]->GetObjectID() ) ) )
				continue;
			else if ( !(
				newX + width <= objects[ i ]->x ||
				objects[ i ]->x + objects[ i ]->width <= newX ||
				newY + height <= objects[ i ]->y ||
				objects[ i ]->y + objects[ i ]->height <= newY ) )
				return CellsCollision( newX, newY, objects[ i ] );
	}
	return false;
}

#if VECTOR_CELLS
bool BaseObject::CellsCollision( int _newX, int _newY, BaseObject* _other ) const
{
	for ( int a = 0; a < ( int )shape.size(); ++a )
		for ( int b = 0; b < ( int )_other->GetShape().size(); ++b )
			if ( ( ( _newX + shape[ a ].oX ) == ( _other->GetX() + _other->GetShape()[ b ].oX ) ) &&
				( ( _newY + shape[ a ].oY ) == ( _other->GetY() + _other->GetShape()[ b ].oY ) ) )
				return true;
	return false;
}
#elif DLIST_CELLS
bool BaseObject::CellsCollision( int _newX, int _newY, BaseObject* _other ) const
{
	for ( int a = 0; a < shape.getSize(); ++a )
		for ( int b = 0; b < _other->GetShape().getSize(); ++b )
			if ( ( ( _newX + shape[ a ].oX ) == ( _other->GetX() + _other->GetShape()[ b ].oX ) ) &&
				( ( _newY + shape[ a ].oY ) == ( _other->GetY() + _other->GetShape()[ b ].oY ) ) )
				return true;
	return false;
}
#endif

void BaseObject::Input()
{
}
void BaseObject::Update( Frame _frame )
{
	( void )_frame;
}
void BaseObject::Render() const
{
	Show();
}

#if VECTOR_CELLS
void BaseObject::SetShape( std::vector< Cell<> > _shape )
{
	std::vector< Cell<> >::iterator iter = shape.begin();
	while ( iter != shape.end() )
	{
		iter = shape.erase( iter );
	}

	shape.resize( _shape.size() );

	for ( int i = 0; i < ( int )_shape.size(); ++i )
	{
		shape[ i ].bg = _shape[ i ].bg;
		shape[ i ].fg = _shape[ i ].fg;
		shape[ i ].oX = _shape[ i ].oX;
		shape[ i ].oY = _shape[ i ].oY;
		shape[ i ].sym = _shape[ i ].sym;
	}

	CalculateDimensions();
}
#elif DLIST_CELLS
void BaseObject::SetShape( DList< Cell<> > _shape )
{
	shape.clear();

	Cell<> temp;

	for ( int i = 0; i < _shape.getSize(); ++i )
	{
		temp = _shape[ i ];
		shape.push_back( temp );
	}

	CalculateDimensions();
}
#endif

#if VECTOR_CELLS
std::vector< Cell<> > BaseObject::ToCells( const char * const _text, System::ConsoleColor _fg, System::ConsoleColor _bg )
{
	std::vector< Cell<> > cells;
	cells.clear();
	int x = 0, y = 0;
	for ( unsigned int i = 0; i < strlen( _text ); ++i )
	{
		if ( '\t' == _text[ i ] ) ++x;
		else if ( '\n' == _text[ i ] )
		{
			x = 0; ++y;
		}
		else cells.push_back( { x++, y, _fg, _bg, _text[ i ] } );
	}
	cells.resize( cells.size() );
	return cells;
}
#elif DLIST_CELLS
DList< Cell<> > BaseObject::ToCells( const char * const _text, System::ConsoleColor _fg, System::ConsoleColor _bg )
{
	DList< Cell<> > cells;
	cells.clear();
	int x = 0, y = 0;
	for ( unsigned int i = 0; i < strlen( _text ); ++i )
	{
		if ( '\t' == _text[ i ] ) ++x;
		else if ( '\n' == _text[ i ] )
		{
			x = 0; ++y;
		}
		else cells.push_back( { x++, y, _fg, _bg, _text[ i ] } );
	}
	return cells;
}
#endif

// ☻☺ トニー ☺☻ -- Y:2015年 //