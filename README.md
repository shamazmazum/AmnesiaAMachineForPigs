Amnesia: A Machine For Pigs
=======================

## Disclaimer

This is still WIP. The game is not playable to the end (just to the centrifuge
room).

## Readme

This is a port of Amnesia: A Machine For Pigs by Frictional Games to Linux/BSD
systems. It's 100% binary blob free (thanks to buzer2020's port). Only few
dependencies are bundled with this fork:

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
cmake ../amnesia/src
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
