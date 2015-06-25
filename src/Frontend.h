#ifndef FRONTEND_H
#define FRONTEND_H

#include <SDL.h>
#include <stdio.h>
#include "third_party/tinyxml2/tinyxml2.h"
#include "third_party/rapidjson/rapidjson.h"
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
	void drawSystemMenu(const char * sysName);
	void cleanUp();
	void checkUpdates();

    Settings m_settings;
    
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event m_event;
    
    const char * m_currentSysName;
};

#endif // FRONTEND_H
