//
// Created by Yorick on 26/10/2016.
//

#include "Consumable.h"
#include "../Rng.h"
#include "../DM.h"
#include "../actors/Player.h"
#include <set>

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
        case ConsumableType::FOOD:
            DM::say("You set up camp, eat some " + _name + " and get a good night rest.");
            actor->heal(amount);
            break;
        case ConsumableType::HEALING:
            actor->heal(amount);
            return amount;
        case ConsumableType::ILLUMINATION:
            break;
        case ConsumableType::BOMB:
            break;
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
            Room *north = temp->getRoomBehindDoor(Direction::NORTH);
            Room *east = temp->getRoomBehindDoor(Direction::EAST);
            Room *south = temp->getRoomBehindDoor(Direction::SOUTH);
            Room *west = temp->getRoomBehindDoor(Direction::WEST);
            if (north && visited.find(north) == visited.end()) {
                queue.push(north);
                visited[north] = temp;
            }
            if (east && visited.find(east) == visited.end()) {
                queue.push(east);
                visited[east] = temp;
            }
            if (south && visited.find(south) == visited.end()) {
                queue.push(south);
                visited[south] = temp;
            }
            if (west && visited.find(west) == visited.end()) {
                queue.push(west);
                visited[west] = temp;
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
            DM::say("Stairs are " + to_string(distance) + " rooms away.");
        }
    }
}
