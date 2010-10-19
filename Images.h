#pragma once
#include "SDL.h"
#include "Img.h"
#include <stdio.h>
//#include "mmgr.h"
class CImages
{
public:
	CImg *black;
	CImg *titlescreen;
	CImg *background, *levelselecttext;
	CImg *gameboard, *pausemenu, *turnonsound, *turnoffsound;
	CImg *blocks, *background2, *background3, *background4, *background5, *background6, 
		*background7, *background8, *levelselectgameboards;
	CImg *fonts[6];
	CImg *smallblocks;
	CImg *levelselectionbox; 
	CImg *particles[20];
	CImg *congratulations;
	CImg *tutorialpage1, *tutorialpage2, *tutorialpage3;
	CImg *blackoverlay;
	CImg *tutorial[5];
	CImg *blackoverlaygameboard;
	CImg *turnoncolorblindmode, *turnoffcolorblindmode;
	CImg *colorblindblue, *colorblindred, *colorblindpurple, *colorblindcyan, *colorblindgreen;
	CImg *splashscreen;
	CImg *bird[6];
	CImg *cake[3];
	CImg *ending;
	CImg *levelselect[8];
	CImg *levelselectgrid;
	char characters[256];
	int characterMapping[256];
	int micro12rectangles[160][4][7];

	
	SDL_Rect *src;


public:
	CImages(void);
public:
	~CImages(void);
	void RenderText(int x, int y, int font, char *text, int alpha = 255);
	void RenderTextCustom(int x, int y, int font, char *text, int alpha = 255);
	void LoadImages();
};
