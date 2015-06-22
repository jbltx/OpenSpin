#ifndef MAINMENU_SETTING_H
#define MAINMENU_SETTING_H

class MainMenuSetting
{
public:
	MainMenuSetting();
	~MainMenuSetting();

	const char* getID(const char* key);
	const char* getName(const char* key);

private:
	const char* name;
	const char* id;
};

#endif // MAINMENU_SETTING_H