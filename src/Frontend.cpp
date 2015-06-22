#include "Frontend.h"
#include <iostream>
#include <ctime>

Frontend::Frontend()
	: m_window(NULL), m_renderer(NULL)
{
	frontendEstate = FrontendEstates::MAIN_MENU_ESTATE;
    
    // Frontend settings initialization
    m_frontendSettings["Main"]               = m_fs_main;
    m_frontendSettings["Resolution"]         = m_fs_resolution;
    m_frontendSettings["Optimizer"]          = m_fs_optimizer;
    m_frontendSettings["IntroVideo"]         = m_fs_introvideo;
    m_frontendSettings["Sound"]              = m_fs_sound;
    m_frontendSettings["AttractMode"]        = m_fs_attractMode;
    m_frontendSettings["Keyboard"]           = m_fs_keyboard;
    m_frontendSettings["P1 Controls"]        = m_fs_p1controls;
    m_frontendSettings["P2 Controls"]        = m_fs_p2controls;
    m_frontendSettings["P1 Joystick"]        = m_fs_p1joystick;
    m_frontendSettings["P2 Joystick"]        = m_fs_p2joystick;
    m_frontendSettings["Trackball"]          = m_fs_trackball;
    m_frontendSettings["Spinner"]            = m_fs_spinner;
    m_frontendSettings["Startup Program"]    = m_fs_startupprogram;
    m_frontendSettings["Exit Program"]       = m_fs_exitprogram;
    m_frontendSettings["LEDBlinky"]          = m_fs_led;
    m_frontendSettings["HiScore"]            = m_fs_hiscore;
    
    
    m_fs_main["Menu_Mode"]                   = "multi";
    m_fs_main["Single_Mode"]                 = "false";
    m_fs_main["Enable_Exit_Menu"]            = "false";
    m_fs_main["Enable_Exit"]                 = "multi";
    m_fs_main["Exit_Default"]                = "multi";
    m_fs_main["Exit_Action"]                 = "multi";
    m_fs_main["Version"]                     = "multi";
    m_fs_main["Last_System"]                 = "multi";
    m_fs_main["Hyperlaunch_Path"]            = "multi";
    
    
    m_fs_resolution["FullScreen"]            = "multi";
    m_fs_resolution["Width"]                 = "multi";
    m_fs_resolution["Height"]                = "multi";
    m_fs_resolution["Scanlines_Active"]      = "multi";
    m_fs_resolution["Scanlines_Image"]       = "multi";
    m_fs_resolution["Scanlines_Scale"]       = "multi";
    m_fs_resolution["Scanlines_Alpha"]       = "multi";
}

Frontend::~Frontend()
{
	writeLog("Quiting Frontend");

	cleanUp();

	writeLog("Bye!");
}

int Frontend::exec()
{
	writeLog("Frontend Started");
    
    loadFrontendSettings();

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
	
	writeLog("Going windowed mode ");

	m_window = SDL_CreateWindow("Frontend", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		640, 480, 
		SDL_WINDOW_SHOWN);

	if (m_window == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create main window : %s", 
								SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", 
								"Unable to create main window", m_window);
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, 
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
		drawSystemMenu();
}

void Frontend::drawMainMenu()
{
	SDL_SetRenderDrawColor(m_renderer, 0,0,0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void Frontend::drawSystemMenu()
{

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

bool Frontend::loadFrontendSettings()
{
    if (CANTFINDFILE) {
        CREATEFILE
    }
    else
    {
        for (auto i = m_frontendSettings.begin(); i != m_frontendSettings.end(); i++)
        {
            
        }
    }

    return true;
}

std::string Frontend::getIniProperty(std::string filepath, std::string category, std::string propertyName)
{
    INIReader reader(filepath);
    if (reader.ParseError() < 0) {
        std::cout << "Can't load 'test.ini'\n";
        return "ERROR";
    }
    return reader.Get(category, propertyName, "UNKNOWN");
}

void Frontend::checkUpdates()
{
	writeLog("Checking for updates");
	// do some stuff...
	writeLog("Update Check Complete ");
}