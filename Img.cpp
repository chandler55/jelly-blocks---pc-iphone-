#include "StdAfx.h"
#include "Img.h"

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}
int CImg::getWidth() {
	return width;
}
int CImg::getHeight() {
	return height;
}
CImg::CImg(char *filename)
{
	image = IMG_Load(filename);
	if (image == NULL) {
		printf("Couldn't load %s: %s\n", filename, SDL_GetError());
	}

	int format = SDL_PIXELFORMAT_ABGR8888; /* desired texture format */

	texture_id = SDL_CreateTextureFromSurface(format, image);
	if (texture_id == 0) {
		printf("problem with texture: %s",SDL_GetError());
	}
	SDL_SetTextureBlendMode(texture_id, SDL_TEXTUREBLENDMODE_BLEND);
	width = image->w;
	height = image->h;

	SDL_FreeSurface(image);
}

CImg::~CImg(void)
{

}
void CImg::InitWithPixels(void *pixels) {

}
void CImg::Init(char *filename) {
	image = IMG_Load(filename);
	if (image == NULL) {
		printf("Couldn't load %s: %s\n", filename, SDL_GetError());
	}

	int format = SDL_PIXELFORMAT_ABGR8888; /* desired texture format */

	texture_id = SDL_CreateTextureFromSurface(format, image);
	if (texture_id == 0) {
		printf("problem with texture: %s",SDL_GetError());
	}
	SDL_SetTextureBlendMode(texture_id, SDL_TEXTUREBLENDMODE_BLEND);
}

void CImg::Render(int x, int y,int alpha) {
	//SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
	dst.x = x;
	dst.y  = y;
	//	SDL_BlitSurface(image, NULL, screen, &dst);
	dst.w = width;
	dst.h = height;
	
	SDL_SetTextureAlphaMod(texture_id,(Uint8)alpha);
	SDL_RenderCopy(texture_id,0,&dst);
	
	
}

void CImg::ChangeColor(int r, int g, int b) {
	SDL_SetTextureColorMod(texture_id,r,g,b);
}
void CImg::RenderColor(SDL_Rect *fdst, int x, int y,int alpha, int r, int g, int b) {
	
//	SDL_SetTextureBlendMode(texture_id,SDL_TEXTUREBLENDMODE_ADD); //hmm
//	SDL_SetTextureColorMod(texture_id,r,g,b);
	RenderScale(fdst, x,y,alpha,0);
}
void CImg::Render(int x, int y,int alpha,SDL_Rect src) {
//	SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
	dst.x = x;
	dst.y  = y;
	//	SDL_BlitSurface(image, NULL, screen, &dst);
	dst.w = src.w;
	dst.h = src.h;
	
	SDL_SetTextureAlphaMod(texture_id,(Uint8)alpha);
	SDL_RenderCopy(texture_id,&src,&dst);
}

void CImg::RenderScale(SDL_Rect *fdst, int x, int y,int alpha,SDL_Rect *src =0) {
	//SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
	//SDL_SetTextureAlphaMod(texture_id,(Uint8)alpha);
	SDL_RenderCopy(texture_id,src,fdst);
}
void CImg::RenderText() {
	
}
void CImg::ChangeAlpha(int alpha) {
	SDL_SetTextureAlphaMod(texture_id,alpha);
	//SDL_SetAlpha(image, SDL_SRCALPHA, alpha);
}
