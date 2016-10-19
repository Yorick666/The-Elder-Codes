cmake_minimum_required(VERSION 3.3)
project(The_Elder_Codes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp DM.cpp DM.h Rng.cpp Rng.h enum/GameState.h Dungeon.cpp Dungeon.h Floor.cpp Floor.h Room.cpp Room.h MenuFactory.cpp MenuFactory.h Menu.cpp Menu.h MenuStart.cpp MenuStart.h Actor.cpp Actor.h Player.cpp Player.h Game.cpp Game.h MenuRoam.cpp MenuRoam.h Coordinate.cpp Coordinate.h enum/RoomType.h Link.cpp Link.h)
add_executable(The_Elder_Codes ${SOURCE_FILES})