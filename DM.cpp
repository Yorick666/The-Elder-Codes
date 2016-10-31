//
// Created by Yorick on 24/10/2016.
//

#include <iostream>
#include "DM.h"

using namespace std;

DM *DM::_instance = nullptr;

void DM::showMap(Floor *currentFloor, Room *currentRoom, bool debug, int securityLevel, bool minimap) {

    int dMaxX = currentFloor->getMaxX() + 1;
    int dMinX = currentFloor->getMinX() - 1;
    int dMaxY = currentFloor->getMaxY() + 1;
    int dMinY = currentFloor->getMinY() - 1;
    int width = (currentFloor->getMaxX() - currentFloor->getMinX() + 3);

    Coordinate *currentCoordinate = currentRoom->getCoordinate();

    if (minimap) {
        dMaxX = currentCoordinate->x + 2;
        dMinX = currentCoordinate->x - 2;
        dMaxY = currentCoordinate->y + 2;
        dMinY = currentCoordinate->y - 2;
        width = 5;
    }

    string topBorder = "";
    string botBorder = "";
    for (int i = 0; i < (width * 5) + 2; ++i) {
        topBorder += char(220);
        botBorder += char(223);
    }

    DM::say(topBorder, minimap);

    for (int y = dMinY; y <= dMaxY; ++y) {
        string top = "";
        string mid = "";
        string bot = "";

        top += char(219);
        mid += char(219);
        bot += char(219);
        for (int x = dMinX; x <= dMaxX; ++x) {
            Room *currentDrawingRoom = currentFloor->getRoom(x, y);
            if (x < 0 || y < 0 || currentDrawingRoom == nullptr) {
                top += "     ";
                mid += "     ";
                bot += "     ";
            } else {
                if (!currentDrawingRoom->visited() && !debug &&
                    (currentDrawingRoom->getRoomBehindDoor(Direction::NORTH) &&
                     currentDrawingRoom->getRoomBehindDoor(Direction::NORTH)->visited() ||
                     currentDrawingRoom->getRoomBehindDoor(Direction::EAST) &&
                     currentDrawingRoom->getRoomBehindDoor(Direction::EAST)->visited() ||
                     currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH) &&
                     currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH)->visited() ||
                     currentDrawingRoom->getRoomBehindDoor(Direction::WEST) &&
                     currentDrawingRoom->getRoomBehindDoor(Direction::WEST)->visited())) {
                    top += "  ";
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::NORTH) &&
                        currentDrawingRoom->getRoomBehindDoor(Direction::NORTH)->visited()) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::NORTH)->isCollapsed()) {
                            top += char(177);
                        } else {
                            top += char(179);
                        }
                    } else {
                        top += " ";
                    }
                    top += "  ";

                    if (currentDrawingRoom->getRoomBehindDoor(Direction::WEST) &&
                        currentDrawingRoom->getRoomBehindDoor(Direction::WEST)->visited()) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::WEST)->isCollapsed()) {
                            mid += char(177);
                            mid += char(177);
                        } else {
                            mid += char(196);
                            mid += char(196);
                        }
                    } else {
                        mid += "  ";
                    }
                    mid += to_string(currentDrawingRoom->getSecurityLevel());
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::EAST) &&
                        currentDrawingRoom->getRoomBehindDoor(Direction::EAST)->visited()) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::EAST)->isCollapsed()) {
                            mid += char(177);
                            mid += char(177);
                        } else {
                            mid += char(196);
                            mid += char(196);
                        }
                    } else {
                        mid += "  ";
                    }

                    bot += "  ";
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH) &&
                        currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH)->visited()) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::SOUTH)->isCollapsed()) {
                            bot += char(177);
                        } else {
                            bot += char(179);
                        }
                    } else {
                        bot += " ";
                    }
                    bot += "  ";
                } else if (!currentDrawingRoom->visited() && !debug) {
                    top += "     ";
                    mid += "     ";
                    bot += "     ";
                } else {
                    if (currentDrawingRoom->getRoomBehindDoor(Direction::NORTH)) {
                        top += char(218);
                        top += char(196);
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::NORTH)->isCollapsed()) {
                            top += char(177);
                        } else {
                            top += char(193);
                        }
                        top += char(196);
                        top += char(191);
                    } else {
                        top += char(218);
                        top += char(196);
                        top += char(196);
                        top += char(196);
                        top += char(191);
                    }

                    if (currentDrawingRoom->getRoomBehindDoor(Direction::WEST)) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::WEST)->isCollapsed()) {
                            mid += char(177);
                        } else {
                            mid += char(180);
                        }
                    } else {
                        mid += char(179);
                    }

                    if (currentDrawingRoom->getRoomBehindDoor(Direction::SOUTH)) {
                        bot += char(192);
                        bot += char(196);
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::SOUTH)->isCollapsed()) {
                            bot += char(177);
                        } else {
                            bot += char(194);
                        }
                        bot += char(196);
                        bot += char(217);
                    } else {
                        bot += char(192);
                        bot += char(196);
                        bot += char(196);
                        bot += char(196);
                        bot += char(217);
                    }

                    if (currentDrawingRoom->getCoordinate()->x == currentCoordinate->x &&
                        currentDrawingRoom->getCoordinate()->y == currentCoordinate->y) {
                        mid += " @ ";
                    } else if (currentDrawingRoom->getRoomType() == RoomType::NORMAL) {
                        mid += " " + to_string(currentDrawingRoom->getSecurityLevel()) + " ";
//                        mid += to_string(x) + to_string(currentDrawingRoom->getSecurityLevel()) + to_string(y);
                    } else if (currentDrawingRoom->getRoomType() == RoomType::UPGRADE) {
                        if (currentDrawingRoom->getSecurityLevel() < securityLevel) {
                            mid += " " + to_string(currentDrawingRoom->getSecurityLevel()) + " ";
                        } else {
                            mid += "^" + to_string(currentDrawingRoom->getSecurityLevel()) + "^";
                        }
                    } else if (currentDrawingRoom->getRoomType() == RoomType::DOWN) {
                        mid += "\\-/";
                    } else if (currentDrawingRoom->getRoomType() == RoomType::UP) {
                        mid += "/-\\";
                    } else if (currentDrawingRoom->getRoomType() == RoomType::EXIT) {
                        mid += "[=]";
                    } else {
                        mid += "???";
                    }

                    if (currentDrawingRoom->getRoomBehindDoor(Direction::EAST)) {
                        if (currentDrawingRoom->getCorridorBehindDoor(Direction::EAST)->isCollapsed()) {
                            mid += char(177);
                        } else {
                            mid += char(195);
                        }
                    } else {
                        mid += char(179);
                    }
                }
            }
        }
        top += char(219);
        mid += char(219);
        bot += char(219);

        DM::say(top + "\n" + mid + "\n" + bot, minimap);
    }
    DM::say(botBorder, minimap);
}

