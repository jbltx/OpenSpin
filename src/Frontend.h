#ifndef FRONTEND_H
#define FRONTEND_H

#include <SDL.h>
#include <stdio.h>

#include "Settings.h"

enum class FrontendEstates : unsigned int
{
	MAIN_MENU_ESTATE,
	SYSTEM_MENU_ESTATE,
	EXIT_ESTATE,
	TOTAL_ESTATES
};

class Frontend
{
public:
	Frontend();
	~Frontend();

	int exec();
	void writeLog(const char* msg);

protected:
	FrontendEstates frontendEstate;

private:
	bool initSDL();
	bool loadMedia();
	void applicationLoop();
	void handleEvents(SDL_Event event);
	void mainMenuHandleEvents(SDL_Event event);
	void systemMenuHandleEvents(SDL_Event event);
	void draw();
	void drawMainMenu();
	void drawSystemMenu();
	void cleanUp();
	void checkUpdates();


	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event m_event;
};

#endif // FRONTEND_H
