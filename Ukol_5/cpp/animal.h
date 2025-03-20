#ifndef ANIMAL_H
#define ANIMAL_H

#include "organism.h"

class Animal : public Organism {
protected:
    bool female;
    int femaleReproductionCondition;
    int maleReproductionCondition;
public:
    Animal(int x, int y, int hp, const std::string& type);
    virtual void metabolize() override;
    virtual void consume() override;
    virtual void info() const override;
    virtual std::shared_ptr<Entity> reproduce(const std::array<int, 2>& position) override;
    void moveTo(const std::array<int, 2>& finalPosition);
    bool isFemale() const;
};

#endif // ANIMAL_H
