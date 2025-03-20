//environment.cpp
#include <thread>
#include <chrono>
#include <random>
#include "environment.h"

Environment::Environment(int width, int height) : width(width), height(height){}
Environment::~Environment() = default;

void Environment::addEntity(const std::shared_ptr<Entity>& ent){

    world.push_back(ent);

}

void Environment::populate(int entitiesLeverage) {
    int plantShare = 4;     
    int herbivoreShare = 1;  
    int carnivoreShare = 1;   
    std::list<std::array<int, 2>> initialEmptyPositions;


    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            initialEmptyPositions.push_back({i, j});
        }
    }

    for (int i = 0; i < entitiesLeverage; i++) {

        populateEntities<Herbivore>(
            world, herbivoreShare, width, height, initialEmptyPositions,
            [](int x, int y) {
                return std::make_shared<Herbivore>(x, y);
            });


        populateEntities<Carnivore>(
            world, carnivoreShare, width, height, initialEmptyPositions,
            [](int x, int y) {
                return std::make_shared<Carnivore>(x, y);
            });


        populateEntities<Plant>(
            world, plantShare, width, height, initialEmptyPositions,
            [](int x, int y) {
                return std::make_shared<Plant>(x, y);
            });
    }
}

void Environment::resolveCollisions() {
    std::map<std::array<int, 2>, std::list<std::shared_ptr<Entity>>> positionMap;

    // Group entities by position
    for (const auto& entity : world) {
        positionMap[entity->getPosition()].push_back(entity);
    }

    // Keep track of entities to remove
    std::list<std::shared_ptr<Entity>> entitiesToRemove;

    for (auto& [position, entitiesAtPosition] : positionMap) {
        if (entitiesAtPosition.size() > 1) {
            std::list<std::shared_ptr<Entity>> remainingEntities;

            for (auto it = entitiesAtPosition.begin(); it != entitiesAtPosition.end(); ++it) {
                auto currentEntity = *it;
                bool resolved = false;

                for (auto innerIt = std::next(it); innerIt != entitiesAtPosition.end(); ++innerIt) {
                    auto otherEntity = *innerIt;

                    // Herbivore eats plant
                    if (auto herbivore = std::dynamic_pointer_cast<Herbivore>(currentEntity)) {
                        if (auto plant = std::dynamic_pointer_cast<Plant>(otherEntity)) {
                            herbivore->consume();
                            plant->hp = 0;
                            resolved = true;
                            entitiesToRemove.push_back(plant);
                        }
                    } else if (auto herbivore = std::dynamic_pointer_cast<Herbivore>(otherEntity)) {
                        if (auto plant = std::dynamic_pointer_cast<Plant>(currentEntity)) {
                            herbivore->consume();
                            plant->hp = 0;
                            resolved = true;
                            entitiesToRemove.push_back(plant);
                        }
                    }

                    // More interaction rules can be added here...
                }

                if (!resolved) {
                    remainingEntities.push_back(currentEntity);
                }
            }

            positionMap[position] = remainingEntities;
        }
    }

    // **Remove dead entities AFTER iteration**
    for (auto& entity : entitiesToRemove) {
        world.remove(entity);
    }
}





bool Environment::removeEntityByHash(size_t hashID) {
    auto it = std::find_if(world.begin(), world.end(),
                           [hashID](const std::shared_ptr<Entity>& entity) {
                               return entity->getHash() == hashID;
                           });

    if (it != world.end()) {
        world.erase(it);
        return true;
    }
    return false;
}


std::list<std::shared_ptr<Entity>> Environment::listEntitiesInArea(int x, int y, int distance, bool radial){

    std::list<std::shared_ptr<Entity>> result;

    for(auto& ent : world){

        int posX = ent->x;
        int posY = ent->y;

        if(!radial){
        
            if(x >= posX - distance && x <= posX + distance  && y >= posY - distance && y <= posY + distance){

                result.push_back(ent);

            }

        }else{

            if(sqrt( (posX-x)*(posX-x)+(posY-y)*(posY-y)) <= distance){

                result.push_back(ent);

            }

        }

    }

    return result;     

}


void Environment::removeDeadOrganisms() {
    world.remove_if([](const std::shared_ptr<Entity>& ent) {
        return ent->hp <= 0;
    });
}

