#ifndef HERBIVORE_H
#define HERBIVORE_H

#include "animal.h"
#include "plant.h"

class Herbivore : public Animal {
public:
    Herbivore(int x, int y);
    void lookForFood(std::list<std::shared_ptr<Plant>>& plants);
    virtual void metabolize() override;
    virtual void info() const override;
    virtual void consume() override;
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) override;
};

#endif // HERBIVORE_H
