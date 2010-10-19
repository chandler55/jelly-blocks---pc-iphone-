#include "StdAfx.h"
#include "Game.h"
#include <math.h>

#define PI (3.141592653589793)
#define DEG_TO_RAD(X) (X*PI/180.0) 

#define TMOL 42
#define COMBO 0
#define CHAIN 1
#define SCOREMODE_TA 1
#define MAX( x, y ) ((x) > (y) ? (x) : (y))

extern CShared *shared;
CGame::CGame(void)
{
	cakeAnimation= cakeAnimationCounter = 0;
	birdX = birdY = 0;
	birdAnimation = 0;
	birdSpriteFrame= 0;
	setSelected= 1;
	levelSelected = 1;
	particleFallingCounter= 0;
	sprintf(congratulationsString, "CONGRATULATIONS!");
	congratulationsLastStage= false;
	for (int i = 0; i < 16 ;i++) {
		congratulationsAnimatingY[i] = 3;
		congratulationsAnimationY[i] = 130+i*2;

		congratulationsAnimationY2[i] = rand()%480;
		congratulationsAnimationX[i] = rand()%320;
		congratulationsXAnimationDone[i]= congratulationsYAnimationDone[i] = false;
	}
	cursorAnimating = cursorAnimationX = cursorAnimationX2 = cursorAnimationY =cursorAnimationY2 = 0;
	cursorAnimatingX= cursorAnimatingY = 0;
	
	pauseMenuAnimation = pauseMenuAnimating= 0;
	changeLevelUponTransition= false;
	pauseMenuAnimation = -304;
	cameFromTransition= false;
	levelSelectionAnimation= 0;
	levelSelectionAnimating= 0;
	rulesAnimation= 0;
	rulesAnimating = 0;
	percentLoading= 0; // theres about 64 objects to load (images/buttons)
	undoMovesCursor = 0;
	tutorialAnimation = 0;
	tutorialAnimationDirection = true;
	tutorialAnimation2 = 0;
	tutorialAnimationDirection2 = 0;

	pulsateAnimationDirection= true;
	pulsateAnimation= 252;
	shared = CShared::getInstance();
	gameMode= SPLASH;
	shared = CShared::getInstance();
	shared->Init();
	//InitLineClearGoals();

	// initialize non game stuff
	tutorialPage = 1;
	// initialize game stuff
	//GameInit();
	pausedMenu = false;
	setSelected= 1;
	transitioning = false;
	transitioningAnimation= 0;
	nextState = 0;
	
}

void CGame::GameInit()
{	
	particleFallingCounter= 1000;
	completePuzzleSequence= 0;
	birdX = birdY = 0;
	birdAnimation = 0;
	birdSpriteFrame= 0;
	levelCompletedX= -100;
	levelCompletedX2 = 420;
	congratulationsLastStage= false;
	for (int i = 0; i < 16 ;i++) {
		congratulationsAnimatingY[i] = 3;
		congratulationsAnimationY[i] = 130+i*2;

		congratulationsAnimationY2[i] = rand()%480;
		congratulationsAnimationX[i] = rand()%320;
		congratulationsXAnimationDone[i]= congratulationsYAnimationDone[i] = false;
	}
	cursorAnimating = cursorAnimationX = cursorAnimationX2 = cursorAnimationY =cursorAnimationY2 = 0;
	cursorAnimatingX= cursorAnimatingY = 0;

	// reset undo moves
	while (!levelUndoMoves.empty()) {
		levelUndoMoves.pop();
	}

	// initialize level information
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
				//transitionlevel.set(i,j,0);
			//	level.set(j,i,0);
				
				if (i == 0 || i == 17 || j == 17 || j ==0) {
					leveltagged[i][j] = 1;
					level[i][j] = 4;
					purpletagged[i][j] = 0;
					levelgates[i][j]= 0;
					levelMovingAnimation[i][j] = 0;
				}
				else {
					level[i][j] = 0;
					purpletagged[i][j] = 0;
					leveltagged[i][j] = 0;
					levelgates[i][j] = 0;
					levelMovingAnimation[i][j]= 0;
				}
			}
	}

	shared->particleengine->InitGame();

	pausedMenu = false;
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			level[i][j] = shared->levels[(setSelected-1)*12 + levelSelected][i][j];
		}
	}

	// replace gates with open spaces, and put gate information in levelgates
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			if (level[i][j] == 11) {
				level[i][j] = 0;
				levelgates[i][j] = 11;
			}
			if (level[i][j] == 12) {
				level[i][j] = 0;
				levelgates[i][j] = 12;
			}
			if (level[i][j] == 13) {
				level[i][j] = 0;
				levelgates[i][j] = 13;
			}
		}
	}
	rightIsPressed = downIsPressed = upIsPressed = leftIsPressed = 0;
	undoHasBeenPressed = rightHasBeenPressed = downHasBeenPressed = upHasBeenPressed = leftHasBeenPressed = 0;

}

CGame::~CGame(void)
{
}

void CGame::Options() {
	
}
			
void CGame::Tutorial() {
	switch (tutorialPage) {
		case 1:
			if (rulesAnimation < 0)
				rulesAnimation+=8;
			break;
		case 2:
			if (rulesAnimation > -320)
				rulesAnimation-=8;
			if (rulesAnimation < -320)
				rulesAnimation+=8;
			break;
		case 3:
			if (rulesAnimation > -640)
				rulesAnimation-=8;
			break;
	}
	shared->images->background->Render(0,0);
	sprintf(text,"RULES");
	shared->images->RenderText(130,20,shared->MICRO10SILVER,text);

		shared->images->tutorialpage1->Render(rulesAnimation,0);
		tutorialAnimation++;
		if (tutorialAnimation > 60) {
			tutorialAnimation = 0;
			tutorialAnimationDirection = !tutorialAnimationDirection;
		}
		if (tutorialAnimationDirection) {
			shared->images->tutorial[0]->Render(60+rulesAnimation,257);
		} else {
			shared->images->tutorial[1]->Render(60+rulesAnimation,257);
		}		
	

		shared->images->tutorialpage2->Render(320+rulesAnimation,0);

		tutorialAnimation2++;
		if (tutorialAnimation2 > 60) {
			tutorialAnimation2 = 0;
			switch (tutorialAnimationDirection2) {
				case 0:
					tutorialAnimationDirection2 = 1;
					break;
				case 1:
					tutorialAnimationDirection2 = 2;
					break;
				case 2:
					tutorialAnimationDirection2 = 0;
					break;
			}
		}
		if (tutorialAnimationDirection2 == 0) {
			shared->images->tutorial[2]->Render(104+320+rulesAnimation,198);
		} else if (tutorialAnimationDirection2 == 1){
			shared->images->tutorial[3]->Render(104+320+rulesAnimation,198);
		} else if (tutorialAnimationDirection2 == 2){
			shared->images->tutorial[4]->Render(104+320+rulesAnimation,198);
		}			

		shared->images->tutorialpage3->Render(320+320+rulesAnimation,0);
	
	
	shared->buttons->backbutton->Update();
	if (shared->buttons->backbutton->PressAndReleased()) {
		gameMode = TITLESCREEN;
		shared->sounds->menu->playSound();
	}
	shared->buttons->backbutton->Render();
	
	if (tutorialPage == 1|| tutorialPage == 2){
		shared->buttons->next->Update();
		if (shared->buttons->next->PressAndReleased()) {
			tutorialPage++;
			shared->sounds->switchSound->playSound();
			if (tutorialPage == 1)
				rulesAnimating= 1;
			if (tutorialPage == 2)
				rulesAnimating = 2;
		}
		shared->buttons->next->Render();
	}
	if (tutorialPage == 2 || tutorialPage == 3) {
		shared->buttons->previous->Update();
		if (shared->buttons->previous->PressAndReleased()) {
			tutorialPage--;
			shared->sounds->switchSound->playSound();
			if (tutorialPage == 2)
				rulesAnimating= 4;
			if (tutorialPage == 3)
				rulesAnimating = 3;
		}
		shared->buttons->previous->Render();
	}

		sprintf(text,"PAGE 1/3");
		shared->images->RenderText(111+rulesAnimation,404,shared->MICRO10SILVER,text);


		sprintf(text,"PAGE 2/3");
		shared->images->RenderText(111+320+rulesAnimation,404,shared->MICRO10SILVER,text);
	

		sprintf(text,"PAGE 3/3");
		shared->images->RenderText(111+320+320+rulesAnimation,404,shared->MICRO10SILVER,text);

	if (gameMode != TUTORIAL) {
		nextState = gameMode;
		gameMode = TUTORIAL;
		transitioning = true;
	}
	FromTransition();
	Transition();
}
void CGame::TagAround(int color, int i, int j) {
	leveltagged[i][j] = 1;

	if (level[i-1][j] == color && leveltagged[i-1][j] == 0) {
		TagAround(color,i-1,j);
	}
	if (level[i+1][j] == color && leveltagged[i+1][j] == 0) {
		TagAround(color,i+1,j);
	}
	if (level[i][j-1] == color && leveltagged[i][j-1] == 0) {
		TagAround(color,i,j-1);
	}
	if (level[i][j+1] == color && leveltagged[i][j+1] == 0) {
		TagAround(color,i,j+1);
	}
}
void CGame::TagAroundPurple(int color, int i, int j) {
	purpletagged[i][j] = 1;

	if (level[i-1][j] == color && purpletagged[i-1][j] == 0) {
		TagAroundPurple(color,i-1,j);
	}
	if (level[i+1][j] == color && purpletagged[i+1][j] == 0) {
		TagAroundPurple(color,i+1,j);
	}
	if (level[i][j-1] == color && purpletagged[i][j-1] == 0) {
		TagAroundPurple(color,i,j-1);
	}
	if (level[i][j+1] == color && purpletagged[i][j+1] == 0) {
		TagAroundPurple(color,i,j+1);
	}
}

