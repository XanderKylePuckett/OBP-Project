#pragma once
#include "BaseState.h"
#include "stdafx.h"
#include "Player.h"

class HighScoresState : public BaseState
{
private:
	std::vector<PlayerInfo> scores;

	short sort;
	int minScore, maxScore, minDiff, maxDiff;
	double avgScore, avgDiff;
	char minScoreName[ 32 ], maxScoreName[ 32 ], minDiffName[ 32 ], maxDiffName[ 32 ];
	bool keyPressed;
	int currPage;
	unsigned int numPages;

public:
	HighScoresState();
	~HighScoresState();

	void Enter( void );
	void Input( void );
	void Update( Frame _frame );
	void Render( void ) const;
	void Exit( void );
	void Init( void );

private:
	void SaveScores( void ) const;
	void SetStats( void );
};

// ☻☺ トニー ☺☻ -- Y:2015年 //