void DM::say(std::string saying, bool direct) {
    if (direct) {
        cout << saying << endl;
    } else {
        DM::getInstance()->addLineToQueue(saying);
    }
}

string DM::askInput() {
    string input;
    cin >> input;
    cout << endl;
    return input;
}

DM *DM::getInstance() {
    if (!_instance)
        _instance = new DM();
    return _instance;
}

void DM::showOutput() {
    while (_outputQueue.size() > 0) {
        cout << _outputQueue.front() << endl;
        _outputQueue.pop();
    }
}

void DM::addLineToQueue(std::string line) {
    _outputQueue.push(line);
}

void DM::describeRoom(Room *room) {
    string description = "\n";
    switch (room->getRoomSize()) {
        case RoomSize::SMALL:
            description += "You see a very small room. ";
            break;
        case RoomSize::MEDIUM:
            description += "You see a seemingly normal room. Don't worry, everyone gets it wrong sometimes.\n";
            break;
        case RoomSize::LARGE:
            description += "Describing this room as large would be an understatement... It's HUGE.\n";
            break;
        case RoomSize::CAVERN:
            description += "You may have left the dungeon, because this room looks more like a cavern.\n";
            break;
    }
    switch (room->getRoomCuriosity()) {
        case RoomCuriosity::CRACK:
            description += "A crack in the ceiling above the middle of the north wall allows a trickle of water to flow down to the floor.\nThe water pools near the base of the wall, and a rivulet runs along the wall an out into the hall.\nThe water smells fresh.";
            break;
        case RoomCuriosity::COBWEBS:
            description += "Thick cobwebs fill the corners of the room, and wisps of webbing hang from the ceiling and waver in a wind you can barely feel.\nOne corner of the ceiling has a particularly large clot of webbing within which a goblin's bones are tangled.";
            break;
        case RoomCuriosity::TAPESTRIES:
            description += "Tapestries decorate the walls of this room. Although they may once have been brilliant in hue,\nthey now hang in graying tatters.\nDespite the damage of time and neglect, you can perceive once-grand images of wizards' towers, magical beasts, and symbols of spellcasting.";
            break;
        case RoomCuriosity::BATS:
            description += "A flurry of bats suddenly flaps through the doorway, their screeching barely audible as they careen past your heads.\nThey flap past you into the rooms and halls beyond.";
            break;
        case RoomCuriosity::SPIKES:
            description += "Rusting spikes line the walls and ceiling of this chamber.The dusty floor shows no sign that the walls move over it,\nbut you can see the skeleton of some humanoid impaled on some wall spikes nearby.";
            break;
        case RoomCuriosity::SKELETON:
            description += "A skeleton dressed in moth-eaten garb lies before a large open chest in the rear of this chamber. The chest is empty,\nbut you note two needles projecting from the now-open lock. Dust coats something sticky on the needles' points.";
            break;
        case RoomCuriosity::MANACLES:
            description += "The manacles set into the walls of this room give you the distinct impression that it was used as a prison and torture chamber,\nalthough you can see no evidence of torture devices.\nOne particularly large set of manacles -- big enough for an ogre -- have been broken open.";
            break;
        case RoomCuriosity::SKULLS:
            description += "You gaze into the room and hundreds of skulls gaze coldly back at you. They're set in niches in the walls in a checkerboard pattern,\neach skull bearing a half-melted candle on its head.\nThe grinning bones stare vacantly into the room, which otherwise seems empty.";
            break;
        case RoomCuriosity::MARBLE:
            description += "Unlike the flagstone common throughout the dungeon, this room is walled and floored with black marble veined with white.\nThe ceiling is similarly marbled, but the thick pillars that hold it up are white";
            break;
        case RoomCuriosity::TOMB:
            description += "Stone sarcophagi stand in five rows of three, each carved with the visage of a warrior lying in state.\nIn their center, one sarcophagus stands taller than the rest. Held up by six squat pillars,\nits stone bears the carving of a beautiful woman who seems more asleep than dead.\nThe carving of the warriors is skillful but seems perfunctory compared to the love a sculptor must have lavished upon the lifelike carving of the woman.";
            break;
        case RoomCuriosity::MOSS:
            description += "A dim bluish light suffuses this chamber, its source obvious at a glance.\nBlue-glowing lichen and violet-glowing moss cling to the ceiling and spread across the floor.\nIt even creeps down and up each wall, as if the colonies on the floor and ceiling are growing to meet each other.\nTheir source seems to be a glowing, narrow crack in the ceiling, the extent of which you cannot gauge from your position.\nThe air in the room smells fresh and damp.";
            break;
    }

    if (room->getRoomType() == RoomType::UPGRADE) {
        description += "\nA statue of the god from the machine is standing in the corner and you can't help admiring this plot device";
    }

    DM::say(description);
}
