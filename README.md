# Amnesia: A Machine For Pigs
[![CI](https://github.com/shamazmazum/AmnesiaAMachineForPigs/actions/workflows/build.yml/badge.svg)](https://github.com/shamazmazum/AmnesiaAMachineForPigs/actions/workflows/build.yml)

## Before you play

This port is still WIP. To play the game you will need to modify the files from
the original game following these instructions:

* Download and install [Autodesk FBX converter](https://www.autodesk.com/developer-network/platform-technologies/fbx-converter-archives). 
  You may need to install Windows on some VM for that.
* Convert all `.FBX` models in the game directory to Collada format (file
  extension `.dae`).
* From the top directory where the game assets are invoke the following command:
  `find . -name "*.ent" -print0 | xargs -0 sed -i.bak 's/\.FBX/\.dae/'`.

If you do something wrong you will not see manpigs and children in the beginning
of the game.

## Readme

This is a port of Amnesia: A Machine For Pigs developed by The Chinese Room and
published by Frictional Games to Linux/BSD systems. It's 100% binary blob free
(thanks to buzer2020's port). Only few dependencies are bundled with this fork:

* OALWrapper. It's easier to bundle it because it's specific to Frictional
  Games.
* Newton Dynamics Engine. Finding the sources for this particular version was a
  pain (again, thanks to buzer2020 here on GitHub).
* AngelScript. There is `lang/angelscript` port in FreeBSD ports collection, but
  that version is too new for this game.
  
## Building

Just run

~~~~
mkdir build && cd build
cmake ../Game/src
make
~~~~

or, alternatively, if you want your game assets installed system-wide:

~~~~
mkdir build && cd build
cmake -DSYSTEMWIDE_RESOURCES=ON -DSYSTEMWIDE_RESOURCES_LOCATION="/path/to/game/assets" ../amnesia/src
make
~~~~

This will produce a single executable, `AmnesiaAMFP` which you need to run to play
the game.

## Dependencies

In addition to those ancient bundled dependencies, the game needs a few newer
ones:

* OpenGL
* SDL2
* libtheora
* libvorbis
* libvorbisfile
* DevIL
* GLEW

All this libraries can be found in FreeBSD ports.

## Additional notes

The original repository has a bunch of additional tools like level and model
editors. Because these tools are not suitable for my Wayland environment and
require X libraries, I do not build them. The sources are still here, however.
