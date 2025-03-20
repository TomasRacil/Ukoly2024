#ifndef ORGANISM_H
#define ORGANISM_H

#include "entity.h"

class Organism : public Entity {
public:
    Organism(int x, int y, int hp, const std::string& type);
    void roam(const std::list<std::shared_ptr<Entity>>& entitiesInArea);
    virtual void metabolize() override;
    virtual void consume() override;
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) override;
    virtual void info() const override;
    bool isAlive() const;
};

#endif // ORGANISM_H
