#include "Frontend.h"
#include <iostream>
#include <ctime>
#include <map>
#include <string>

using namespace std;

Frontend::Frontend() : m_window(NULL), m_renderer(NULL)
{
	frontendEstate = FrontendEstates::MAIN_MENU_ESTATE;
}

Frontend::~Frontend()
{
	writeLog("Quiting Frontend");

	cleanUp();

	writeLog("Bye!");
}

int Frontend::exec(const bool noServerArg, const char * usernameArg, const char * pwdArg, const int portArg)
{
	writeLog("Frontend Started");
    
    if(m_settings.FRONTEND.empty())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Can't intialize Frontend settings... Exiting.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                                 "Can't intialize Frontend settings... Exiting.", m_window);
        return -1;
    }
    
    if (m_settings.MAINMENU.empty()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Can't intialize Main Menu settings... Exiting.");
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                                 "Can't intialize Main Menu settings... Exiting.", m_window);
        return -1;
    }
    
	if (!initSDL())
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to initialize SDL", m_window);
		return -1;
	}

	checkUpdates();

	if (!loadMedia())
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load media");
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to load media", m_window);
		return -1;
	}

	applicationLoop();

	return 0;
}

bool Frontend::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initialize SDL library : %s", 
								SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to initialize SDL library", m_window);
		return false;
	}
    
    SDL_WindowFlags fullscreenFlag;
    if (m_settings.FRONTEND["Resolution"]["FullScreen"] == "true") {
        writeLog("Going fullscreen mode ");
        fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else {
        writeLog("Going windowed mode ");
        fullscreenFlag = SDL_WINDOW_SHOWN;
    }
    
    int width  = atoi(m_settings.FRONTEND["Resolution"]["Width"].c_str());
    int height = atoi(m_settings.FRONTEND["Resolution"]["Height"].c_str());
    
    #ifdef ANDROID_NDK
    width = height = 0;
    fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
    #endif
	
	m_window = SDL_CreateWindow("Frontend",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		width, height,
		fullscreenFlag );

	if (m_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create main window : %s", 
								SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to create main window", m_window);
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1,
                SDL_RENDERER_TARGETTEXTURE |
				SDL_RENDERER_ACCELERATED |
                SDL_RENDERER_PRESENTVSYNC);
    

	if (m_renderer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create main renderer : %s", 
								SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to create main renderer", m_window);
		return false;
	}


	
	return true;
}

bool Frontend::loadMedia()
{
	return true;
}

void Frontend::applicationLoop()
{
	while (frontendEstate != FrontendEstates::EXIT_ESTATE)
	{
		//Check for events (user inputs)
		while (SDL_PollEvent(&m_event) != 0)
		{
			if (m_event.type == SDL_QUIT || (m_event.type == SDL_KEYDOWN 
								&& m_event.key.keysym.sym == SDLK_ESCAPE 
								&& frontendEstate == FrontendEstates::MAIN_MENU_ESTATE))
				frontendEstate = FrontendEstates::EXIT_ESTATE;
			handleEvents(m_event);
		}
		
		//Draw objects on the screen
		draw();
	}
}

void Frontend::handleEvents(SDL_Event event)
{
	if (frontendEstate == FrontendEstates::MAIN_MENU_ESTATE)
		mainMenuHandleEvents(event);
	if (frontendEstate == FrontendEstates::SYSTEM_MENU_ESTATE)
		systemMenuHandleEvents(event);
}

void Frontend::mainMenuHandleEvents(SDL_Event event)
{	

}

void Frontend::systemMenuHandleEvents(SDL_Event event)
{

}

void Frontend::draw()
{
	if(frontendEstate == FrontendEstates::MAIN_MENU_ESTATE)
		drawMainMenu();
	if(frontendEstate == FrontendEstates::SYSTEM_MENU_ESTATE)
		drawSystemMenu(m_currentSysName);
}

void Frontend::drawMainMenu()
{
	SDL_SetRenderDrawColor(m_renderer, 0,0,0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Frontend::drawSystemMenu(const char * sysName)
{
    std::cout << "Going to render : " << sysName << std::endl;
}

void Frontend::cleanUp()
{
	SDL_DestroyRenderer(m_renderer);
	if (m_renderer != NULL)
		m_renderer = NULL;
	SDL_DestroyWindow(m_window);
	if (m_window != NULL)
		m_window = NULL;
	SDL_Quit();
    
}

void Frontend::writeLog(const char* msg)
{
	time_t currentTime;
	struct tm *localTime;

	time( &currentTime );
	localTime = localtime( &currentTime );

	int Day    = localTime->tm_mday;
	int Month  = localTime->tm_mon + 1;
	int Year   = localTime->tm_year + 1900;
	int Hour   = localTime->tm_hour;
	int Min    = localTime->tm_min;
	int Sec    = localTime->tm_sec;

	FILE* pFile = fopen("log.txt", "a");
	fprintf(pFile, "%02d/%02d/%04d - %02d:%02d:%02d | %s\n",Month,Day,Year,Hour,Min,Sec,msg);
	fclose(pFile);
    
    if (pFile != NULL)
        pFile = NULL;
}

void Frontend::checkUpdates()
{
	writeLog("Checking for updates");
	// do some stuff...
	writeLog("Update Check Complete ");
}