# OpenSpin - Open Source Emulators Frontend

OpenSpin is a cross-platform and open source front-end to find and launch your games on emulator. 
It can be built for Windows/OSX/Linux/Android/iOS with arm/i386/amd64 arch.

To more, this front-end is compatible with HyperSpin configuration files/databases/themes.

## Command-Line Interface

You can launch OpenSpin binary in command-line, here's the help section

```
OpenSpin - CLI

--help, -H              Show this help page
--system, -S            Define the system name
--rom, -R               Define the rom name
--args, -A              Define additional args to emulator execution
--noserver, -NS         Disable the app server feature to be able to remotely control OpenSpin

--fullscreen, -fs       Run OpenSpin in fullscreen (default is 1)
--width, -w             Width resolution of the application (default is 1024)
--height, -h            Height resolution of the application (default is 768)
--username, -u          Define user name used to remotely control the app (default is "admin")
--password, -pwd        Define user password (default is "admin")
--port, -p              Define application server port (default is 55670)
```

### API

OpenSpin runs a simple HTTP server which allows you to remotely control the application.
Server responses are given in JSON format.

```
# Payload :
http://SERVER_IP:55670/status
# Response :
{"http": {"code": 200}, "application": {"name": "Open-Source Emulators Frontend", "version": "1.0", ...}, ...} // if the application is currently running a game, this game's metadata will be given here.

# Payload :
http://SERVER_IP:55670/play?game=GAME_NAME&system=SYSTEM_NAME
# Response :
{"http": {"code": 200}, "game": {"name": "GAME_NAME", "version": "GAME_VERSION", ...}, ...} // the response gives all available metadata from the application game database.

# Payload :
http://SERVER_IP:55670/quit
# Response :
{"http": {"code": 200}} // if response is not 200, the application can't quit
```

## Dependencies

### Main

* [libsdl2-dev](https://www.libsdl.org/download-2.0.php)
* cmake
* make

### For toolchain

Just install known dependencies for your toolchain (android-sdk and ndk for Android toolchain, mingw32 for window toolchain, etc...) 

## Build

**NB :** You need to use xCode to build for iOS and OSX.

### Simple steps

```
git clone https://github.com/jbltx/OpenSpin.git
cd OpenSpin
mkdir -p build && cd build
cmake ../
make
sudo make install
```

### Cmake toolchain

```
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/android.cmake ../    # Build Android app for ARM devices
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/win32.cmake ../      # Build Windows Desktop 32bits app
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/win64.cmake ../      # Build Windows Desktop 64bits app
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/lin32.cmake ../      # Build Linux-based 32bits app
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/lin64.cmake ../      # Build Linux-based 64bits app
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/armhf.cmake ../      # Build Linux-based ARM (hard-float) app
```

## License

Open-Source Emulators Frontend is under GNU/GPLv2 license.

## Contributing

OpenSpin uses a Git-flow source control workflow.

1. Fork our develop branch
2. Create a new feature branch
3. Write your code
4. Send a Pull Request on our develop branch

More informations about git-flow [here](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow).
