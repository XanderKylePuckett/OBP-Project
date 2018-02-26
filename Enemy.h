#pragma once
#include "BaseObject.h"

class Enemy : public BaseObject
{
private:

public:
	Enemy();
#if VECTOR_CELLS
	Enemy( std::vector< Cell<> > _shape );
#elif DLIST_CELLS
	Enemy( DList< Cell<> > _shape );
#endif

	Enemy( const Enemy& _obj ); // Copy Constructor
	Enemy& operator=( const Enemy& _obj ); // Assignment Operator
	~Enemy(); // Destructor


	// Methods

	void Update( Frame _frame );

private:
	void Shoot( Direction _dir ) const;

};

// ☻☺ トニー ☺☻ -- Y:2015年 //