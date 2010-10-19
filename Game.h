#pragma once
#include "module.h"
#include "CPU.h"
#include "constants.h"
#include <time.h>
#include <stdio.h>
#include <stack>
using namespace std;
struct Level {
	int level[18][18];
};
class CGame
{
public:
	
	////////////////////////////////////////////////////////////////////////////
	// The matches-checking routine.

	int gameMode;
	char text[100];
	
	int tutorialPage;
	int tutorialAnimation;
	bool tutorialAnimationDirection;
	int tutorialAnimation2;
	int tutorialAnimationDirection2;
	int handAnimationX;
	bool pausedMenu; 
	int levelSelected;
	int setSelected;
	int leftIsPressed; // for fast control
	int rightIsPressed;
	int upIsPressed;
	int downIsPressed;
	int leftHasBeenPressed; // so we dont use fast and slow control simultaneously
	int rightHasBeenPressed;
	int upHasBeenPressed;
	int downHasBeenPressed;
	bool arrowbuttonPressed;
	int undoHasBeenPressed;
	int pulsateAnimation;
	bool pulsateAnimationDirection;

	int levelMovingType[18][18]; // what type moving animation 1 left 2 right 3 up 4 down
	int levelMovingAnimation[18][18]; // moving animation
	int leveltagged[18][18]; // are the blocks stuck from moving (1 yes 0 no)
							// also used to check if puzzle is completed
	int level[18][18];
	int purpletagged[18][18]; // are the purple blocks moving (1 yes 0 no)
	int levelgates[18][18]; // gates that only certain colors can through, 1 2 3 (blue red green)
	int completePuzzleSequence;
	int backupUndoMoves[100][18][18]; // keep up to 100 moves
	int undoMovesCursor; // start at 0...up to 100 kept
	stack<Level> levelUndoMoves; // stack of all words
	float percentLoading;
	bool cameFromTransition;
	bool transitioning;
	int nextState; 
	float transitioningAnimation;
	int rulesAnimation;
	int rulesAnimating; // 0 no animating, 1 page1->2, 2 page2->3, 3 page3->2, 4 page2->1

	int levelSelectionAnimating; // 1 left or 2 right
	int levelSelectionAnimation; 
	int levelSelectionOffset;
	bool changeLevelUponTransition;

	int pauseMenuAnimating; // 1 opening 2 closing
	int pauseMenuAnimation;

	int cursorAnimating; // moving
	int cursorAnimationX;
	int cursorAnimationY;
	int cursorAnimationX2;
	int cursorAnimationY2;
	int cursorAnimatingX, cursorAnimatingY;
	
	int congratulationsAnimatingY[16]; // 2 going up 1 going down 3 starting animation
	float congratulationsAnimationY[16];
	char congratulationsString[20];
	int congratulationsAnimationX[16];
	int congratulationsAnimationY2[16];
	bool congratulationsXAnimationDone[16];
	bool congratulationsYAnimationDone[16];
	bool congratulationsLastStage;

	int levelCompletedX;
	int levelCompletedX2;
	int particleFallingCounter; // limit to one per half second

	// bird sprite
	int birdSpriteFrame;
	int birdAnimation; // 1 alive 0 dead
	int birdX;
	int birdY;
	int cakeAnimation;
	int cakeAnimationCounter;
public:
	CGame(void);
public:
	~CGame(void);
	void Input();
	void Options();
	void LevelSelect();
	void Titlescreen();
	void Tutorial();
	void ShowScore();
	void Splash();
	void RenderEndless();
	void Update();
	void GameInit();
	void GamePlay();
	void MoveDown();
	void ResetTags();
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void TagAroundPurple(int color, int i, int j);
	void TagAround(int color, int i, int j);
	void CheckCompleted();
	void changeColorUp(int color, int x, int y);
	void changeColorLeft(int color, int x, int y);
	void changeColorRight(int color, int x, int y);
	void changeColorDown(int color, int x, int y);
	void RestoreLastMove();
	void BackupBoard();
	SDL_Rect getColorToRectForSmall(int color, bool lcolor, bool rcolor, bool bcolor, bool tcolor);
	SDL_Rect getColorToRect(int color, bool lcolor, bool rcolor, bool bcolor, bool tcolor);
	void Transition();
	void FromTransition();
	void RenderCongratulations();
	void RenderGame();
	void RenderGameBackground();
	void Ending();
};	
