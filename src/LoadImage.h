#ifndef LOADIMAGE_H
#define LOADIMAGE_H

#include <SDL2/SDL.h>

class LoadImage
{
public:
	LoadImage(SDL_Window *window,SDL_Renderer *renderer);
	~LoadImage();

	bool loadFromSurface(SDL_Surface *surface);
	void render(SDL_Rect *clip, SDL_Rect *renderQuad, 
						double angle, SDL_Point *center, SDL_RendererFlip flip);

private:
	SDL_Texture *m_texture;
	int m_imgWidth;
	int m_imgHeight;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	void cleanUp();
};

#endif // LOADIMAGE_H