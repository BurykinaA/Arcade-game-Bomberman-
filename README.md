# Course work
## _Arcade game “Bomberman”_


This game is designed for one player and is made in the arcade genre. The player controls a character located on a randomly generated game location consisting of two types of blocks: destructible boxes and indestructible walls. The character itself is in the upper left corner of the map, can move on the grass. He can bet with a small gap during time bombs that explode after a fixed time and destroy boxes next to them. Thanks to the bombs, the player clears his way, as well as kills opponents (monsters). The character himself also takes damage if hit by the bomb. To pass to the next level you need to get to five   opponents and destroy them with the help of bombs that the player places on the level. The player receives one kill point. For each enemy destroyed by the character. The character has only 3 health points, which disappear if he falls into the zone of the explosion of the bomb left by him or stumbles upon the enemy. If all health points are lost, the player loses and the game restarts with first level. This will also reset the kill counter.


## Technical description

- main.cpp - this is where the program starts, calls the menu, opens
and closing the window.
- Map.h and Map.cpp - header and implementation of the map, random
game field generation.
- Player.h and Player.cpp - header and implementation of the player, it is described
traffic.
- BoxCollider.h and BoxCollider.cpp – collider header and implementation,
which checks that the objects cannot intersect.
- bomb.h and Bomb.cpp - header and implementation of the bomb class, an array of bombs.
- Monster.h and Monster.ccp - header and implementation of monsters, their description
movement, their intersection with surrounding objects.
- Spawner.h and Spawner.cpp - header and implementation of random generation
monsters.
- HealthBar.h and HealthBar.cpp - header and implementation of the updated
panel showing the three lives that can be lost,
blown up by a bomb or faced with a monster. If this
happened, the player will be returned to the starting point.
- KillBar.h and KillBar.cpp - header and implementation of the updated bar,
showing the number of killed mobs, resets to zero after death
player.
- LevelBar.h and LevelBar.cpp - header and implementation of the updated bar,
showing the number of levels completed. Resets after
player death


## Installation

Download SFML 2.5.1: https://www.sfml dev.org/download/sfml/2.5.1/

In order to use this application, you must download the svn repository from the link [1] and build the project using CMake. AT You can find the configuration file Doxyfile for doxygen in the sources. With his using it is possible to get the documentation of the Map class. At the same time, in folder where the project was built, when building docs, the html folder will appear, where documentation is located. After you need to set the path CMAKE_INSTALL_PREFIX, where later all the necessary files will be installed, and being in the folder with the assembled project, type cmake --build on the command line. --target install, after which to the specified CMAKE_INSTALL_PREFIX path, three folders will be created: lib - contains library files with extensions .h and .cpp; bin - contains the application BomberMan.exe and the necessary SFML library files to run

Or you can download the archive and play :)
