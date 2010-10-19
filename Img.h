#pragma once
#include "SDL_Image.h"
#include "SDL.h"
#include <string>
class CImg
{
	int width, height;
	SDL_Surface *image;
	SDL_Rect dst;
	SDL_TextureID texture_id;

public:
	CImg(char *filename);
public:
	~CImg(void);
	void InitWithPixels(void *pixels);
	void Render(int x=0, int y =0, int alpha = 255);
	void ChangeAlpha(int alpha);
	SDL_Surface *getSurface() { return image; }
	void Init(char *filename);
	void Render(int x, int y,int alpha,SDL_Rect src);
	void RenderText();
	void RenderColor(SDL_Rect *fdst,int x, int y,int alpha, int r, int g, int b);
	void RenderScale(SDL_Rect *fdst, int x, int y,int alpha,SDL_Rect *src);
	void ChangeColor(int r, int g, int b);
	int getWidth();
	int getHeight();
};
