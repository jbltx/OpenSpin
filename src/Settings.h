#ifndef SETTINGS_H
#define SETTINGS_H

#include <map>
#include <string>

class Settings
{
public:
    
    bool fileExists(std::string fileName);
    
    Settings();
    ~Settings();
    
    std::map<std::string, std::map<std::string, std::string>> FRONTEND;
    std::map<std::string, std::map<std::string, std::string>> MAINMENU;
    std::map<std::string, std::map<std::string, std::string>> SYSTEM(std::string systemName);
    
private:
    
    std::string m_currentSystem;
    
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
    
    
    std::map<std::string, std::string> m_ms_wheel;
    std::map<std::string, std::string> m_ms_pointer;
    std::map<std::string, std::string> m_ms_videodefaults;
    std::map<std::string, std::string> m_ms_sounds;
    std::map<std::string, std::string> m_ms_spearta;
    std::map<std::string, std::string> m_ms_speartb;
    
    
    std::map<std::string, std::string> m_ss_exeinfo;
    std::map<std::string, std::string> m_ss_filters;
    std::map<std::string, std::string> m_ss_themes;
    std::map<std::string, std::string> m_ss_wheel;
    std::map<std::string, std::string> m_ss_pointer;
    std::map<std::string, std::string> m_ss_videodefaults;
    std::map<std::string, std::string> m_ss_sounds;
    std::map<std::string, std::string> m_ss_navigation;
    std::map<std::string, std::string> m_ss_spearta;
    std::map<std::string, std::string> m_ss_speartb;
    std::map<std::string, std::string> m_ss_speartc;
    std::map<std::string, std::string> m_ss_gametext;
    
    
    void initFrontendSettings();
    void initMenuSettings();
    
};

#endif // SETTINGS_H