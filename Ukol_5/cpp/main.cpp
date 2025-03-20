//main.cpp


#include <iostream>
#include <memory>
#include "entity.h"
#include "organism.h"
#include "plant.h"
#include "animal.h"
#include "herbivore.h"
#include "carnivore.h"
#include "environment.h"

int main() {

    Environment env(50, 50);
    env.populate(5);
    env.infoEntities();
    env.resolveCollisions();
    env.simulate();
    return 0;
}

