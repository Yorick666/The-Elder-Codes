cmake_minimum_required(VERSION 3.3)
project(The_Elder_Codes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++ -std=c++11")

set(SOURCE_FILES main.cpp DM.cpp DM.h Rng.cpp Rng.h enum/GameState.h dungeon/Dungeon.cpp dungeon/Dungeon.h dungeon/Floor.cpp dungeon/Floor.h dungeon/Room.cpp dungeon/Room.h menu/MenuFactory.cpp menu/MenuFactory.h menu/Menu.cpp menu/Menu.h menu/MenuStart.cpp menu/MenuStart.h actors/Actor.cpp actors/Actor.h actors/Player.cpp actors/Player.h Game.cpp Game.h menu/MenuRoam.cpp menu/MenuRoam.h dungeon/Coordinate.cpp dungeon/Coordinate.h enum/RoomType.h enum/Direction.h items/Weapon.cpp items/Weapon.h items/Armor.cpp items/Armor.h enum/Dice.h actors/Monster.cpp actors/Monster.h items/Item.cpp items/Item.h enum/ArmorType.h enum/WeaponType.h DM.cpp DM.h Loader.cpp Loader.h enum/ItemType.h items/Consumable.cpp items/Consumable.h enum/ConsumableType.h menu/MenuFight.cpp menu/MenuFight.h menu/MenuInventory.cpp menu/MenuInventory.h enum/InventoryState.h dungeon/Corridor.cpp dungeon/Corridor.h enum/RoomSize.h enum/RoomCuriosity.h menu/MenuPickup.cpp menu/MenuPickup.h)
add_executable(The_Elder_Codes ${SOURCE_FILES})