void Environment::simulate() {
    std::cout << "Select number of steps: ";
    int steps;
    std::cin >> steps;
    // std::cout << "Steps hardcoded on 30" << std::endl;
    // int steps = 30;

    for (int i = 0; i < steps; i++) {
        std::list<std::shared_ptr<Animal>> animals;
        std::list<std::shared_ptr<Plant>> plants = makeEntityList<Plant>();
        std::list<std::shared_ptr<Herbivore>> herbivores;

        // 🦌 Sort animals
        for (auto& ent : world) {
            if (auto animal = std::dynamic_pointer_cast<Animal>(ent)) {
                animals.push_back(animal);

            }
        }

        // 🌱 Process plants (gain energy, metabolize & reproduce)
        for (auto& plant : plants) {
            plant->consume();  // 🔋 Gain energy over time
            plant->metabolize();  // ⚡ Plants also consume energy over time
            std::random_device rd;  // Seed
            std::mt19937 gen(rd()); // Mersenne Twister PRNG
            std::uniform_int_distribution<int> dist(-1, 1); // Generates -1, 0, or 1

            if (plant->hp >= 20) {  // 🌿 Reproduce threshold
                int newX = plant->x + dist(gen);  // Small offset
                int newY = plant->y + dist(gen);
            
                // Ensure position is valid and not already occupied
                bool isSpotEmpty = std::none_of(world.begin(), world.end(), [&](const std::shared_ptr<Entity>& ent) {
                    return ent->x == newX && ent->y == newY && std::dynamic_pointer_cast<Plant>(ent);
                });
            
                if (isSpotEmpty && newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    auto newPlant = std::make_shared<Plant>(newX, newY);
                    world.push_back(newPlant);
                    plant->hp /= 2;  // ⚡ Split energy on reproduction
                }
            }
        }

        // 🦌 Herbivores search for food, metabolize & reproduce
        for (auto& animal : animals) {
            if (auto herbivore = std::dynamic_pointer_cast<Herbivore>(animal)) {
                std::random_device rd;  // Seed
                std::mt19937 gen(rd()); // Mersenne Twister PRNG
                std::uniform_int_distribution<int> dist(-1, 1); // 
                herbivore->metabolize();  // 🦌 Lose energy over time
                herbivore->lookForFood(plants);

                // 🌱 If enough energy, attempt reproduction
                if (herbivore->hp >= 120) {
                    int newX = herbivore->x + dist(gen);  // Small offset
                    int newY = herbivore->y + dist(gen);

                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                        auto newHerbivore = std::make_shared<Herbivore>(newX, newY);
                        world.push_back(newHerbivore);
                        herbivore->hp -=60;
                    }
                }
            }

        }
        for (auto& animal : animals) {
            if (auto herbivore = std::dynamic_pointer_cast<Herbivore>(animal)) {
                herbivores.push_back(herbivore);
                
            }
        }

        for (auto& animal : animals) {
            if (auto carnivore = std::dynamic_pointer_cast<Carnivore>(animal)) {
                std::random_device rd;  // Seed
                std::mt19937 gen(rd()); // Mersenne Twister PRNG
                std::uniform_int_distribution<int> dist(-1, 1); // 
                carnivore->metabolize();  // 🦌 Lose energy over time
                carnivore->hunt(herbivores);

                // 🌱 If enough energy, attempt reproduction
                if (carnivore->hp >= 180) {
                    int newX = carnivore->x + dist(gen);  // Small offset
                    int newY = carnivore->y + dist(gen);

                    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                        auto newCarnivore = std::make_shared<Carnivore>(newX, newY);
                        world.push_back(newCarnivore);
                        carnivore->hp -=90;  // 🦌 Split energy with offspring
                    }
                }
            }

        }

        removeDeadOrganisms();
        std::cout << "Entities after step " << i + 1 << std::endl;
        infoEntities();

        // ✅ Initialize counts properly before counting
        int h = 0, c = 0, p = 0;
        for (auto& ent : world) {
            if (std::dynamic_pointer_cast<Herbivore>(ent)) {
                h++;
            } else if (std::dynamic_pointer_cast<Plant>(ent)) {
                p++;
            } else if (std::dynamic_pointer_cast<Carnivore>(ent)) {
                c++;
            }
            
        }

        std::cout << "There are " << h << " herbivores, " << c <<" carnivores and " << p << " plants now.\n";
    }
}




void Environment::infoEntities() const{
    for(const auto& ent : world){
        ent->info();
    }
}