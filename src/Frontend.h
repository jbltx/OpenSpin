#ifndef FRONTEND_H
#define FRONTEND_H

#include <SDL.h>
#include <stdio.h>

#include "MainMenuSetting.h"

#include "../third_party/inih/cpp/INIReader.h"

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
    std::string getIniProperty(std::string filepath, std::string category, std::string propertyName);

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
    bool loadFrontendSettings();
    
    std::map<std::string, std::map<std::string, std::string>> m_frontendSettings;
    std::map<std::string, std::string> m_fs_main;
    std::map<std::string, std::string> m_fs_resolution;
    std::map<std::string, std::string> m_fs_optimizer;
    std::map<std::string, std::string> m_fs_introvideo;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event m_event;
};

#endif // FRONTEND_H
