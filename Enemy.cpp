#include "Enemy.h"
#include "Missile.h"
#include "GameState.h"

Enemy::Enemy() : BaseObject()
{
	SetObjectID( Obj_Enemy );
}

#if VECTOR_CELLS
Enemy::Enemy( std::vector< Cell<> > _shape ) : BaseObject( _shape )
{
	SetObjectID( Obj_Enemy );
	IsAlive( true );
}
#elif DLIST_CELLS
Enemy::Enemy( DList< Cell<> > _shape ) : BaseObject( _shape )
{
	SetObjectID( Obj_Enemy );
	IsAlive( true );
}
#endif

Enemy::Enemy( const Enemy& _obj ) : BaseObject( _obj )
{
	SetObjectID( Obj_Enemy );
	IsAlive( true );
}

Enemy& Enemy::operator=( const Enemy& _obj )
{
	if ( this != &_obj )
		( void )( BaseObject::operator=( _obj ) );
	return *this;
}

Enemy::~Enemy()
{
}

void Enemy::Update( Frame _frame )
{
	if ( !( Game::GetCheats() & CHEAT_DISABLE_ENEMY_MOVEMENT ) )
		if ( 0 == _frame % 5 )
			Move( ( 0b100 << ( rand() % 3 ) ) | ( 0b100 >> ( ( rand() % 3 ) + 1 ) ) );

	if ( !( Game::GetCheats() & CHEAT_DISABLE_ENEMY_SHOOT_MISSILES ) )
		if ( 0 == _frame % 50 )
			Shoot( DIR_LEFT );
}

void Enemy::Shoot( Direction _dir ) const
{
	( void )_dir;

	Missile* m = new Missile( System::ConsoleColor::ENEMY_MISSILE );
	m->IsEnemyMissile( true );
	m->SetX( GetX() - 1 );
	m->SetY( GetY() + ( GetHeight() >> 1 ) );
	m->SetVel( -1, 0 ); // DIR_LEFT
	m->IsAlive( true );

	GameState::GetObjects().push_back( m );
}

// ☻☺ トニー ☺☻ -- Y:2015年 //