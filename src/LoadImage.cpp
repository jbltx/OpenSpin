#include "LoadImage.h"

LoadImage::LoadImage(SDL_Window *window,SDL_Renderer *renderer)
	: m_texture(NULL), m_imgWidth(0), m_imgHeight(0), m_window(window), m_renderer(renderer)
{

}

LoadImage::~LoadImage()
{
	cleanUp();
}

bool LoadImage::loadFromSurface(SDL_Surface *surface)
{
	if (surface == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Surface was already NULL");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Surface was already NULL", m_window);
		return false;
	}


	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	if (m_texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture creation error : %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
			"Texture creation error", m_window);
		SDL_FreeSurface(surface);

		if (surface != NULL)
			surface = NULL;

		return false;
	}

	m_imgHeight = surface->h;
	m_imgWidth = surface->w;

	SDL_FreeSurface(surface);

	if (surface != NULL)
		surface = NULL;

	return true;
}

void LoadImage::render(SDL_Rect *clip, SDL_Rect *renderQuad, 
						double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(m_renderer, m_texture, clip, renderQuad, angle, center, flip);
}

void LoadImage::cleanUp()
{
	if (m_texture != NULL)
	{
		SDL_DestroyTexture(m_texture);
		m_imgHeight = 0;
		m_imgWidth = 0;

		if (m_texture != NULL)
			m_texture = NULL;
	}
}