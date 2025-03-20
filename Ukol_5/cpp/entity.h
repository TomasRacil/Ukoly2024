#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include <functional>
#include <cmath>
#include <array>
#include <memory>
#include <vector>
#include <list>
#include <cstdlib> // for rand
#include <algorithm> // for std::find
#include <chrono>
#include <sstream>
#include <iomanip>

class Entity {
private:
    static int globalID;     
    int id;                 
protected:
    size_t hashID;          
    std::string type;       
public:
    int x, y;               
    int hp;                 
    Entity(int x, int y, int hp, const std::string& type);
    virtual ~Entity() = default;
    size_t getHash() const noexcept;
    std::array<int, 2> getPosition() const noexcept;
    std::array<int, 2> chooseRandomPosition(const std::list<std::array<int, 2>>& emptyPositions);
    bool isPositionEmpty(int x, int y, const std::list<std::shared_ptr<Entity>>& entities) const;
    std::list<std::array<int, 2>> emptyPositionsNearby(const std::shared_ptr<Entity>& entity, const std::list<std::shared_ptr<Entity>>& entities, int distance, bool radial) const;
    std::list<std::array<int, 2>> emptyPositionsNearby(const std::list<std::shared_ptr<Entity>>& entities, int distance, bool radial) const;
    virtual void metabolize() = 0;
    virtual void consume() = 0;
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) = 0;
    bool withinArea(const std::shared_ptr<Entity>& entity, int distance, bool radial) const;
    bool withinArea(const std::array<int, 2>& position, int distance, bool radial) const;
    virtual void info() const;
};

#endif // ENTITY_H