// check if a puzzle is completed
void CGame::CheckCompleted() {
	ResetTags();
	completePuzzleSequence = 1;
	for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= 16; j++) {
				if (level[i][j] == 6) {
					TagAround(6,i,j);
					j = 30;
					i = 30;
				}
			}
		}

	for (int z = 1; z < 4; z++ ){
		for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= 16; j++) {
				if (level[i][j] == z) {
					TagAround(z,i,j);
					j = 30;
					i = 30;
				}
			}
		}
		for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= 16; j++) {
				if (level[i][j] == z && leveltagged[i][j] == 0) {
					completePuzzleSequence = 0;
					ResetTags();
					return;
				}
			}
		}
	}
	// check if purple are attached as well
	for (int i = 1; i <= 16; i++) {
			for (int j = 1; j <= 16; j++) {
				if (level[i][j] == 6 && leveltagged[i][j] == 0) {
					completePuzzleSequence = 0;
					ResetTags();
					return;
				}
			}
		}
	//playfireworks = true;
	ResetTags();
	//winnerSound.play();
	shared->sounds->winner->playSound();
	shared->SaveToFile();
}
void CGame::GamePlay() {
	
	RenderGameBackground();
	shared->images->gameboard->Render(30,30);
	//shared->particleengine->InitFireworks();
	// animating pause menu
	if (pauseMenuAnimating > 0) {
		if (pauseMenuAnimating == 1) {
			if (pauseMenuAnimation < 0)
				pauseMenuAnimation+= 8;
			}
		if (pauseMenuAnimating == 2) {
			if (pauseMenuAnimation > -304)
				pauseMenuAnimation-= 8;
		}
		if (pauseMenuAnimation == -304 || pauseMenuAnimation == 0) {
			pauseMenuAnimating = 0;
		}
		shared->images->pausemenu->Render(35,30+5+pauseMenuAnimation);
		return;
	}
	// game is paused
	if (pausedMenu) {
		shared->images->pausemenu->Render(35,30+5+pauseMenuAnimation);
		shared->buttons->resetbutton->Update();
		if (shared->buttons->resetbutton->PressAndReleased()) {
			pausedMenu = false;
			shared->sounds->switchSound->playSound();
			GameInit();
		}
		shared->buttons->resetbutton->Render();
		shared->buttons->levelselect->Update();
		if (shared->buttons->levelselect->PressAndReleased()) {
			gameMode = LEVELSELECT;
			shared->sounds->menu->playSound();
			GameInit();
		}
		shared->buttons->levelselect->Render();
		shared->buttons->backbutton2->Update();
		if (shared->buttons->backbutton2->PressAndReleased()) {
			pausedMenu = false;
			pauseMenuAnimating= 2;
			shared->sounds->switchSound->playSound();
		}
		shared->buttons->backbutton2->Render();
		
		if (shared->savedata->soundOn) {
			shared->buttons->turnoffsound->Update();
			if (shared->buttons->turnoffsound->PressAndReleased()) {
				shared->savedata->soundOn = false;
				shared->sounds->switchSound->playSound();
			}
			shared->buttons->turnoffsound->Render();
			shared->images->turnoffsound->Render(142,122+pauseMenuAnimation);
		} else {
			shared->buttons->turnonsound->Update();
			if (shared->buttons->turnonsound->PressAndReleased()) {
				shared->savedata->soundOn = true;
				shared->sounds->switchSound->playSound();
			}
			shared->buttons->turnonsound->Render();
			shared->images->turnonsound->Render(142,122+pauseMenuAnimation);
		}
		if (!shared->savedata->colorBlindOn) {
			shared->buttons->colorblindon->Update();
			if (shared->buttons->colorblindon->PressAndReleased()) {
				shared->savedata->colorBlindOn = true;
				shared->sounds->switchSound->playSound();
			}
			shared->buttons->colorblindon->Render();
			shared->images->turnoncolorblindmode->Render(123,156+pauseMenuAnimation);
		} else {
			shared->buttons->colorblindoff->Update();
			if (shared->buttons->colorblindoff->PressAndReleased()) {
				shared->savedata->colorBlindOn = false;
				shared->sounds->switchSound->playSound();
			}
			shared->buttons->colorblindoff->Render();
			shared->images->turnoffcolorblindmode->Render(123,156+pauseMenuAnimation);
		}
		shared->buttons->menubutton->Update();
		if (shared->buttons->menubutton->PressAndReleased()) {
			pausedMenu = false;
			pauseMenuAnimating= 2;
			pauseMenuAnimation = 0; 
			shared->sounds->switchSound->playSound();
		}
		shared->buttons->menubutton->Render();
	
		if (gameMode != GAMEPLAY) {
			nextState = gameMode;
			gameMode = GAMEPLAY;
			transitioning = true;
		}
		Transition();
		return;
	}
	
	if (!completePuzzleSequence) {
		Input();
	}

	shared->buttons->undobutton->Update();
	// undo last move (has memory up to 100 moves)
	if (undoHasBeenPressed == 0 && shared->buttons->undobutton->IsPressed() && !completePuzzleSequence) {
		RestoreLastMove();
		undoHasBeenPressed= 10;
		shared->sounds->undo->playSound();
	//	completePuzzleSequence= true;
	}
	shared->buttons->undobutton->Render();
	shared->buttons->menubutton->Update();
	if (shared->buttons->menubutton->PressAndReleased()) {
		pausedMenu = true;
		pauseMenuAnimating= 1;
		pauseMenuAnimation = -304;
		shared->sounds->switchSound->playSound();
	}
	shared->buttons->menubutton->Render();

	// game
	RenderGame();

	
	// if the puzzle is completed
	if (completePuzzleSequence) {
		shared->savedata->stagePassed[1+levelSelected+(setSelected-1)*12] = true;
		//shared->SaveToFile();
		
		shared->buttons->nextlevel->Update();
		if (shared->buttons->nextlevel->PressAndReleased()) {
			changeLevelUponTransition= true;
			transitioning = true;
			shared->sounds->menu->playSound();
		}
		
		RenderCongratulations();
	} else {
		CheckCompleted(); // is puzzle solved
	}
	sprintf(text,"Level %d-%d", setSelected, levelSelected+1);
	shared->images->RenderText(105,6,shared->MICRO10SILVER,text);
	
	FromTransition();
	Transition();
	shared->particleengine->Update();
	shared->particleengine->Render();
	return;
}
void CGame::RenderGame() {
	// render gates
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			
			SDL_Rect src;
			int color, lcolor, bcolor, tcolor, rcolor;
			color = levelgates[i][j];
			
			lcolor = levelgates[i-1][j];
			rcolor = levelgates[i+1][j];
			bcolor = levelgates[i][j+1];
			tcolor = levelgates[i][j-1];
			if (color != 0) {
				src = getColorToRect(color,lcolor != color,rcolor != color,bcolor != color,tcolor != color);
				shared->images->blocks->Render(30- 14 + i*16,30 -14 + j*16,255,src);
				if (shared->savedata->colorBlindOn) {
						switch (color) {
							case 11: // blue
								shared->images->colorblindblue->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 12: // red
								shared->images->colorblindred->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 13:
								shared->images->colorblindgreen->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
						}
				}
			}
		}
	}
	SDL_Rect src; src.x = src.y = src.h = src.w = 0;
	// render game board
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			
			int color, lcolor, bcolor, tcolor, rcolor;

			if (levelgates[i][j] != 0 && level[i][j] == 0) {
				
			} else {
				color = level[i][j];
				if (color == 0) // if empty space dont draw anything
					continue;
				lcolor = level[i-1][j];
				rcolor = level[i+1][j];
				bcolor = level[i][j+1];
				tcolor = level[i][j-1];
				src = getColorToRect(color,lcolor != color,rcolor != color,bcolor != color,tcolor != color);
				if (levelMovingAnimation[i][j] <= 0) {
					shared->images->blocks->Render(30- 14 + i*16,30 -14 + j*16,255,src);
					if (shared->savedata->colorBlindOn) {
						switch (color) {
							case 1: // blue
								shared->images->colorblindblue->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 2: // red
								shared->images->colorblindred->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 3:
								shared->images->colorblindgreen->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 6: // purple
								shared->images->colorblindpurple->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
							case 9:
								shared->images->colorblindcyan->Render(30- 14 + i*16,30 -14 + j*16,255);
								break;
						}
					}
				}
			}
			
			if (levelMovingAnimation[i][j] > 0) {
				switch (levelMovingType[i][j]) {
					case 1: // left
						shared->images->blocks->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255,src);
						if (shared->savedata->colorBlindOn) {
							switch (color) {
									case 1: // blue
										shared->images->colorblindblue->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 2: // red
										shared->images->colorblindred->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 3:
										shared->images->colorblindgreen->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 6: // purple
										shared->images->colorblindpurple->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 9:
										shared->images->colorblindcyan->Render(levelMovingAnimation[i][j] + 30- 14 + i*16,30 -14 + j*16,255);
										break;
								}
						}
						break;
					case 2: // right
						shared->images->blocks->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255,src);
						if (shared->savedata->colorBlindOn) {
							switch (color) {
									case 1: // blue
										shared->images->colorblindblue->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 2: // red
										shared->images->colorblindred->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 3:
										shared->images->colorblindgreen->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 6: // purple
										shared->images->colorblindpurple->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255);
										break;
									case 9:
										shared->images->colorblindcyan->Render(-16+(16-levelMovingAnimation[i][j]) + 30- 14 + i*16,30 -14 + j*16,255);
										break;
								}
						}
						break;
					case 3:  // up 
						shared->images->blocks->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255,src);
						if (shared->savedata->colorBlindOn) {
							switch (color) {
									case 1: // blue
										shared->images->colorblindblue->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255);
										break;
									case 2: // red
										shared->images->colorblindred->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255);
										break;
									case 3:
										shared->images->colorblindgreen->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255);
										break;
									case 6: // purple
										shared->images->colorblindpurple->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255);
										break;
									case 9:
										shared->images->colorblindcyan->Render(30- 14 + i*16,levelMovingAnimation[i][j] + 30 -14 + j*16,255);
										break;
								}
						}
						break;
					case 4: // down
						shared->images->blocks->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255,src);
						if (shared->savedata->colorBlindOn) {
							switch (color) {
									case 1: // blue
										shared->images->colorblindblue->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255);
										break;
									case 2: // red
										shared->images->colorblindred->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255);
										break;
									case 3:
										shared->images->colorblindgreen->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255);
										break;
									case 6: // purple
										shared->images->colorblindpurple->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255);
										break;
									case 9:
										shared->images->colorblindcyan->Render(30- 14 + i*16,-16+(16-levelMovingAnimation[i][j]) + 30 -14 + j*16,255);
										break;
								}
						}					
						break;
				}
				
				levelMovingAnimation[i][j]-= 2;

			}

				
		}
	}
}
void CGame::RenderCongratulations() {
	shared->images->blackoverlaygameboard->Render(30,30,128);
	//shared->images->congratulations->Render(25,130);
	shared->buttons->nextlevel->Render();

	for (int i = 0; i < 16; i++) {
		if (!congratulationsLastStage) {
			if (congratulationsAnimationX[i]+1 < 34+16*i) {
				congratulationsAnimationX[i]+=2;
			} else if (congratulationsAnimationX[i] > 34+16*i) {
				congratulationsAnimationX[i]-=2;
			} else {
				congratulationsXAnimationDone[i] = true;
			}
			if (congratulationsAnimationY2[i]+1 < congratulationsAnimationY[i]) {
				congratulationsAnimationY2[i]+=2;
			} else if (congratulationsAnimationY2[i] > congratulationsAnimationY[i]) {
				congratulationsAnimationY2[i]-=2;
			} else {
				congratulationsYAnimationDone[i] = true;
			}
			bool isCongratulationsReallyDone = true;
			for (int i = 0; i < 16; i++) {
				if (!congratulationsYAnimationDone[i] || !congratulationsXAnimationDone[i]) {
					isCongratulationsReallyDone = false;
					break;
				}
			}
			if (isCongratulationsReallyDone) {
				for (int i = 0; i < 16; i++) {
					congratulationsAnimatingY[i] = 1;
				}
				congratulationsLastStage = true;
			}
			if (congratulationsYAnimationDone[i] == true && congratulationsXAnimationDone[i] == true) {
				congratulationsAnimatingY[i] = 1;
			}
			sprintf(text, "%c", congratulationsString[i]);
			shared->images->RenderText(congratulationsAnimationX[i],congratulationsAnimationY2[i],shared->CAPS18GREEN,text);
		} else {
		
			if (congratulationsAnimationY[i] > 170) {
				congratulationsAnimatingY[i] = 2;
			} else if (congratulationsAnimationY[i] < 130) {
				congratulationsAnimatingY[i] = 1;
			}
			if (congratulationsAnimatingY[i] == 1) // going down
				congratulationsAnimationY[i] += 1;
			if (congratulationsAnimatingY[i] == 2) // going up
				congratulationsAnimationY[i] -= 1;
			sprintf(text, "%c", congratulationsString[i]);
			shared->images->RenderText(34+16*i,congratulationsAnimationY[i],shared->CAPS18GREEN,text);
		}
		
	}
	if (levelCompletedX < 100)
		levelCompletedX+=4;
	if (levelCompletedX2 > 100)
		levelCompletedX2-=4;
	sprintf(text,"LEVEL %d - %d", setSelected, levelSelected+1);
	shared->images->RenderText(levelCompletedX,76,shared->CAPS12GREEN,text);
	sprintf(text,"COMPLETED", setSelected, levelSelected+1);
	shared->images->RenderText(levelCompletedX2,96,shared->CAPS12GREEN,text);

	// render congratulations animations , each set has different ones
	switch (setSelected) {
		case 1:
			// render falling leaves
			particleFallingCounter++;
			if (particleFallingCounter >= 60) {
				shared->particleengine->InitLeaves(0);
				particleFallingCounter= 0;
			}
			break;
		case 2:
			// render falling butterflies
			particleFallingCounter++;
			if (particleFallingCounter >= 60) {
				shared->particleengine->InitButterflies(1);
				particleFallingCounter= 0;
			}
			break;
		case 3:
			// snow rendering
			particleFallingCounter++;
			if (particleFallingCounter >= 30) {
				shared->particleengine->InitSnow();
				particleFallingCounter= 0;
			}
			break;
		case 4:
			// render falling leaves
			particleFallingCounter++;
			if (particleFallingCounter >= 60) {
				shared->particleengine->InitLeaves(1);
				particleFallingCounter= 0;
			}
			break;
		case 5:
			// render shooting stars
			particleFallingCounter++;
			if (particleFallingCounter >= 200) {
				shared->particleengine->InitShootingStar(1);
				particleFallingCounter= 0;
			}
			break;
		case 6:
			// bird animation
			if (birdAnimation == 0) { // initialize bird
				birdAnimation=1;
				birdX = -60;
				birdY = rand()%300+50;
			} else {
				birdX+=2;
				birdAnimation++;
				if (birdAnimation >= 320)
					birdAnimation = 0;
				if (birdAnimation % 6 == 0) {
					birdSpriteFrame++;
					if (birdSpriteFrame == 6)
						birdSpriteFrame = 0;
				}
			}
			shared->images->bird[birdSpriteFrame]->Render(birdX, birdY);
			break;
		case 7:
			// render falling butterflies
			particleFallingCounter++;
			if (particleFallingCounter >= 60) {
				shared->particleengine->InitButterflies(0);
				particleFallingCounter= 0;
			}
			break;
		case 8:
			// render shooting stars
			particleFallingCounter++;
			if (particleFallingCounter >= 200) {
				shared->particleengine->InitShootingStar(0);
				particleFallingCounter= 0;
			}
			break;
	}


}
void CGame::RenderGameBackground() {
	switch (setSelected) {
		case 1:
			shared->images->background->Render(0,0);
			break;
		case 2:
			shared->images->background2->Render(0,0);
			break;
		case 3:
			shared->images->background3->Render(0,0);
			break;
		case 4:
			shared->images->background4->Render(0,0);
			break;
		case 5:
			shared->images->background5->Render(0,0);
			break;
		case 6:
			shared->images->background6->Render(0,0);
			break;
		case 7:
			shared->images->background7->Render(0,0);
			break;
		case 8:
			shared->images->background8->Render(0,0);
			break;
	}
}
void CGame::LevelSelect() {
	// animating levels going left
	if (levelSelectionAnimating == 1) {
		if (levelSelectionAnimation > 0)
			levelSelectionAnimation-=8;
	}// animate levels going right
	if (levelSelectionAnimating == 2) {
		if (levelSelectionAnimation < 0)
			levelSelectionAnimation+=8;
	}

	if (pulsateAnimationDirection)
		pulsateAnimation-=4;
	else 
		pulsateAnimation+=4;

	if (pulsateAnimation == 64)
		pulsateAnimationDirection = false;
	if (pulsateAnimation == 252)
		pulsateAnimationDirection = true;

	shared->buttons->startbutton2->Update();
	if (shared->buttons->startbutton2->PressAndReleased()) {
		if (shared->savedata->stagePassed[0]) {   // levelSelected+(setSelected-1)*12]
			gameMode = GAMEPLAY;
			shared->sounds->menu->playSound();
			GameInit();
		}
	}
	
	shared->buttons->titlescreen->Update();
	if (shared->buttons->titlescreen->PressAndReleased()) {
		gameMode = TITLESCREEN;
		shared->sounds->menu->playSound();
	}
	
	shared->buttons->leftarrowlevel->Update();
	if (shared->buttons->leftarrowlevel->PressAndReleased()) {
		if (setSelected > 1) {
			setSelected--;
			levelSelected = 0;
			levelSelectionAnimating = 2;
			levelSelectionAnimation = -320;

			cursorAnimating = true;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
			shared->sounds->switchSound->playSound();
			return;
		}
	}
	
	shared->buttons->rightarrowlevel->Update();
	if (shared->buttons->rightarrowlevel->PressAndReleased()) {
		if (setSelected < 8) {
			setSelected++;
			levelSelectionAnimating = 1;
			levelSelectionAnimation = 320;
			levelSelected = 0;

			cursorAnimating = true;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
			shared->sounds->switchSound->playSound();
			return;
		}
	}
	RenderGameBackground();

	shared->buttons->leftarrowlevel->Render();
	shared->buttons->rightarrowlevel->Render();
	shared->buttons->titlescreen->Render();
	shared->buttons->startbutton2->Render();
	
	sprintf(text,"LEVEL SELECT");
	shared->images->RenderText(96,20,shared->MICRO10SILVER,text);
	
	sprintf(text,"SET %d", setSelected);
	shared->images->RenderText(129,275,shared->MICRO10SILVER,text);

	sprintf(text,"LEVEL %d", levelSelected+1);
	shared->images->RenderText(110,275+20,shared->MICRO10SILVER,text);

	// render levels that are being transitioned away
	if (levelSelectionAnimating == 1 || levelSelectionAnimating == 2) {
		if (levelSelectionAnimating == 1) {
			levelSelectionOffset= 320;
			setSelected--;
		}
		else if (levelSelectionAnimating == 2) {
			levelSelectionOffset= -320;
			setSelected++;
		}

		//shared->images->levelselectgameboards->Render(18+(levelSelectionAnimation-levelSelectionOffset),43);
		shared->images->levelselect[setSelected-1]->Render(levelSelectionAnimation-levelSelectionOffset+ 19,44);
		shared->images->levelselectgrid->Render(levelSelectionAnimation-levelSelectionOffset+ 18,43);
		shared->images->levelselectgrid->Render(levelSelectionAnimation-levelSelectionOffset+ 18,43+74);
		shared->images->levelselectgrid->Render(levelSelectionAnimation-levelSelectionOffset+ 18,43+74+74);
		// render game board
		for (int a = 0; a < 4; a++) {
			for (int b= 0; b < 3; b++) {

				if (!shared->savedata->stagePassed[(setSelected-1)*12 + b*4 + a])
					shared->images->blackoverlay->Render(levelSelectionAnimation-levelSelectionOffset + a*74 + 29- 14 + 3,b*74+54 -14 + 3, 128);
			}
		}
		if (levelSelectionAnimating == 1) {
			setSelected++;
		}
		else if (levelSelectionAnimating == 2) {
			setSelected--;
		}
	}
	//shared->images->levelselectgameboards->Render(18+levelSelectionAnimation,43);
	// render game board
	shared->images->levelselect[setSelected-1]->Render(levelSelectionAnimation+ 19,44);
	shared->images->levelselectgrid->Render(levelSelectionAnimation+ 18,43);
	shared->images->levelselectgrid->Render(levelSelectionAnimation+ 18,43+74);
	shared->images->levelselectgrid->Render(levelSelectionAnimation+ 18,43+74+74);
	for (int a = 0; a < 4; a++) {
		for (int b= 0; b < 3; b++) {
			if (!shared->savedata->stagePassed[(setSelected-1)*12 + b*4 + a])
				shared->images->blackoverlay->Render(levelSelectionAnimation + a*74 + 29- 14 + 3,b*74+54 -14 + 3, 128);
		}
	}
	
	if (!cursorAnimating) {
		if (shared->input->mousePressed && shared->input->x > 18 && shared->input->x < 18+66 &&
			shared->input->y > 43 && shared->input->y < 43 + 66) {
			cursorAnimating = true;
			levelSelected = 0;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74 && shared->input->x < 18+66+74 &&
			shared->input->y > 43 && shared->input->y < 43 + 66){
			cursorAnimating = true;
			levelSelected = 1;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74 && shared->input->x < 18+66+74+74 &&
			shared->input->y > 43 && shared->input->y < 43 + 66){
			cursorAnimating = true;
			levelSelected = 2;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74+74 && shared->input->x < 18+66+74+74+74 &&
			shared->input->y > 43 && shared->input->y < 43 + 66){
			cursorAnimating = true;
			levelSelected = 3;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18 && shared->input->x < 18+66 &&
			shared->input->y > 43+74 && shared->input->y < 43+74 + 66){
			cursorAnimating = true;
			levelSelected = 4;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74 && shared->input->x < 18+66+74 &&
			shared->input->y > 43+74 && shared->input->y < 43+74 + 66){
			cursorAnimating = true;
			levelSelected = 5;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74 && shared->input->x < 18+66+74+74 &&
			shared->input->y > 43+74 && shared->input->y < 43+74 + 66){
			cursorAnimating = true;
			levelSelected = 6;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74+74 && shared->input->x < 18+66+74+74+74 &&
			shared->input->y > 43+74 && shared->input->y < 43+74 + 66){
			cursorAnimating = true;
			levelSelected = 7;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18 && shared->input->x < 18+66 &&
			shared->input->y > 43+74+74 && shared->input->y < 43+74+74 + 66){
			cursorAnimating = true;
			levelSelected = 8;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74 && shared->input->x < 18+66+74 &&
			shared->input->y > 43+74+74 && shared->input->y < 43+74+74 + 66){
			cursorAnimating = true;
			levelSelected = 9;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74 && shared->input->x < 18+66+74+74 &&
			shared->input->y > 43+74+74 && shared->input->y < 43+74+74 + 66){
			cursorAnimating = true;
			levelSelected = 10;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
		if (shared->input->mousePressed && shared->input->x > 18+74+74+74 && shared->input->x < 18+66+74+74+74 &&
			shared->input->y > 43+74+74 && shared->input->y < 43+74+74 + 66){
			cursorAnimating = true;
			levelSelected = 11;
			cursorAnimatingX =cursorAnimationX;
			cursorAnimatingY =cursorAnimationY;
		}
	}
	// level selection box
	switch (levelSelected) {
		case 0:
			cursorAnimationX = 15;
			cursorAnimationY = 39;
			cursorAnimationX2 = 15;
			cursorAnimationY2 = 39;
			break;
		case 1:
			cursorAnimationX = 15+74;
			cursorAnimationY = 39;
			cursorAnimationX2 = 15+74;
			cursorAnimationY2 = 39;
			break;
		case 2:
			cursorAnimationX = 15+74+74;
			cursorAnimationY = 39;
			cursorAnimationX2 = 15+74+74;
			cursorAnimationY2 = 39;
			break;
		case 3:
			cursorAnimationX = 15+74+74+74;
			cursorAnimationY = 39;
			cursorAnimationX2 = 15+74+74+74;
			cursorAnimationY2 = 39;
			break;
		case 4:
			cursorAnimationX = 15;
			cursorAnimationY = 39+74;
			cursorAnimationX2 = 15;
			cursorAnimationY2 = 39+74;
			break;
		case 5:
			cursorAnimationX = 15+74;
			cursorAnimationY = 39+74;
			cursorAnimationX2 = 15+74;
			cursorAnimationY2 = 39+74;
			break;
		case 6:
			cursorAnimationX = 15+74+74;
			cursorAnimationY = 39+74;
			cursorAnimationX2 = 15+74+74;
			cursorAnimationY2 = 39+74;
			break;
		case 7:
			cursorAnimationX = 15+74+74+74;
			cursorAnimationY = 39+74;
			cursorAnimationX2 = 15+74+74+74;
			cursorAnimationY2 = 39+74;
			break;
		case 8:
			cursorAnimationX = 15;
			cursorAnimationY = 39+74+74;
			cursorAnimationX2 = 15;
			cursorAnimationY2 = 39+74+74;
			break;
		case 9:
			cursorAnimationX = 15+74;
			cursorAnimationY = 39+74+74;
			cursorAnimationX2 = 15+74;
			cursorAnimationY2 = 39+74+74;
			break;
		case 10:
			cursorAnimationX = 15+74+74;
			cursorAnimationY = 39+74+74;
			cursorAnimationX2 = 15+74+74;
			cursorAnimationY2 = 39+74+74;
			break;
		case 11:
			cursorAnimationX = 15+74+74+74;
			cursorAnimationY = 39+74+74;
			cursorAnimationX2 = 15+74+74+74;
			cursorAnimationY2 = 39+74+74;
			break;
	}

	if (cursorAnimating) {
		if (cursorAnimatingX > cursorAnimationX+3)
			cursorAnimatingX-= 4;
		else if (cursorAnimatingX < cursorAnimationX-3)
			cursorAnimatingX+= 4;
		else 
			cursorAnimatingX = cursorAnimationX;
		if (cursorAnimatingY > cursorAnimationY+3)
			cursorAnimatingY-= 4;
		else if (cursorAnimatingY < cursorAnimationY-3)
			cursorAnimatingY+= 4;
		else
			cursorAnimatingY = cursorAnimationY;

		if (cursorAnimatingY == cursorAnimationY && cursorAnimatingX == cursorAnimationX)
			cursorAnimating = false;
		shared->images->levelselectionbox->Render(cursorAnimatingX,cursorAnimatingY,255);
	}
	else {
		shared->images->levelselectionbox->Render(cursorAnimationX,cursorAnimationY,pulsateAnimation);
	}

	if (gameMode != LEVELSELECT) {
		nextState = gameMode;
		gameMode = LEVELSELECT;
		transitioning = true;
	}
	FromTransition();
	Transition();
	
}
void CGame::Ending() { 
	shared->images->background->Render();
	shared->images->ending->Render();
	shared->buttons->titlescreen->Update();
	cakeAnimationCounter++;
	if (cakeAnimationCounter > 15) {
		cakeAnimationCounter = 0; 
		cakeAnimation++;
		if (cakeAnimation == 3)
			cakeAnimation= 0;
	}

	shared->images->cake[cakeAnimation]->Render(120,160);
	if (shared->buttons->titlescreen->PressAndReleased()) {
		gameMode = TITLESCREEN;
		shared->sounds->menu->playSound();
	}
	shared->buttons->titlescreen->Render();
	particleFallingCounter++;
	if (particleFallingCounter >= 60) {
		shared->particleengine->InitMixed();
		particleFallingCounter= 0;
	}
	shared->particleengine->Update();
	shared->particleengine->Render();
	
	if (gameMode != ENDING) {
		nextState = gameMode;
		gameMode = ENDING;
		transitioning = true;
	}
	FromTransition();
	Transition();
}
void CGame::FromTransition() {
	// animate coming from a transition
	if (cameFromTransition) {
		if (changeLevelUponTransition) {
			if (setSelected == 8 && levelSelected == 11) {
				gameMode = ENDING;
				shared->sounds->ending->playSound();
			}
			changeLevelUponTransition = false;
			
			if (gameMode != ENDING && levelSelected == 11) {
				levelSelected = 0;
				setSelected++;
			} else {
				levelSelected++;
			}
			GameInit();
		}
		if (transitioningAnimation >= 30) {
			transitioningAnimation= 0;
			cameFromTransition= false;
		}
		else {
			transitioningAnimation++;
			shared->images->black->Render(0,0,255-((255/30.0) * transitioningAnimation));
		}
		
	}
}
void CGame::ResetTags() {
	for (int i = 1; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			leveltagged[i][j] = 0;
			purpletagged[i][j]= 0;
			
		}
	}
}
void CGame::changeColorUp(int color, int x, int y) {
	leveltagged[x][y] = 1;
		
	if (level[x+1][y] == color && leveltagged[x+1][y] != 1) {
		changeColorUp(color, x+1, y);
	}
	if (level[x-1][y] == color && leveltagged[x-1][y] != 1) {
		changeColorUp(color, x-1, y);
	}
	if (level[x][y-1] == color && leveltagged[x][y-1] != 1) {
		changeColorUp(color, x, y-1);
	}
	if ((level[x][y+1] == 1 || level[x][y+1] == 2 || level[x][y+1] == 3 || level[x][y+1] == 6) && leveltagged[x][y+1] != 1) {
		changeColorUp(level[x][y+1], x, y+1);
	}
}
void CGame::changeColorRight(int color, int x, int y) {
	leveltagged[x][y] = 1;
	
	if (level[x][y+1] == color && leveltagged[x][y+1] != 1) {
		changeColorRight(color, x, y+1);
	}
	if (level[x][y-1] == color && leveltagged[x][y-1] != 1) {
		changeColorRight(color, x, y-1);
	}
	if (level[x+1][y] == color && leveltagged[x+1][y] != 1) {
		changeColorRight(color, x+1, y);
	}
	if ((level[x-1][y] == 1 || level[x-1][y] == 2 || level[x-1][y] == 3 || level[x-1][y] == 6) && leveltagged[x-1][y] != 1) {
		changeColorRight(level[x-1][y], x-1, y);
	}
}
void CGame::MoveUp() {
	
	ResetTags();
	BackupBoard();
	// check what blocks cant move and tag them
	for (int j = 0; j < 16; j++) {
		for (int i = 1; i < 17; i++) {
			if ((levelgates[i][j] == 11 && level[i][j+1] != 1) || (levelgates[i][j] == 12 && level[i][j+1] != 2) || (levelgates[i][j] == 13 && level[i][j+1] != 3) || level[i][j] == 4 || leveltagged[i][j] == 1) {
				if ((level[i][j+1] == 1 || level[i][j+1] == 2 || level[i][j+1] == 3 || level[i][j+1] == 6) && leveltagged[i][j+1] != 1)
					changeColorUp(level[i][j+1], i, j+1);
				if (level[i][j+1] == 9) 
					leveltagged[i][j+1] = 1;
			}
		}
	}
	// check if we should move any purple blocks
	for (int a = 0; a < 18; a++) {
		for (int b = 0; b < 18; b++) {
			if (level[a][b] == 6 && leveltagged[a][b] != 1) {
				// check if any purple blocks are being nudged by a color block
				for (int k = b; k < 18; k++) {
					if (level[a][k] == 4 || level[a][k] == 0)
						break;
					if ((level[a][k] == 1 || level[a][k] == 2 || level[a][k] == 3) && leveltagged[a][k] != 1) {
						TagAroundPurple(6,a,b);
						break;
					}
				}	
			}
		}
	}
	// move the blocks up that can
	for (int j = 2; j < 17; j++) {
		for (int i  = 1; i < 17; i++) {
			bool moveGreyUp = false;
			if ((level[i][j] == 9) && level[i][j-1] == 0) {
				for (int t = j; t < 17; t++) {
					if (level[i][t] == 0 || level[i][t] == 4 || leveltagged[i][t] == 1) {
						moveGreyUp = false;
						break;
					}
					else if (level[i][t] == 1 || level[i][t] == 2 || level[i][t] == 3 || purpletagged[i][t] == 1) {
						moveGreyUp = true;
						break;
					}
				}
				if (moveGreyUp) {
					if (level[i][j] == 9) {
						level[i][j] = 0;
						level[i][j-1] = 9;
						levelMovingAnimation[i][j-1] = 16;
						levelMovingType[i][j-1] = 3;
					}
				}
			}
			
			for (int z = 1; z < 4; z++) {
				if (level[i][j] == z && level[i][j-1] == 0 && leveltagged[i][j] != 1)  {
					level[i][j] = 0;
					level[i][j-1] = z;
					levelMovingAnimation[i][j-1] = 16;
					levelMovingType[i][j-1] = 3;
				}
			}
			if (purpletagged[i][j] && level[i][j] == 6 && level[i][j-1] == 0 && leveltagged[i][j] != 1)  {
					level[i][j] = 0;
					level[i][j-1] = 6;
					levelMovingAnimation[i][j-1] = 16;
					levelMovingType[i][j-1] = 3;
			}
		}	
	}

}

