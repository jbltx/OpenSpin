#ifndef MAIN_SETTINGS_H
#define MAIN_SETTINGS_H

class MainSettings
{
public:
	MainSettings();
	~MainSettings();

	const char* getID(const char* key);
	const char* getName(const char* key);

private:
	const char* name;
	const char* id;
};

#endif // MAIN_SETTINGS_H