# OpenSpin - Open Source Emulators Frontend 
![](https://img.shields.io/badge/pre_alpha-v0.1.0-yellow.png) 

OpenSpin is a cross-platform and open source front-end to find and launch your games on emulator. 
It can be built for Windows/OSX/Linux.

To more, this front-end is compatible with HyperSpin configuration files/databases/themes.

## Build status

| [Linux][lin-link] | [Windows][win-link] |
| :---------------: | :-----------------: |
| ![lin-badge]      | ![win-badge]        |

[lin-link]: https://travis-ci.org/jbltx/OpenSpin
[win-link]: https://ci.appveyor.com/project/jbltx/openspin
[lin-badge]: https://travis-ci.org/jbltx/OpenSpin.svg?branch=develop "Travis build status"
[win-badge]: https://ci.appveyor.com/api/projects/status/vfmiudumrc57o8h6?svg=true "AppVeyor build status"

## Command-Line Interface

You can launch OpenSpin binary in command-line, here's the help section

```
OpenSpin - CLI

--help, -h              Show this help page
--version, -v 			Show version
--system, -s            Define the system name
--rom, -r               Define the rom name
--args, -a              Define additional args to emulator execution
--noserver, -ns         Disable the app server feature to be able to remotely control OpenSpin

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

## Build

**NB :** You need to use xCode to build for iOS and OSX.

### Simple steps

```bash
git clone https://github.com/jbltx/OpenSpin.git
cd OpenSpin
mkdir -p build && cd build
cmake ../
make
sudo make install
```

## License

OpenSpin is under GNU/GPLv2 license.

## Contributing

OpenSpin uses a Git-flow source control workflow.

1. Fork our develop branch
2. Create a new feature branch
3. Write your code
4. Send a Pull Request on our develop branch

More informations about git-flow [here](https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow).