void CGame::MoveLeft()  {
	BackupBoard();
	ResetTags();
	for (int i = 0; i < 17; i++) {
		for (int j = 1; j < 17; j++) {
			if ((levelgates[i][j] == 11 && level[i+1][j] != 1) || (levelgates[i][j] == 12 && level[i+1][j] != 2) || (levelgates[i][j] == 13 && level[i+1][j] != 3) || level[i][j] == 4 || leveltagged[i][j] == 1) {
				if ((level[i+1][j] == 1 || level[i+1][j] == 2 || level[i+1][j] == 3 || level[i+1][j] == 6) && leveltagged[i+1][j] != 1)
					changeColorLeft(level[i+1][j], i+1, j);
				if (level[i+1][j] == 9) 
					leveltagged[i+1][j] = 1;
			}
		}
	}
	// check if we should move any purple blocks
	for (int a = 0; a < 18; a++) {
		for (int b = 0; b < 18; b++) {
			if (level[a][b] == 6 && leveltagged[a][b] != 1) {
				// check if any purple blocks are being nudged by a color block
				for (int k = a; k < 18; k++) {
					if (level[k][b] == 4 || level[k][b] == 0)
						break;
					if ((level[k][b] == 1 || level[k][b] == 2 || level[k][b] == 3) && leveltagged[k][b] != 1) {
						TagAroundPurple(6,a,b);
						break;
					}
				}
				
			}
		}
	}
	for (int i = 1; i < 18; i++) {
		for (int j = 1; j < 17; j++) {
			bool moveGreyLeft = false;
			if ((level[i][j] == 9)  && level[i-1][j] == 0) {
				for (int t = i; t < 18; t++) {
					if (level[t][j] == 0 || level[t][j] == 4 || leveltagged[t][j] == 1) {
						moveGreyLeft = false;
						break;
					}
					else if (level[t][j] == 1 || level[t][j] == 2 || level[t][j] == 3 || purpletagged[t][j] == 1) {
						moveGreyLeft = true;
						break;
					}
				}
				if (moveGreyLeft) {

					if (level[i][j] == 9) {
						level[i][j] = 0;
						level[i-1][j] = 9;
						levelMovingAnimation[i-1][j] = 16;
						levelMovingType[i-1][j] = 1;
					}
				}
			}
			for (int z = 1; z < 4; z++)
				if (level[i][j] == z && level[i-1][j] == 0 && leveltagged[i][j] != 1) {
					level[i][j] = 0;
					level[i-1][j] = z;
					levelMovingAnimation[i-1][j] = 16;
					levelMovingType[i-1][j] = 1;
				}
			if (purpletagged[i][j] && level[i][j] == 6 && level[i-1][j] == 0 && leveltagged[i][j] != 1)  {
				level[i][j] = 0;
				level[i-1][j] = 6;
				levelMovingAnimation[i-1][j] = 16;
				levelMovingType[i-1][j] = 1;
			}
		}
			
	}
}

