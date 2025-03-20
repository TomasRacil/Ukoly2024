//entity.cpp
#include "entity.h"
#include "environment.h"

int Entity::globalID = 0;

std::size_t generateHash(int globalID){

    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    std::ostringstream oss;
    oss << millis << globalID;
    std::string combinedString = oss.str();
    std::hash<std::string> hasher;

    return hasher(combinedString);
}

Entity::Entity(int x, int y, int hp, const std::string& type) : x(x), y(y), hp(hp), type(type), id(globalID++){

    
    hashID = generateHash(globalID);
        
    }


// Entity::~Entity() = default;
//Entity::~Entity();


size_t Entity::getHash() const noexcept{
    return hashID;
}


bool Entity::isPositionEmpty(int x, int y, const std::list<std::shared_ptr<Entity>>& entities) const {
    for (const auto& entity : entities) {
        if (entity && entity->x == x && entity->y == y) {
            return false;
        }
    }
    return true;
}







std::array<int, 2> Entity::chooseRandomPosition(const std::list<std::array<int, 2>>& emptyPositions) {
    if (emptyPositions.empty()) {
        throw std::runtime_error("No empty positions available.");
    }
    int randomIndex = std::rand() % emptyPositions.size();
    auto it = emptyPositions.begin();
    std::advance(it, randomIndex);
    return *it;
}



std::list<std::array<int, 2>> Entity::emptyPositionsNearby(const std::shared_ptr<Entity>& entity,
                                                 const std::list<std::shared_ptr<Entity>>& entities, 
                                                 int distance, bool radial) const {

    std::list<std::array<int, 2>> validPositions;

    if (!entity) return validPositions;

    int posX = entity->x;
    int posY = entity->y;


    if (!radial) {
            
        for (int i = -distance; i <= distance; ++i) {
            for (int j = -distance; j <= distance; ++j) {
                int newX = posX + i;
                int newY = posY + j;

                if (isPositionEmpty(newX, newY, entities)) {
                    validPositions.push_back({newX, newY});
                }
            }
        }
    } else {
            // Iterate over a circular region
        for (int i = -distance; i <= distance; ++i) {
            for (int j = -distance; j <= distance; ++j) {
                int newX = posX + i;
                int newY = posY + j;

                    // Check radial distance
                if (sqrt(i * i + j * j) <= distance && isPositionEmpty(newX, newY, entities)) {
                    validPositions.push_back({newX, newY});
                }
            }
        }
    }

    return validPositions;
}


std::list<std::array<int, 2>> Entity::emptyPositionsNearby(const std::list<std::shared_ptr<Entity>>& entities, 
                                                 int distance, bool radial) const{

    std::list<std::array<int, 2>> validPositions;


    int posX = x;
    int posY = y;


    if (!radial) {
            
        for (int i = -distance; i <= distance; ++i) {
            for (int j = -distance; j <= distance; ++j) {
                int newX = posX + i;
                int newY = posY + j;

                if (isPositionEmpty(newX, newY, entities)) {
                    validPositions.push_back({newX, newY});
                }
            }
        }
    } else {
            // Iterate over a circular region
        for (int i = -distance; i <= distance; ++i) {
            for (int j = -distance; j <= distance; ++j) {
                int newX = posX + i;
                int newY = posY + j;

                    // Check radial distance
                if (sqrt(i * i + j * j) <= distance && isPositionEmpty(newX, newY, entities)) {
                    validPositions.push_back({newX, newY});
                }
            }
        }
    }

    return validPositions;
}








std::array<int,2> Entity::getPosition() const noexcept{

    return {x,y};

}




bool Entity::withinArea(const std::shared_ptr<Entity>& entity, int distance, bool radial) const{

    if (!entity) return false;


    int posX = entity->x;
    int posY = entity->y;

    if (!radial) {
        return x >= posX - distance && x <= posX + distance &&
               y >= posY - distance && y <= posY + distance;
    }


    return sqrt((x - posX) * (x - posX) + (y - posY) * (y - posY)) <= distance;
}



bool Entity::withinArea(const std::array<int,2>& position, int distance, bool radial)const{

    if(position[0] == x && position[1] == y) return true;

    if(!radial){

        return x >= position[0] - distance && x <= position[0] + distance  && y >= position[1] - distance && y <= position[1] + distance;

    }

    return sqrt((x-position[0]) * (x-position[0]) + (y-position[1]) * (y-position[1])) <= distance; 
                   
}


void Entity::info()const{
    std::cout << "  " << std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}


