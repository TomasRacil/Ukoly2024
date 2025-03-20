#ifndef CARNIVORE_H
#define CARNIVORE_H

#include "animal.h"
#include "herbivore.h"

class Carnivore : public Animal {
public:
    Carnivore(int x, int y);
    void hunt(std::list<std::shared_ptr<Herbivore>>& herbivores);
    virtual void metabolize() override;
    virtual void consume() override;
    void info() const override;
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) override;
};

#endif // CARNIVORE_H
