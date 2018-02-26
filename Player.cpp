#include "Player.h"
#include "Missile.h"
#include "GameState.h"

Player::Player() : BaseObject()
{
	SetObjectID( Obj_Player );
	SetName( "Player" );
	score = 0;
	diff = 0;
	dir = 0;
	IsAlive( true );
}

#if VECTOR_CELLS
Player::Player( std::vector< Cell<> > _shape, char const * const _name, int _score, int _diff ) : BaseObject( _shape )
{
	SetObjectID( Obj_Player );
	SetName( _name );
	SetScore( _score );
	SetDifficulty( _diff );
	IsAlive( true );
}
#elif DLIST_CELLS
Player::Player( DList< Cell<> > _shape, char const * const _name, int _score, int _diff ) : BaseObject( _shape )
{
	SetObjectID( Obj_Player );
	SetName( _name );
	SetScore( _score );
	SetDifficulty( _diff );
	IsAlive( true );
}
#endif

Player::Player( const Player& _obj ) : BaseObject( _obj )
{
	SetObjectID( Obj_Player );
	SetName( _obj.name.c_str() );
	SetScore( _obj.score );
	SetDifficulty( _obj.diff );
	IsAlive( true );
}
Player& Player::operator=( const Player& _obj )
{
	if ( this != &_obj )
	{
		( void )( BaseObject::operator=( _obj ) );
		SetName( _obj.name.c_str() );
		SetScore( _obj.score );
		SetDifficulty( _obj.diff );
	}
	return *this;
}
Player::~Player()
{
}

void Player::Show() const
{
	int i = 0;
	BaseObject::Show();
	System::Console::ForegroundColor( ( WORD )( System::ConsoleColor::HUD_COLOR ) );
	System::Console::BackgroundColor( ( WORD )( System::ConsoleColor::GAME_BACKGROUND ) );
	System::Console::SetCursorPosition( 0, System::Console::WindowHeight() - 3 );
	for ( ; i < System::Console::WindowWidth(); ++i ) std::cout << '=';
	System::Console::SetCursorPosition( 0, System::Console::WindowHeight() - 2 );
	for ( i = 0; i < System::Console::WindowWidth(); ++i ) std::cout << '=';
	System::Console::SetCursorPosition( 5, System::Console::WindowHeight() - 2 );
	std::cout << "  Name: " << name << "  ";
	System::Console::SetCursorPosition( ( System::Console::WindowWidth() >> 1 ) - 10, System::Console::WindowHeight() - 2 );
	std::cout << "  Score: " << score << "  ";
	System::Console::SetCursorPosition( ( System::Console::WindowWidth() << 2 ) / 5, System::Console::WindowHeight() - 2 );
	std::cout << "  Difficulty: " << diff << "  ";
	System::Console::ResetColor();
}

void Player::Input()
{
	dir = 0;

	if ( GetAsyncKeyState( 'W' ) ) dir |= DIR_UP;
	if ( GetAsyncKeyState( 'A' ) ) dir |= DIR_LEFT;
	if ( GetAsyncKeyState( 'S' ) ) dir |= DIR_DOWN;
	if ( GetAsyncKeyState( 'D' ) ) dir |= DIR_RIGHT;
}
void Player::Update( Frame _frame )
{
	if ( GetAsyncKeyState( VK_SPACE ) )
		if ( 0 == _frame % 3 ) Shoot( DIR_RIGHT );

	Move( dir );

	if ( Game::GetCheats() & CHEAT_INCREMENT_SCORE ) score += 159;
}
void Player::Render() const
{
	Show();
}

void Player::Shoot( Direction _dir ) const
{
	( void )_dir; // TODO: Direction of Missile

	Missile* m = new Missile();//dynamic_cast< Missile* >( GameState::GetObjects()[ 2 ] );
	m->SetX( GetX() + GetWidth() + 1 );
	m->SetY( GetY() + ( GetHeight() >> 1 ) );
	m->SetVel( 1, 0 ); // DIR_RIGHT
	m->IsAlive( true );

	GameState::GetObjects().push_back( m );
}

// ☻☺ トニー ☺☻ -- Y:2015年 //