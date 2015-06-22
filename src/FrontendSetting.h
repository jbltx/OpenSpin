//
//  FrontendSetting.h
//  OpenSpin
//
//  Created by Mickael Bonfill on 22/06/2015.
//
//

#ifndef FRONTENDSETTING_H
#define FRONTENDSETTING_H

#include <stdio.h>

class FrontendSetting
{
public:
    FrontendSetting();
    ~FrontendSetting();    
};

class Main : public FrontendSetting
{
private:
    const char* Menu_Mode;
    const char* Single_Mode;
    const char* Enable_Exit_Menu;
    const char* Enable_Exit;
    const char* Exit_Default;
    const char* Exit_Action;
    const char* Version;
    const char* Last_System;
    const char* Hyperlaunch_Path;
};

class Resolution : public FrontendSetting
{
private:
    const char* FullScreen;
    const char* Width;
    const char* Height;
    const char* Scanlines_Active;
    const char* Scanlines_Image;
    const char* Scanlines_Scale;
    const char* Scanlines_Alpha;
};

class Optimizer : public FrontendSetting
{
    const char* CPU_Priority;
    const char* Quality;
    const char* Image_Smoothing;
    const char* Animated_Backgrounds;
    const char* Inter_Backgrounds;
    const char* Leve1_Backgrounds;
    const char* Leve2_Backgrounds;
    const char* Leve3_Backgrounds;
    const char* Leve4_Backgrounds;
    const char* Special_Backgrounds;
    const char* Wait_For_Special;
    const char* Animated_Artworks;
    const char* Level1_Artworks;
    const char* Level2_Artworks;
};

class IntroVideo : public FrontendSetting
{
private:
    const char* Use_Intro;
    const char* Stop_On_Keypress;
};

class Sound : public FrontendSetting
{
private:
    const char* Master_Volume;
    const char* Video_Volume;
    const char* Wheel_Volume;
    const char* Interface_Volume;
};

class AttractMode : public FrontendSetting
{
private:
    const char* Active;
    const char* Time;
    const char* MaxSpinTime;
    const char* HyperSpin;
    const char* Wait_For_Video;
};

class Keyboard : public FrontendSetting
{
private:
    const char* Key_Delay;
};

class P1_Controls : public FrontendSetting
{
private:
    const char* Start;
    const char* Exit;
    const char* Up;
    const char* Down;
    const char* SkipUp;
    const char* SkipDown;
    const char* SkipUpNumber;
    const char* SkipDownNumber;
    const char* HyperSpin;
    const char* Genre;
    const char* Favorites;
};

class P2_Controls : public FrontendSetting
{
private:
    const char* Start;
    const char* Exit;
    const char* Up;
    const char* Down;
    const char* SkipUp;
    const char* SkipDown;
    const char* SkipUpNumber;
    const char* SkipDownNumber;
    const char* HyperSpin;
    const char* Genre;
    const char* Favorites;
};

class P1_Joystick : public FrontendSetting
{
private:
    const char* Enabled;
    const char* Joy;
    const char* Threshold;
    const char* Start;
    const char* Exit;
    const char* Up;
    const char* Down;
    const char* SkipUp;
    const char* SkipDown;
    const char* SkipUpNumber;
    const char* SkipDownNumber;
    const char* HyperSpin;
    const char* Genre;
    const char* Favorites;
};

class P2_Joystick : public FrontendSetting
{
private:
    const char* Enabled;
    const char* Joy;
    const char* Threshold;
    const char* Start;
    const char* Exit;
    const char* Up;
    const char* Down;
    const char* SkipUp;
    const char* SkipDown;
    const char* SkipUpNumber;
    const char* SkipDownNumber;
    const char* HyperSpin;
    const char* Genre;
    const char* Favorites;
};

class Trackball : public FrontendSetting
{
private:
    const char* Enabled;
    const char* Sensitivity;
};

class Spinner : public FrontendSetting
{
private:
    const char* Enabled;
    const char* Sensitivity;
};

class Startup_Program : public FrontendSetting
{
private:
    const char* Executable;
    const char* Parameters;
    const char* Working_Directory;
    const char* WinState;
};

class Exit_Program : public FrontendSetting
{
private:
    const char* Executable;
    const char* Parameters;
    const char* Working_Directory;
    const char* WinState;
};

class LEDBlinky : public FrontendSetting
{
private:
    const char* Active;
    const char* Path;
};

class HiScore : public FrontendSetting
{
private:
    const char* Active;
    const char* Y;
    const char* Delay;
};

#endif // FRONTENDSETTING_H