#pragma once
#pragma comment(lib, "winmm.lib")

#include <Windows.h>
#include <iostream>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Console.h"

#define VECTOR_CELLS 0
#if VECTOR_CELLS
#define DLIST_CELLS 0
#else
#define DLIST_CELLS 1
#endif

#define DIR_UP     (0b0001) // 1 -> -y
#define DIR_DOWN   (0b0010) // 2 -> +y
#define DIR_LEFT   (0b0100) // 4 -> -x
#define DIR_RIGHT  (0b1000) // 8 -> +x

#define DIR_UP_LEFT     (0b0101) // 5  -> -x -y
#define DIR_UP_RIGHT    (0b1001) // 9  -> +x -y
#define DIR_DOWN_LEFT   (0b0110) // 6  -> -x +y
#define DIR_DOWN_RIGHT  (0b1010) // 10 -> +x +y

#define CHEAT_ISPLAYING                     (0b00000001) // bit-1
#define CHEAT_DISABLE_ENEMY_MOVEMENT        (0b00000010) // bit-2
#define CHEAT_DISABLE_ENEMY_SHOOT_MISSILES  (0b00000100) // bit-4
#define CHEAT_INCREMENT_SCORE               (0b00001000) // bit-8
#define CHEAT_DISABLE_ENEMY_COLLISION       (0b00010000) // bit-16
#define CHEAT_UNUSED_32                     (0b00100000) // bit-32
#define CHEAT_UNUSED_64                     (0b01000000) // bit-64
#define CHEAT_UNUSED_128                    (0b10000000) // bit-128

typedef byte Direction;
typedef unsigned long long Frame;

#define TRANSITION 11111
#define MAINMENU_NUMITEMS 4

#define MENU_ITEMCOLOR DarkRed
#define MENU_SELECTEDCOLOR Green
#define MENU_BACKGROUND DarkGray
#define GAME_BACKGROUND DarkBlue
#define HUD_COLOR White
#define MENU_DESCCOLOR DarkMagenta
#define PLAYER_MISSILE Green
#define ENEMY_MISSILE Red
#define SCORES_BACKGROUND DarkGreen
#define SCORES_FOREGROUND Black
#define ERROR_COLOR Red
#define CHEATS_BG White
#define CHEATS_FG DarkRed
#define MAXSCORES 25u

extern unsigned int randSeed;

/*
OBP Lab 10 - Extra Credit

< Use SoundPlayer to play a .WAV (FMOD is an acceptable substitute) >
  ( ??, SoundPlayer? )
	>> GameState.cpp::63 (Start Song)
	>> GameState.cpp::132 (End Song)

< Draw a box around the field leaving the top row for the HUD and bottom row for the bit flags then update bounds checking >
	>> GameState.cpp::106~126 (Draw box)
	>> BaseObject.cpp::135~138 (Bounds Checking)
	>> Missile.cpp::45~48 (Dead Missile Check)

< Display high-score statistics (min, max and average) for both diff and score >
	>> HighScoresState.h::12~14 (Declare member variables)
	>> HighScoresState.cpp::445~486 (Calculate values)
	>> HighScoresState.cpp::313~344 (Show stats on screen)

< Change the name of the 6th player in the binary high-score file to “Number Six” >
	>> HighScoresState.cpp::156~172 (Write Number Six to file)

< Implement something interesting or cool that is not on this list for a max of 5 more points >
  ( ??, Define "something interesting or cool" )
  ( ??, like the transitions between my states? idk )
	>> HighScoresState.cpp::42~49
	>> GameState.cpp::26~33
	>> MenuState.cpp::19~25

< Replace vector of cells with a DList in BaseObject class >
	>> BaseObject.h::29 (Declare DList of cells)
	>> BaseObject.h::40 (Object constructor declarition)
	>> BaseObject.h::77~80 (Shape accessor)
	>> BaseObject.h::103 (Shape mutator declaration)
	>> BaseObject.cpp::23~30 (Object constructor definition)
	>> BaseObject.cpp::227~240 (Shape mutator definition)

*/

// ☻☺ トニー ☺☻ -- Y:2015年 //