void CGame::changeColorDown(int color, int x, int y) {
	leveltagged[x][y] = 1;

	// recursively tag the connected blocks because they cant move either
	if (level[x][y+1] == color && leveltagged[x][y+1] != 1) {
		changeColorDown(color, x, y+1);
	}
	if (level[x+1][y] == color && leveltagged[x+1][y] != 1) {
		changeColorDown(color, x+1, y);
	}
	if (level[x-1][y] == color && leveltagged[x-1][y] != 1) {
		changeColorDown(color, x-1, y);
	}

	if ((level[x][y-1] == 1 || level[x][y-1] == 2 || level[x][y-1] == 3 || level[x][y-1] == 6) && leveltagged[x][y-1] != 1) {
		changeColorDown(level[x][y-1], x, y-1);
	}
}
void CGame::changeColorLeft(int color, int x, int y) {
		
	leveltagged[x][y] = 1;

	if (level[x-1][y] == color && leveltagged[x-1][y] != 1) {
		changeColorLeft(color, x-1, y);
	}
	if (level[x][y+1] == color && leveltagged[x][y+1] != 1) {
		changeColorLeft(color, x, y+1);
	}
	if (level[x][y-1] == color && leveltagged[x][y-1] != 1) {
		changeColorLeft(color, x, y-1);
	}
	if ((level[x+1][y] == 1 || level[x+1][y] == 2 || level[x+1][y] == 3 || level[x+1][y] == 6) && leveltagged[x+1][y] != 1) {
		changeColorLeft(level[x+1][y], x+1, y);
	}
}
void CGame::MoveRight() {
	BackupBoard();
	ResetTags();
	for (int i = 17; i > 1; i--) {
		for (int j = 1; j < 17; j++) {
			if ((levelgates[i][j] == 11 && level[i-1][j] != 1) || (levelgates[i][j] == 12 && level[i-1][j] != 2) || (levelgates[i][j] == 13 && level[i-1][j] != 3) || level[i][j] == 4 || leveltagged[i][j] == 1) {
				if ((level[i-1][j] == 1 || level[i-1][j] == 2 || level[i-1][j] == 3 || level[i-1][j] == 6) && leveltagged[i-1][j] != 1)
					changeColorRight(level[i-1][j], i-1, j);
				if (level[i-1][j] == 9) 
					leveltagged[i-1][j] = 1;
			}
		}
	}
	// check if we should move any purple blocks
	for (int a = 0; a < 18; a++) {
		for (int b = 0; b < 18; b++) {
			if (level[a][b] == 6 && leveltagged[a][b] != 1) {
				// check if any purple blocks are being nudged by a color block
				for (int k = a; k > 0; k--) {
					if (level[k][b] == 4 || level[k][b] == 0)
						break;
					if ((level[k][b] == 1 || level[k][b] == 2 || level[k][b] == 3) && leveltagged[k][b] != 1) {
						TagAroundPurple(6,a,b);
						break;
					}
				}
				
			}
		}
	}
	for (int i = 15; i > 0; i--) {
			for (int j = 16; j > 0; j--) {
				bool moveGreyRight = false;
				if ((level[i][j] == 9)  && level[i+1][j] == 0) {
					for (int t = i; t > 0; t--) {
						if (level[t][j] == 0 || level[t][j] == 4 || leveltagged[t][j] == 1) {
							moveGreyRight = false;
							break;
						}
						else if (level[t][j] == 1 || level[t][j] == 2 || level[t][j] == 3 || purpletagged[t][j] == 1) {
							moveGreyRight = true;
							break;
						}
					}
					if (moveGreyRight) {
						if (level[i][j] == 9) {
							level[i][j] = 0;
							level[i+1][j] = 9;
							levelMovingAnimation[i+1][j] = 16;
							levelMovingType[i+1][j] = 2;
						}
					}
				}
				for (int z = 1; z < 4; z++)
					if (level[i][j] == z && level[i+1][j] == 0 && leveltagged[i][j] != 1) {
						level[i][j] =0;
						level[i+1][j] = z;
						levelMovingAnimation[i+1][j] = 16;
						levelMovingType[i+1][j] = 2;
					}
				if (purpletagged[i][j] && level[i][j] == 6 && level[i+1][j] == 0 && leveltagged[i][j] != 1)  {
					level[i][j] = 0;
					level[i+1][j] = 6;
					levelMovingAnimation[i+1][j] = 16;
					levelMovingType[i+1][j] = 2;
				}
			}
		} 
}
void CGame::MoveDown() {
	
	BackupBoard();
	ResetTags();
	for (int i =1; i < 18; i++) {
		for (int j = 17; j > 1; j--) {
			if ((levelgates[i][j] == 11 && level[i][j-1] != 1) || (levelgates[i][j] == 12 && level[i][j-1] != 2) || (levelgates[i][j] == 13 && level[i][j-1] != 3) || level[i][j] == 4 || leveltagged[i][j] == 1) {
				if ((level[i][j-1] == 1 || level[i][j-1] == 2 || level[i][j-1] == 3 || level[i][j-1] == 6) && leveltagged[i][j-1] != 1)
					changeColorDown(level[i][j-1], i, j-1);
				if (level[i][j-1] == 9) {
					leveltagged[i][j-1] = 1;
				}
			}
		}
	}
	
	// check if we should move any purple blocks
	for (int a = 0; a < 18; a++) {
		for (int b = 0; b < 18; b++) {
			if (level[a][b] == 6 && leveltagged[a][b] != 1) {
				// check if any purple blocks are being nudged by a color block
				for (int k = b; k > 0; k--) {
					if (level[a][k] == 4 || level[a][k] == 0)
						break;
					if ((level[a][k] == 1 || level[a][k] == 2 || level[a][k] == 3) && leveltagged[a][k] != 1) {
						TagAroundPurple(6,a,b);
						break;
					}
				}
				
			}
		}
	}
	// move grey blocks down if need be
	for (int i = 16; i > 0; i--) {
		for (int j = 15; j > 0; j--) {
			bool moveGreyDown = false;
			if ((level[i][j] == 9)  && level[i][j+1] == 0) {
				for (int t = j; t > 0; t--) {
					if (level[i][t] == 0 || level[i][t] == 4 || leveltagged[i][t] == 1) {
						moveGreyDown = false;
						break;
					}
					else if (level[i][t] == 1 || level[i][t] == 2 || level[i][t] == 3 || purpletagged[i][t] == 1) {
						moveGreyDown = true;
						break;
					}
				}
				if (moveGreyDown) {
					if (level[i][j] == 9) {
						level[i][j] = 0;
						level[i][j+1] = 9;
						levelMovingAnimation[i][j+1] = 16;
						levelMovingType[i][j+1] = 4;
					}
				}
			}
			for (int z = 1; z < 4; z++)  {
				if (level[i][j] == z && level[i][j+1] == 0 && leveltagged[i][j] != 1) {
					level[i][j] = 0;
					level[i][j+1] = z;
					levelMovingAnimation[i][j+1] = 16;
					levelMovingType[i][j+1] = 4;
				}
			}
			if (purpletagged[i][j] && level[i][j] == 6 && level[i][j+1] == 0 && leveltagged[i][j] != 1)  {
					level[i][j] = 0;
					level[i][j+1] = 6;
					levelMovingAnimation[i][j+1] = 16;
					levelMovingType[i][j+1] = 4;
			}
		}
	}
}
void CGame::Splash() {

	shared->images->splashscreen->Render(0,0);
	SDL_Rect rect;
	rect.h = 480; rect.x = 0; rect.y = 0; rect.w = percentLoading * 320;
	shared->images->titlescreen->Render(0,0, 255,rect);
	if (shared->buttons->colorblindoff == NULL) {
		shared->buttons->InitButtons(); // colorblindoff
		percentLoading += 1.0/99.0;
	} else {
		shared->images->LoadImages(); // blackoverlaygameboard
		percentLoading += 1.0/99.0;
	}
	
	sprintf(text,"LOADING %.0f", percentLoading*100);

	shared->images->RenderText(103,422,shared->MICRO10SILVER,text);
	if (shared->images->blackoverlaygameboard != NULL)
	   gameMode = TITLESCREEN;

	shared->images->black->Render(0,0,128);
}
void CGame::Titlescreen() {
	shared->buttons->startbutton->Update();
	if (shared->buttons->startbutton->PressAndReleased()) {
		gameMode = LEVELSELECT;
		levelSelected= 0;
		shared->sounds->menu->playSound();
	}
	shared->buttons->rulesbutton->Update();
	if (shared->buttons->rulesbutton->PressAndReleased()) {
		gameMode = TUTORIAL;
		shared->sounds->menu->playSound();
	}
	shared->images->titlescreen->Render(0,0);
	// render falling leaves
	particleFallingCounter++;
	if (particleFallingCounter >= 60) {
		shared->particleengine->InitLeaves(0);
		particleFallingCounter= 0;
	}
	
	shared->particleengine->Update();
	shared->particleengine->Render();
	
	shared->buttons->startbutton->Render();
	shared->buttons->rulesbutton->Render();
	if (gameMode != TITLESCREEN) {
		nextState = gameMode;
		gameMode = TITLESCREEN;
		transitioning = true;
	}
	FromTransition();
	Transition();

	//Ending() ;
	return;
}
void CGame::Transition() {
	if (transitioning) {
		if (transitioningAnimation >= 30) {
			gameMode = nextState;
			transitioningAnimation= 0;
			transitioning = false;
			cameFromTransition= true;
			shared->images->black->Render(0,0,255);
		}
		else {
			transitioningAnimation++;
			shared->images->black->Render(0,0,(255/30.0) * transitioningAnimation);
		}
		
	}
}
void CGame::Update() {
	//cpu->linkShared(shared);

	if (shared->input->mouseToggle) {
		//	animatingTo = true;
	}
	if (gameMode == SPLASH) {
		Splash();
		return;
	}
	if (gameMode == ENDING) {
		Ending();
		return;
	}
	if (gameMode == TITLESCREEN) {
		Titlescreen();
		return;
	}
	if (gameMode == LEVELSELECT) {
		LevelSelect();
		return;
	}
	if (gameMode == TUTORIAL) {
		Tutorial();
		return;
	}
	if (gameMode == GAMEPLAY) {
		GamePlay();
		return;
	}
}
SDL_Rect CGame::getColorToRectForSmall(int color, bool lcolor, bool rcolor, bool bcolor, bool tcolor) {
		//	var src:Rectangle = new Rectangle();
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 4;
	src.h = 4;
	// what block color
	switch (color) {
		case 0:
			src.x = 0;
			src.y = 0;
			break;
		case 1:
			src.x =12;
			src.y = 0;
			break;
		case 2:
			src.x = 24;
			src.y = 0;
			break;
		case 3:
			src.x = 36;
			src.y = 0;
			break;
		case 4:
			src.x = 0;
			src.y = 0;
			break;
		case 6:
			src.x = 128/4;
			src.y = 80/4;
			src.h = 16/4;
			src.w = 16/4;
			return src;
			break;
		case 9:
			src.x = 112/4;
			src.y = 80/4;
			src.h = 16/4;
			src.w = 16/4;
			return src;
			break;
		case 11:
			src.x = 64/4;
			src.y = 80/4;
			src.h = 16/4;
			src.w = 16/4;
			return src;
			break;
		case 12:
			src.x = 80/4;
			src.y = 80/4;
			src.h = 16/4;
			src.w = 16/4;
			return src;
			break;
		case 13:
			src.x = 160/4;
			src.y = 80/4;
			src.h = 16/4;
			src.w = 16/4;
			return src;
			break;
	}
	
	// what block type (left right up down etc)
	if (lcolor && tcolor && rcolor && bcolor) {
		src.y += 12;
	}
	else if (lcolor && tcolor && rcolor) {
		src.x += 4;
		src.y += 12;
	}
	else if (lcolor && bcolor && rcolor) {
		src.x += 8;
		src.y += 12;
	}
	else if (bcolor && tcolor && rcolor) {
		src.x += 8;
		src.y += 8;
	}
	else if (lcolor && tcolor && bcolor) {
		src.x += 4;
		src.y += 8;
	}
	else if (lcolor && tcolor) {
	}
	else if (tcolor && rcolor) {
		src.x += 8;
	}
	else if (bcolor && rcolor) {
		src.x += 8;
		src.y += 8;
	}
	else if (lcolor && bcolor) {
		src.y += 8;
	}
	else if (tcolor && bcolor) {
		src.y += 8;
	}
	else if (lcolor && rcolor) {
		src.y += 20;
	}
	else if (lcolor) {
		src.y += 4;
	}
	else if (tcolor) {
		src.x += 4;
	}
	else if (bcolor) {
		src.x += 4;
		src.y += 8;
	}
	else if (rcolor) {
		src.x += 8;
		src.y += 4;
	}
	else {
		src.x += 4;
		src.y += 4;
	}

	//src.right = 16 + src.x; 
	//src.bottom = 16 + src.y;
	src.h = 4;
	src.w = 4;
	
	return src;
}
SDL_Rect CGame::getColorToRect(int color, bool lcolor, bool rcolor, bool bcolor, bool tcolor) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = 16;
	src.h = 16;
	// what block color
	switch (color) {
		case 0:
			src.x = 0;
			src.y = 0;
			break;
		case 1:
			src.x =48;
			src.y = 0;
			break;
		case 2:
			src.x = 96;
			src.y = 0;
			break;
		case 3:
			src.x = 144;
			src.y = 0;
			break;
		case 4:
			src.x = 0;
			src.y = 0;
			break;
		case 6:
			src.x = 144+48;
			src.y = 0;
			src.h = 16;
			src.w = 16;
			
			break;
		case 9: /// cyan blocks
			src.x = 112;
			src.y = 80;
			src.h = 16;
			src.w = 16;
			return src;
			break;
		case 11:
			src.x = 64;
			src.y = 80;
			src.h = 16;
			src.w = 16;
			return src;
			break;
		case 12:
			src.x = 80;
			src.y = 80;
			src.h = 16;
			src.w = 16;
			return src;
			break;
		case 13:
			src.x = 160;
			src.y = 80;
			src.h = 16;
			src.w = 16;
			return src;
			break;
	}
	
	// what block type (left right up down etc)
	if (lcolor && tcolor && rcolor && bcolor) {
		src.y += 48;
	}
	else if (lcolor && tcolor && rcolor) {
		src.x += 16;
		src.y += 48;
	}
	else if (lcolor && bcolor && rcolor) {
		src.x += 32;
		src.y += 48;
	}
	else if (bcolor && tcolor && rcolor) {
		src.x += 32;
		src.y += 64;
	}
	else if (lcolor && tcolor && bcolor) {
		src.x += 16;
		src.y += 64;
	}
	else if (lcolor && tcolor) {
	}
	else if (tcolor && rcolor) {
		src.x += 32;
	}
	else if (bcolor && rcolor) {
		src.x += 32;
		src.y += 32;
	}
	else if (lcolor && bcolor) {
		src.y += 32;
	}
	else if (tcolor && bcolor) {
		src.y += 64;
	}
	else if (lcolor && rcolor) {
		src.y += 80;
	}
	else if (lcolor) {
		src.y += 16;
	}
	else if (tcolor) {
		src.x += 16;
	}
	else if (bcolor) {
		src.x += 16;
		src.y += 32;
	}
	else if (rcolor) {
		src.x += 32;
		src.y += 16;
	}
	else {
		src.x += 16;
		src.y += 16;
	}

	//src.right = 16 + src.x; 
	//src.bottom = 16 + src.y;
	src.h = 16;
	src.w = 16;
	
	return src;
}
void CGame::Input() {

	arrowbuttonPressed = false;
	shared->buttons->leftarrow->Update();
	if (shared->buttons->leftarrow->IsPressed()) {
		leftIsPressed++;
	} else {
		leftIsPressed = 0;
	}
	// to keep track of fast moving control, so we dont make blocks move twice when person uses slow and fast control
	if (leftHasBeenPressed > 0)
		leftHasBeenPressed--;
	if (upHasBeenPressed > 0)
		upHasBeenPressed--;
	if (undoHasBeenPressed > 0)
		undoHasBeenPressed--;
	if (downHasBeenPressed > 0)
		downHasBeenPressed--;
	if (rightHasBeenPressed > 0)
		rightHasBeenPressed--;

	if (!arrowbuttonPressed && leftIsPressed > 8) {
		MoveLeft();
		leftIsPressed = 0;
		arrowbuttonPressed= true;
		leftHasBeenPressed = 5;
	}
	if (leftHasBeenPressed == 0 && leftIsPressed == 0 && !arrowbuttonPressed && shared->buttons->leftarrow->PressAndReleased()) {
		MoveLeft();
		arrowbuttonPressed= true;
	}
	shared->buttons->leftarrow->Render();

	shared->buttons->uparrow->Update();
	if (!arrowbuttonPressed && shared->buttons->uparrow->IsPressed()) {
		upIsPressed++;
	} else {
		upIsPressed = 0;
	}
	if (!arrowbuttonPressed && upIsPressed > 8) {
		MoveUp();
		upIsPressed = 0;
		arrowbuttonPressed= true;
		upHasBeenPressed = 5;
	}
	if (upHasBeenPressed == 0 && upIsPressed == 0 && !arrowbuttonPressed && shared->buttons->uparrow->PressAndReleased()) {
		MoveUp();
		arrowbuttonPressed= true;
	}
	shared->buttons->uparrow->Render();
	
	shared->buttons->rightarrow->Update();
	if (!arrowbuttonPressed && shared->buttons->rightarrow->IsPressed()) {
		rightIsPressed++;
	} else {
		rightIsPressed = 0;
	}
	if (!arrowbuttonPressed && rightIsPressed > 8) {
		MoveRight();
		rightIsPressed = 0;
		arrowbuttonPressed= true;
		rightHasBeenPressed = 5;
	}
	if (rightHasBeenPressed == 0 && rightIsPressed == 0 && !arrowbuttonPressed && shared->buttons->rightarrow->PressAndReleased()) {
		MoveRight();
		arrowbuttonPressed= true;
	}
	shared->buttons->rightarrow->Render();

	shared->buttons->downarrow->Update();
	if (!arrowbuttonPressed && shared->buttons->downarrow->IsPressed()) {
		downIsPressed++;
	} else {
		downIsPressed = 0;
	}
	if (!arrowbuttonPressed && downIsPressed > 8) {
		MoveDown();
		downIsPressed = 0;
		arrowbuttonPressed= true;
		downHasBeenPressed = 5;
	}
	if (downHasBeenPressed == 0 && downIsPressed == 0 && !arrowbuttonPressed && shared->buttons->downarrow->PressAndReleased()) {
		MoveDown();
		
		arrowbuttonPressed= true;
	}
	shared->buttons->downarrow->Render();
}
// backup board
void CGame::BackupBoard() {
	Level temp;
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			temp.level[i][j] = level[i][j];
		}
	}

	levelUndoMoves.push(temp);

	shared->sounds->drum->playSound();
}
// undo last move
void CGame::RestoreLastMove() {
	if (levelUndoMoves.empty())
		return;

	Level temp = levelUndoMoves.top();
	levelUndoMoves.pop();
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 18; j++) {
			level[i][j] = temp.level[i][j];
		}
	}

}