#ifndef PLANT_H
#define PLANT_H

#include "organism.h"

class Plant : public Organism {
public:
    Plant(int x, int y);
    virtual void info() const override;
    virtual void metabolize() override;
    virtual void consume() override;
    virtual void roam(const std::list<std::shared_ptr<Entity>>& entitiesInArea);
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) override;
    std::shared_ptr<Plant> makeSeedlings();
};

#endif // PLANT_H
