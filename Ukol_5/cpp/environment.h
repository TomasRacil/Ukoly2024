//environment.h
#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <list>
#include <memory>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <map>
#include "entity.h"
#include "organism.h"
#include "plant.h"
#include "animal.h"
#include "herbivore.h"
#include "carnivore.h"

class Environment{
    
private:

    int width;
    int height;

public:
    std::list<std::shared_ptr<Entity>> world;
    Environment(int width, int height);
    ~Environment();

template <typename T>
std::list<std::shared_ptr<T>> makeEntityList() {
    std::list<std::shared_ptr<T>> listOfChosenEntity;
    for (const auto& entity : world) {
        if (auto castedEntity = std::dynamic_pointer_cast<T>(entity)) {
            listOfChosenEntity.push_back(castedEntity);
        }
    }
    return listOfChosenEntity;
}

template <typename EntityType>
void populateEntities(std::list<std::shared_ptr<Entity>>& world,
                      int entityShare,
                      int width,
                      int height,
                      std::list<std::array<int, 2>>& initialEmptyPositions,
                      const std::function<std::shared_ptr<EntityType>(int, int)>& createEntity) {
    for (int j = 0; j < entityShare; j++) {
        bool placed = false;
        while (!placed) {

            int rngPosX = rand() % width;
            int rngPosY = rand() % height;


            auto posIt = std::find_if(initialEmptyPositions.begin(), initialEmptyPositions.end(),
                                      [rngPosX, rngPosY](const std::array<int, 2>& pos) {
                                          return pos[0] == rngPosX && pos[1] == rngPosY;
                                      });


            if (posIt != initialEmptyPositions.end()) {
                auto entity = createEntity(rngPosX, rngPosY);
                world.push_back(entity);
                initialEmptyPositions.erase(posIt);
                placed = true;
            }
        }
    }
}

void resolveCollisions();

void removeDeadOrganisms();

void addEntity(const std::shared_ptr<Entity>& ent);

void populate(int entityLeverage);

bool removeEntityByHash(size_t hashID);

void infoEntities() const;

std::list<std::shared_ptr<Entity>> listEntitiesInArea(int x, int y, int distance, bool radial);

    void simulate();

};



#endif
