#pragma once
#include "module.h"

class CCPU  :
	public CModule
{
public:
	////////////////////////////////////////////////////////////////////////////
	// The matches-checking routine.

	int timeCount;
	int saveScore;
	int bestScore;
	int bestMoveX, bestMoveY;
	// This array is used to remember which panels were matched.
	int MatchedPanels[96];
	int backupPanels[96];
	SDL_Rect src;
	float sin_look[361];
	float cos_look[361];
	float wave;
	int lastX, lastY;
	int squarechosenX,squarechosenY;
	int whatRow;
	int AIDifficulty;
	int AIDumbDownTimer;

	double lock60;
	int P1StackTags[96];

	// A panel's timer indicates for how many more frames it will:
	//  . be swapping
	//  . sit in the MATCHED state before being set POPPING
	//  . sit in the POPPING state before actually being POPPED
	//  . sit and be POPPED before disappearing for good
	//  . hover before FALLING
	// depending on which one of these flags is set on the panel.

	// Stack displacement.
	int P1StackDisplacement;
	// This variable indicates how far below the top of the play
	// area the top row of panels actually is.
	// This variable being decremented causes the stack to rise.
	// During the automatic rising routine, if this variable is 0,
	// it's reset to 15, all the panels are moved up one row,
	// and a new row is generated at the bottom.
	// Only when the displacement is 0 are all 12 rows "in play."

	int DoMatchesCheck;
	// if this gets set non-zero a matches-check will occur for this
	// frame.

	int P1DangerCol[6];  // set 1 if this column is near the top
	int P1DangerTimer;   // decided bounce frame when in danger


	int P1DifficultyLV;
	int NewDir;
	int GameTimeRender;
	int P1ScoreRender;
	int MrStopState;
	int MrStopTimer;
	int MrStopAni[25];
	int stackHeight;
	// The stack of panels.
	int P1StackPanels[96];
	// Twelve rows of 8 ints each, the first 6 representing
	// the panels on that row.
	// A panel's color can be retrieved using P1Stack[row<<3+col]

	// Each space on the stack of panels has a timer.
	int P1StackTimers[96];

	// Each space on the stack of panels has flags
	// that define the state it's in.
	int P1StackFlags[96];

	int P1SpeedLV;   // The player's speed level decides the amount of time
	// the stack takes to rise automatically
	int P1RiseTimer;   // When this value reaches 0, the stack will rise a pixel
	int P1RiseLock;   // If the stack is rise locked, it won't rise until it is
	// unlocked.
	int P1HasRisen;   // set once the stack rises once during the game
	int cleanupTick;
	int P1StopTime;
	int P1StopTimeTimer;
	int StopTime_Combo[2][5];
	int StopTime_Chain[2][5];

	int GameTime;
	int GameTimeMode;
	int GameTimeTimer;


	int P1Score;          // der skore
	int P1ChainCounter;   // how high is the current chain?



	// The following variables keep track of stuff:
	int bottomrow;   // row number of the bottom row that's "in play"
	int PanelsInTopRow;  // boolean, panels in the top row (danger)
	int PanelsInSecondRow; // changes music state


	int Count_ActivePanels;
	int Count_ChainPanels;
	int swapType;
	// These change depending on the difficulty and speed levels:
	int FRAMECOUNT_HOVER;
	int FRAMECOUNT_MATCH;
	int FRAMECOUNT_FLASH;
	int FRAMECOUNT_POP;
	int FRAMECOUNT_RISE;

	// Player input stuff:
	int P1ManualRaise;   // set until raising is completed
	int P1ManualRaiseYet;  // if not set, no actual raising's been done yet
	// since manual raise button was pressed
	int P1PreventManualRaise;
	int P1Swap1;   // attempt to initiate a swap on this frame
	int P1Swap2;

	int P1CurWaitTime;   // number of ticks to wait before the cursor begins
	// to move quickly... it's based on P1CurSensitivity
	int P1CurTimer;   // number of ticks for which a new direction's been pressed
	int P1CurDir;     // the direction pressed
	int P1CurRow;  // the row the cursor's on
	int P1CurCol;  // the column the left half of the cursor's on

	int ScoreMode;

	int P1CurMoveAloud;  // this is set if the cursor movement sound should be played


	// score lookup tables
	int Score_Combo_PdP64[40];
	int Score_Combo_TA[31];
	int Score_Chain_TA[14];
	int Input_Swap1Pressed;
	int Input_Swap2Pressed;
	int Input_DirPressed;  // last dir pressed

	int P1GameOver;



	int Font_NumRed;
	int Font_NumBlue;

	int P1StackPosX;   // Position of the play area on the screen
	int P1StackPosY;

	int P1ScoreDisplay;

	int P1ScoreDigits[5];

	int GameTimeDisplay;
	int GameTimeDisplayPosX;
	int GameTimeDisplayPosY;
	int GameTimeDigits[7];

	int Graphics_TIME;

	int Graphics_Ready321;

	int P1SpeedLVDisplay;
	int P1SpeedLVRender;
	int P1SpeedLVDigits[3];


	int Graphics_level;
	int Graphics_MrStop[2];
	int Graphics_Difficulty[5];

	int Graphics_Panels[9];
	int Graphics_Cursor[2];
	
	int bouncetable[13];
	int dangerbouncetable[30];

	int TimeSlideAni[65];

	int CardAni[50];
	int Graphics_ComboCards;
	int Graphics_ChainCards;
	int ComboCardsQueue[50];
	int ComboCardsQueueLength;
	int ChainCards16Queue[50];
	int ChainCards16QueueLength;
	int ChainCards21Queue[50];
	int ChainCards21QueueLength;


	Uint32 time1;
	int NumConfettis;

	int Confettis[8][5];
	int ConfettiAni[48];
	int ConfettiBuf[6][2];

	int Graphics_Controller;
	int Graphics_Controller_Up;
	int Graphics_Controller_Down;
	int Graphics_Controller_Left;
	int Graphics_Controller_Right;
	int Graphics_Controller_ABXY;
	int Graphics_Controller_L;
	int Graphics_Controller_R;
	int staticA, staticB;
	int whatMove;
	int moveCounter;
public:
	CCPU(void);
public:
	~CCPU(void);
	void CleanUp();
	void Update();
	void Render();
	void AnimateTo();
	void AnimateFrom();
	void Controls_NewGame();
	void NewRow();
	void CheckMatches();
	void SetupGame_Any();
	void SetHoverers2(int firsthoverer, int hovertime, int addflags);
	void SetHoverers(int firsthoverer, int hovertime, int addflags);
	// Stuff defined in this file:
	//  . the data structures that store the configuration of
	//    the stack of panels
	//  . the main game routine
	//    (rising, timers, falling, cursor movement, swapping, landing)
	//  . the matches-checking routine
	void PdP();
	void CustomPDP();
	void QuietCursorMovement();
	void GameInit();
	void GameEnd();
	void GameLoop();
	void Input();
	void Render2();
	void Init2();
	void DrawFPS();
	void Render_1P();
	void RenderText();
	void Swap();
	void EnqueueComboCard(int xpos, int ypos, int iofs);
	void DrawComboCards();
	void EnqueueChainCard(int xpos, int ypos, int hitno);
	void DrawChainCards16();
	void DrawChainCards21();
	void EnqueueConfetti(int x, int y);
	void Render_Confetti();
	void RandomShake();
};
