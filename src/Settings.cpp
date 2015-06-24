//
//  Settings.cpp
//  OpenSpin
//
//  Created by Mickael Bonfill on 22/06/2015.
//
//

#include "Settings.h"
#include <iostream>
#include <stdio.h>
#include "ini.h"


Settings::Settings()
{
    IniParser fParser, mParser;
    if (fParser.read("Settings/Settings.ini") == IniParser::ERR::NO_READ_ACESS)
    {
        initFrontendSettings();
        fParser.write("Settings/Settings.ini", Settings::FRONTEND);
    }
    
    if (mParser.read("Settings/MainMenu.ini") == IniParser::ERR::NO_READ_ACESS)
    {
        initMenuSettings();
        mParser.write("Settings/MainMenu.ini", Settings::MAINMENU);
    }
    
    Settings::FRONTEND = fParser.getMap();
    Settings::MAINMENU = mParser.getMap();
}


Settings::~Settings()
{
    Settings::FRONTEND.clear();
    Settings::MAINMENU.clear();
    if (m_currentSystem != "")
    {
        Settings::SYSTEM(m_currentSystem).clear();
    }
}


void Settings::initMenuSettings()
{
    MAINMENU["wheel"]                  = m_ms_wheel;
    MAINMENU["pointer"]                = m_ms_pointer;
    MAINMENU["video defaults"]         = m_ms_videodefaults;
    MAINMENU["sounds"]                 = m_ms_sounds;
    MAINMENU["Special Art A"]          = m_ms_spearta;
    MAINMENU["Special Art B"]          = m_ms_speartb;
}

