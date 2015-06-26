#include "Frontend.h"
#include <iostream>


int showHelp()
{
	std::cout << "OpenSpin - OpenSource Emulators Frontend" << std::endl;
	std::cout << "Version 0.1.0" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "--help, -h              Show this help page" << std::endl;
	std::cout << "--version, -v           Show the application version" << std::endl;
	std::cout << "--system, -s            Launch a Game : Define the system name" << std::endl;
	std::cout << "--rom, -r               Launch a Game : Define the rom name" << std::endl;
	std::cout << "--args, -a              Launch a Game : Define additional args to emulator execution" << std::endl;
	std::cout << "--noserver, -ns         Disable the app server feature to be able to remotely control OpenSpin" << std::endl;
	std::cout << " " << std::endl;
	std::cout << "--username, -u          Define user name used to remotely control the app(default is \"admin\")" << std::endl;
	std::cout << "--password, -pwd        Define user password(default is \"admin\")" << std::endl;
	std::cout << "--port, -p              Define application server port(default is 55670);" << std::endl;

	return 0;
}

int showVersion()
{
	std::cout << "OpenSpin - OpenSource Emulators Frontend" << std::endl;
	std::cout << "Version 0.1.0" << std::endl;

	return 0;
}

int launchGame(const char * systemName, const char * romName, const char * args)
{
	return 0;
}


int main(int argc, char * argv[])
{
	char * systemArg	= "";
	char * romArg		= "";
	char * argsArgs		= "";
	char * usernameArg	= "admin";
	char * pwdArg		= "admin";
	int  portArg        = 55965;
	bool noServerArg	= false;

	for (int i = 0; i < argc; i++)
	{
		if (argv[i] == "-h"   || argv[i] == "--help") 
			return showHelp();

		if (argv[i] == "-v"   || argv[i] == "--version")
			return showVersion();

		if (argv[i] == "-s"   || argv[i] == "--system")
			systemArg = argv[i + 1];

		if (argv[i] == "-r"   || argv[i] == "--rom")
			romArg = argv[i + 1];

		if (argv[i] == "-a"   || argv[i] == "--args")
			argsArgs = argv[i + 1];

		if (argv[i] == "-ns"  || argv[i] == "--noserver")
			noServerArg = true;

		if (argv[i] == "-u"   || argv[i] == "--username")
			usernameArg = argv[i + 1];

		if (argv[i] == "-pwd" || argv[i] == "--password")
			pwdArg = argv[i + 1];

		if (argv[i] == "-p"   || argv[i] == "--port")
			portArg = atoi(argv[i + 1]);

		if ((unsigned)strlen(systemArg) > 1 || (unsigned)strlen(romArg) > 1 || (unsigned)strlen(argsArgs) > 1)
		{
			if ((unsigned)strlen(systemArg) > 1 && (unsigned)strlen(romArg) > 1 && (unsigned)strlen(argsArgs) > 1)
			{
				return launchGame(systemArg, romArg, argsArgs);
			}
			else
			{
				std::cout << "Please provide all arguments to launch a game" << std::endl;
				return -1;
			}
		}

	}

	Frontend frontend;
	return frontend.exec(noServerArg, usernameArg, pwdArg, portArg);
}


