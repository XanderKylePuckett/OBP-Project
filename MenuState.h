#pragma once
#include "BaseState.h"
class MenuState : public BaseState
{
private:

	char* menuItem[ MAINMENU_NUMITEMS ];
	char* desc[ MAINMENU_NUMITEMS ];
	int currItem;
	bool keyPressed;

public:
	MenuState();
	~MenuState();

	void Enter( void );
	void Input( void );
	void Update( Frame _frame );
	void Render( void ) const;
	void Exit( void );
	void Init( void );
};

// ☻☺ トニー ☺☻ -- Y:2015年 //