void Settings::initFrontendSettings()
{
    
    // Frontend settings initialization
    
    m_fs_main["Menu_Mode"]                   = "multi";
    m_fs_main["Single_Mode_Name"]            = "MAME";
    m_fs_main["Enable_Exit_Menu"]            = "true";
    m_fs_main["Enable_Exit"]                 = "true";
    m_fs_main["Exit_Default"]                = "yes";
    m_fs_main["Exit_Action"]                 = "exit";
    m_fs_main["Version"]                     = "1.0.0.0";
    m_fs_main["Last_System"]                 = "MAME";
    m_fs_main["Hyperlaunch_Path"]            = "C:\\Hyperspin\\HyperLaunch\\";
    
    
    m_fs_resolution["FullScreen"]            = "false";
    m_fs_resolution["Width"]                 = "800";
    m_fs_resolution["Height"]                = "600";
    m_fs_resolution["Scanlines_Active"]      = "false";
    m_fs_resolution["Scanlines_Image"]       = "";
    m_fs_resolution["Scanlines_Scale"]       = "2";
    m_fs_resolution["Scanlines_Alpha"]       = "0.1";
    
    
    m_fs_optimizer["CPU_Priority"]           = "normal";
    m_fs_optimizer["Quality"]                = "HIGH";
    m_fs_optimizer["Image_Smoothing"]        = "true";
    m_fs_optimizer["Animated_Backgrounds"]   = "true";
    m_fs_optimizer["Inter_Backgrounds"]      = "false";
    m_fs_optimizer["Level1_backgrounds"]     = "true";
    m_fs_optimizer["Level2_backgrounds"]     = "true";
    m_fs_optimizer["Level3_backgrounds"]     = "false";
    m_fs_optimizer["Level4_backgrounds"]     = "false";
    m_fs_optimizer["Special_Backgrounds"]    = "normal";
    m_fs_optimizer["Wait_For_Special"]       = "false";
    m_fs_optimizer["Animated_Artworks"]      = "true";
    m_fs_optimizer["Level1_Artworks"]        = "true";
    m_fs_optimizer["Level1_Artworks"]        = "true";
    
    
    m_fs_introvideo["Use_Intro"]             = "false";
    m_fs_introvideo["Stop_On_Keypress"]      = "true";
    
    
    m_fs_sound["Master_Volume"]              = "100";
    m_fs_sound["Video_Volume"]               = "100";
    m_fs_sound["Wheel_Volume"]               = "20";
    m_fs_sound["Interface_Volume"]           = "100";
    
    
    m_fs_attractMode["Active"]               = "true";
    m_fs_attractMode["Time"]                 = "60";
    m_fs_attractMode["MaxSpineTime"]         = "10";
    m_fs_attractMode["HyperSpin"]            = "true";
    m_fs_attractMode["Wait_For_Video"]       = "false";
    
    
    m_fs_keyboard["Key_Delay"]               = "true";
    
    
    m_fs_p1controls["Start"]                 = "13";
    m_fs_p1controls["Exit"]                  = "27";
    m_fs_p1controls["Up"]                    = "38";
    m_fs_p1controls["Down"]                  = "40";
    m_fs_p1controls["SkipUp"]                = "37";
    m_fs_p1controls["SkipDown"]              = "39";
    m_fs_p1controls["SkipUpNumber"]          = "70";
    m_fs_p1controls["SkipDownNumber"]        = "86";
    m_fs_p1controls["HyperSpin"]             = "32";
    m_fs_p1controls["Genre"]                 = "71";
    m_fs_p1controls["Favorites"]             = "76";
    
    
    m_fs_p2controls["Start"]                 = "69";
    m_fs_p2controls["Exit"]                  = "81";
    m_fs_p2controls["Up"]                    = "87";
    m_fs_p2controls["Down"]                  = "83";
    m_fs_p2controls["SkipUp"]                = "65";
    m_fs_p2controls["SkipDown"]              = "68";
    m_fs_p2controls["SkipUpNumber"]          = "74";
    m_fs_p2controls["SkipDownNumber"]        = "77";
    m_fs_p2controls["HyperSpin"]             = "88";
    m_fs_p2controls["Genre"]                 = "72";
    m_fs_p2controls["Favorites"]             = "90";
    
    
    m_fs_p1joystick["Enabled"]               = "false";
    m_fs_p1joystick["Joy"]                   = "0";
    m_fs_p1joystick["Threshold"]             = "40";
    m_fs_p1joystick["Start"]                 = "Button_1";
    m_fs_p1joystick["Exit"]                  = "Button_2";
    m_fs_p1joystick["Up"]                    = "Analog_Up";
    m_fs_p1joystick["Down"]                  = "Analog_Down";
    m_fs_p1joystick["SkipUp"]                = "Analog_Left";
    m_fs_p1joystick["SkipDown"]              = "Analog_Right";
    m_fs_p1joystick["SkipUpNumber"]          = "Button_3";
    m_fs_p1joystick["SkipDownNumber"]        = "Button_4";
    m_fs_p1joystick["HyperSpin"]             = "Button_5";
    m_fs_p1joystick["Genre"]                 = "Button_6";
    m_fs_p1joystick["Favorites"]             = "Button_7";
    
    
    m_fs_p2joystick["Enabled"]               = "false";
    m_fs_p2joystick["Joy"]                   = "1";
    m_fs_p2joystick["Threshold"]             = "40";
    m_fs_p2joystick["Start"]                 = "Button_1";
    m_fs_p2joystick["Exit"]                  = "Button_2";
    m_fs_p2joystick["Up"]                    = "Analog_Up";
    m_fs_p2joystick["Down"]                  = "Analog_Down";
    m_fs_p2joystick["SkipUp"]                = "Analog_Left";
    m_fs_p2joystick["SkipDown"]              = "Analog_Right";
    m_fs_p2joystick["SkipUpNumber"]          = "Button_3";
    m_fs_p2joystick["SkipDownNumber"]        = "Button_4";
    m_fs_p2joystick["HyperSpin"]             = "Button_5";
    m_fs_p2joystick["Genre"]                 = "Button_6";
    m_fs_p2joystick["Favorites"]             = "Button_7";

    
    m_fs_trackball["Enabled"]                = "false";
    m_fs_trackball["Sensitivity"]            = "90";
    
    
    m_fs_spinner["Enabled"]                  = "false";
    m_fs_spinner["Sensitivity"]              = "90";
    
    
    m_fs_startupprogram["Executable"]        = "";
    m_fs_startupprogram["Parameters"]        = "";
    m_fs_startupprogram["Working_Directory"] = "";
    m_fs_startupprogram["WinState"]          = "";
    
    
    m_fs_exitprogram["Executable"]           = "";
    m_fs_exitprogram["Parameters"]           = "";
    m_fs_exitprogram["Working_Directory"]    = "";
    m_fs_exitprogram["WinState"]             = "NORMAL";
    
    
    m_fs_led["Active"]                       = "false";
    m_fs_led["Path"]                         = "";
    
    
    m_fs_hiscore["Active"]                   = "false";
    m_fs_hiscore["Y"]                        = "550";
    m_fs_hiscore["Delay"]                    = "2";
    
    
    FRONTEND["Main"]               = m_fs_main;
    FRONTEND["Resolution"]         = m_fs_resolution;
    FRONTEND["Optimizer"]          = m_fs_optimizer;
    FRONTEND["IntroVideo"]         = m_fs_introvideo;
    FRONTEND["Sound"]              = m_fs_sound;
    FRONTEND["AttractMode"]        = m_fs_attractMode;
    FRONTEND["Keyboard"]           = m_fs_keyboard;
    FRONTEND["P1 Controls"]        = m_fs_p1controls;
    FRONTEND["P2 Controls"]        = m_fs_p2controls;
    FRONTEND["P1 Joystick"]        = m_fs_p1joystick;
    FRONTEND["P2 Joystick"]        = m_fs_p2joystick;
    FRONTEND["Trackball"]          = m_fs_trackball;
    FRONTEND["Spinner"]            = m_fs_spinner;
    FRONTEND["Startup Program"]    = m_fs_startupprogram;
    FRONTEND["Exit Program"]       = m_fs_exitprogram;
    FRONTEND["LEDBlinky"]          = m_fs_led;
    FRONTEND["HiScore"]            = m_fs_hiscore;


    
}


bool Settings::fileExists(std::string fileName)
{
    IniParser testParser;
    if (testParser.read("Settings/"+fileName+".ini") == IniParser::ERR::NO_READ_ACESS) {
        return false;
    }
    return true;
}


std::map<std::string, std::map<std::string, std::string>> Settings::SYSTEM(std::string systemName)
{
    IniParser sParser;
    m_currentSystem = systemName;
    sParser.read("Settings/"+systemName+".ini");
    return sParser.getMap();
}