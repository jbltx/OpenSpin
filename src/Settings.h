#ifndef SETTINGS_H
#define SETTINGS_H

#include "../third_party/inih/cpp/INIReader.h"

class Settings
{
public:
    Settings();
    ~Settings();
    
    std::map<std::string, std::map<std::string, std::string>> frontend();
    std::map<std::string, std::map<std::string, std::string>> mainMenu();
    std::map<std::string, std::map<std::string, std::string>> system(std::string systemName);
    
private:
    std::map<std::string, std::map<std::string, std::string>> m_frontendSettings;
    std::map<std::string, std::string> m_fs_main;
    std::map<std::string, std::string> m_fs_resolution;
    std::map<std::string, std::string> m_fs_optimizer;
    std::map<std::string, std::string> m_fs_introvideo;
    std::map<std::string, std::string> m_fs_sound;
    std::map<std::string, std::string> m_fs_attractMode;
    std::map<std::string, std::string> m_fs_keyboard;
    std::map<std::string, std::string> m_fs_p1controls;
    std::map<std::string, std::string> m_fs_p2controls;
    std::map<std::string, std::string> m_fs_p1joystick;
    std::map<std::string, std::string> m_fs_p2joystick;
    std::map<std::string, std::string> m_fs_trackball;
    std::map<std::string, std::string> m_fs_spinner;
    std::map<std::string, std::string> m_fs_startupprogram;
    std::map<std::string, std::string> m_fs_exitprogram;
    std::map<std::string, std::string> m_fs_led;
    std::map<std::string, std::string> m_fs_hiscore;
    
    void initFrontendSettings();
    std::map<std::string, std::map<std::string, std::string>> createIniFile(std::string filePath, std::map<std::string, std::map<std::string, std::string>> map);
    std::map<std::string, std::map<std::string, std::string>> loadIniFile(INIReader reader, std::map<std::string, std::map<std::string, std::string>> map);
};

#endif // SETTINGS_H