//
// Created by Yorick on 26/10/2016.
//

#include "Consumable.h"
#include "../Rng.h"
#include "../DM.h"
#include "../actors/Player.h"
#include <set>
#include <algorithm>

using namespace std;

Consumable::Consumable(std::string name, int rarity, ConsumableType type, int base, int diceAmount, int diceSize)
        : Item(name, rarity) {
    _itemType = ItemType::CONSUMABLE;
    _type = type;
    _diceAmount = diceAmount;
    _diceSize = diceSize;
    _base = base;
}

int Consumable::use(Actor *actor) const {
    DM::say(actor->getName() + " used a(n) " + _name + ".");

    int amount = _base;
    amount += Rng::roleDice(_diceSize, _diceAmount);

    switch (_type) {
        case ConsumableType::FOOD: {
            DM::say("You set up camp, eat some " + _name + " and get a good night rest.");
            actor->heal(amount);
            break;
        }
        case ConsumableType::HEALING: {
            actor->heal(amount);
            return amount;
        }
        case ConsumableType::ILLUMINATION:
            break;
        case ConsumableType::BOMB: {
            DM::say("To use bombs you need another function");
            break;
        }
        case ConsumableType::TALISMAN: {
            Player *player = (Player *) actor;
            BFS(player->getCurrentRoom());
            break;
        }
        case ConsumableType::COMPASS:
            break;
    }

    return 0;
}

void Consumable::BFS(Room *startingRoom) const {
    Room *temp;
    queue<Room *> queue;
    map<Room *, Room *> visited;

    queue.push(startingRoom);
    visited[startingRoom] = startingRoom;

    while (!queue.empty()) {
        temp = queue.front();
        queue.pop();
//        DM::say("visiting room on <" + to_string(temp->getCoordinate()->x) + "," +
//                to_string(temp->getCoordinate()->y) + ">");
        if (temp->getRoomType() != RoomType::NORMAL) {
            break;
        } else {
            Corridor *c = temp->getCorridorBehindDoor(Direction::NORTH);
            if (c && !c->isCollapsed()) {
                Room *r = temp->getRoomBehindDoor(Direction::NORTH);
                if (visited.find(r) == visited.end()) {
                    queue.push(r);
                    visited[r] = temp;
                }
            }
            c = temp->getCorridorBehindDoor(Direction::EAST);
            if (c && !c->isCollapsed()) {
                Room *r = temp->getRoomBehindDoor(Direction::EAST);
                if (visited.find(r) == visited.end()) {
                    queue.push(r);
                    visited[r] = temp;
                }
            }
            c = temp->getCorridorBehindDoor(Direction::SOUTH);
            if (c && !c->isCollapsed()) {
                Room *r = temp->getRoomBehindDoor(Direction::SOUTH);
                if (visited.find(r) == visited.end()) {
                    queue.push(r);
                    visited[r] = temp;
                }
            }
            c = temp->getCorridorBehindDoor(Direction::WEST);
            if (c && !c->isCollapsed()) {
                Room *r = temp->getRoomBehindDoor(Direction::WEST);
                if (visited.find(r) == visited.end()) {
                    queue.push(r);
                    visited[r] = temp;
                }
            }
        }
    }

    bool found = false;
    int distance = 0;
    while (!found) {
        temp = visited[temp];
        distance++;
        if (visited[temp] == temp) {
            found = true;
            if (distance <= _base) {
                DM::say("Stairs are " + to_string(distance) + " rooms away.");
            } else {
                DM::say("Stairs are too far away.");
            }
        }
    }
}

bool Consumable::explode(Floor *currentFloor, Room *startingRoom) {
    vector<Corridor *> edges;
    vector<Room *> forest;
    vector<Corridor *> mst;

    for (Corridor *corridor : currentFloor->getCorridors()) {
        if (!corridor->isCollapsed()) {
            edges.push_back(corridor);
        }
    }

    for (Corridor *corridor : edges) {
        if (!corridor->isCollapsed()) {
            Room *first = corridor->getFirstRoom();
            Room *second = corridor->getSecondRoom();

            if (find(forest.begin(), forest.end(), first) == forest.end() ||
                find(forest.begin(), forest.end(), second) == forest.end()) {
                mst.push_back(corridor);
                if (find(forest.begin(), forest.end(), first) == forest.end()) {
                    forest.push_back(first);
                }
                if (find(forest.begin(), forest.end(), second) == forest.end()) {
                    forest.push_back(second);
                }
            }
        }
    }

    int passagesToCollapse = _base;
    int collapsedPassages = 0;

    if (edges.size() - mst.size() >= passagesToCollapse) {
        forest.clear();
        queue<Room *> queue;
        passagesToCollapse = Rng::roleDice(_diceSize, _diceAmount) + _base;

        queue.push(startingRoom);

        while (!queue.empty()) {
            Room *currentRoom = queue.front();
            queue.pop();

            bool done = false;

            while (!done) {
                if (collapsedPassages >= passagesToCollapse) {
                    break;
                }
                vector<Direction> possibleDirectionsToBlow;
                vector<Direction> possibleDirectionsToGo;

                for (int i = 0; i < 4; ++i) {
                    Direction dir;
                    switch (i) {
                        case 1: {
                            dir = Direction::NORTH;
                            break;
                        }
                        case 2: {
                            dir = Direction::EAST;
                            break;
                        }
                        case 3: {
                            dir = Direction::SOUTH;
                            break;
                        }
                        default: {
                            dir = Direction::WEST;
                            break;
                        }
                    }

                    Corridor *temp = currentRoom->getCorridorBehindDoor(dir);
                    if (temp && !temp->isCollapsed()) {
                        if (find(mst.begin(), mst.end(), temp) == mst.end()) {
                            possibleDirectionsToBlow.push_back(dir);
                        } else {
                            Room *tempRoom = currentRoom->getRoomBehindDoor(dir);
                            if (find(forest.begin(), forest.end(), tempRoom) == forest.end()) {
                                possibleDirectionsToGo.push_back(dir);
                            }
                        }
                    }
                }
                if (!possibleDirectionsToBlow.empty()) {
                    int rand = Rng::roleDice(possibleDirectionsToBlow.size()) - 1;
                    currentRoom->getCorridorBehindDoor(possibleDirectionsToBlow[rand])->collapse();
                    collapsedPassages++;
                } else if (!possibleDirectionsToGo.empty()) {
                    int rand = Rng::roleDice(possibleDirectionsToGo.size()) - 1;
                    queue.push(currentRoom->getRoomBehindDoor(possibleDirectionsToGo[rand]));
                    forest.push_back(currentRoom->getRoomBehindDoor(possibleDirectionsToGo[rand]));
                } else {
                    done = true;
                }
            }
        }
        DM::say("That sounded like " + to_string(collapsedPassages) + " passages caving in.... (I counted)");
        DM::say("Evaporated  " + to_string(startingRoom->getMonsters()->size()) + " monster(s) with that " + _name);
        startingRoom->clearRoom();
        return true;
    }
    return false;
}
