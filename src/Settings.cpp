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

using std::map;
using std::string;

Settings::Settings()
{
    
}

Settings::~Settings()
{
    
}

void Settings::initFrontendSettings()
{
    
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
    
    
    
    
    
}

map<string, map<string, string>> Settings::createIniFile(string filePath, map<string, map<string, string>> map)
{
    const char* path = filePath.c_str();
    FILE* iniFile = fopen(path, "a");
    
    for (auto it0 = map.begin(); it0 != map.end(); it0++)
    {
        fprintf(iniFile, "\n%s\n",it0->first.c_str());
        for (auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
        {
            fprintf(iniFile, "%s=%s\n",it1->first.c_str(),it1->second.c_str());
        }
    }
    fclose(iniFile);
    iniFile = NULL;
    path = NULL;
    
    return map;
}

map<string, map<string, string>> Settings::loadIniFile(INIReader reader, map<string, map<string, string>> map)
{
    for (auto it0 = map.begin(); it0 != map.end(); it0++)
    {
        for (auto it1 = it0->second.begin(); it1 != it0->second.end(); it1++)
        {
            string value = reader.Get(it0->first, it1->first, "");
            m_frontendSettings[it0->first][it1->first] = value;
        }
    }
    return map;
}

map<string, map<string, string>> Settings::frontend()
{
    string filePath = "Settings/Settings.ini";
    initFrontendSettings();
    INIReader reader(filePath);
    if (reader.ParseError() < 0) {
        return createIniFile(filePath, m_frontendSettings);
    }
    else
    {
        return loadIniFile(reader, m_frontendSettings);
    }
}