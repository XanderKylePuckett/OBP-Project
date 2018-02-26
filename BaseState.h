#pragma once
#include "stdafx.h"

class BaseState
{
private:

public:
	BaseState();
	virtual ~BaseState();

	virtual void Init( void ) = 0;
	virtual void Enter( void ) = 0;
	virtual void Input( void ) = 0;
	virtual void Update( Frame _frame ) = 0;
	virtual void Render( void ) const = 0;
	virtual void Exit( void ) = 0;
};

// ☻☺ トニー ☺☻ -- Y:2015年 //