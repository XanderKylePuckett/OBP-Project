#include "Missile.h"
#include "GameState.h"

Missile::Missile() : BaseObject( ToCells( "\x4", System::ConsoleColor::PLAYER_MISSILE, System::ConsoleColor::GAME_BACKGROUND ) )
{
	SetObjectID( Obj_Missile );
	SetX( 0 );
	SetY( 0 );
	IsAlive( false );
	vel.resize( 2 );
	SetVel( 0, 0 );
	IsEnemyMissile( false );
}

Missile::Missile( System::ConsoleColor _color ) : BaseObject( ToCells( "\x4", _color, System::ConsoleColor::GAME_BACKGROUND ) )
{
	SetObjectID( Obj_Missile );
	SetX( 0 );
	SetY( 0 );
	IsAlive( false );
	vel.resize( 2 );
	SetVel( 0, 0 );
	IsEnemyMissile( false );
}

Missile::~Missile()
{
}

void Missile::Input( void )
{
}
void Missile::Update( Frame _frame )
{
	( void )_frame;

	Direction dir = GetDir();

	std::vector<BaseObject*> objects = GameState::GetObjects();


	int newX = GetX() + ( ( ( ( dir & DIR_RIGHT ) == 0 ) ? ( 0 ) : ( 1 ) ) - ( ( ( dir & DIR_LEFT ) == 0 ) ? ( 0 ) : ( 1 ) ) );
	int newY = GetY() + ( ( ( ( dir & DIR_DOWN ) == 0 ) ? ( 0 ) : ( 1 ) ) - ( ( ( dir & DIR_UP ) == 0 ) ? ( 0 ) : ( 1 ) ) );

	if ( System::Console::WindowWidth() - 1 < newX + GetWidth() ||
		 System::Console::WindowHeight() - 3 < newY + GetHeight() ||
		 newX < 1 ||
		 newY < 1 )
	{
		IsAlive( false );
		return;
	}

	for ( int i = 0; i < ( int )objects.size(); ++i )
	{
		if ( objects[ i ]->GetObjectID() == Obj_Missile )
			continue;
		if ( !(
			newX + GetWidth() <= objects[ i ]->GetX() ||
			objects[ i ]->GetX() + objects[ i ]->GetWidth() <= newX ||
			newY + GetHeight() <= objects[ i ]->GetY() ||
			objects[ i ]->GetY() + objects[ i ]->GetHeight() <= newY ) )
		{
			Player* p = dynamic_cast< Player* >( objects[ 0 ] );
			if ( Obj_Enemy == objects[ i ]->GetObjectID() && !enemyMissile )
				p->SetScore( p->GetScore() + 69 );
			else if ( Obj_Player == objects[ i ]->GetObjectID() && enemyMissile )
				p->SetScore( p->GetScore() - 96 );
			IsAlive( false );
			return;
		}
	}

	Move( dir );
}
void Missile::Render( void ) const
{
	BaseObject::Render();
}

Direction Missile::GetDir( void ) const
{
	Direction dir = 0;
	if ( GetVelX() > 0 ) dir |= DIR_RIGHT;
	else if ( GetVelX() < 0 ) dir |= DIR_LEFT;
	if ( GetVelY() > 0 ) dir |= DIR_DOWN;
	else if ( GetVelY() < 0 ) dir |= DIR_UP;
	return dir;
}

// ☻☺ トニー ☺☻ -- Y:2015年 //