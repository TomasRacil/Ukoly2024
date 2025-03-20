
#include "organism.h"

Organism::Organism(int x, int y, int hp, const std::string& type) : Entity(x, y, hp, type){}


void Organism::roam(const std::list<std::shared_ptr<Entity>>& entitiesInArea){

    std::list<std::array<int,2>> emptyPositions = emptyPositionsNearby(entitiesInArea,2,false);
    std::array<int,2> chosenPosition = chooseRandomPosition(emptyPositions);
    x = chosenPosition[0];
    y = chosenPosition[1];
    
}


void Organism::info()const{
    std::cout << "  "<<  std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}


void Organism::metabolize(){}


void Organism::consume(){}


bool Organism::isAlive() const { return hp > 0; }


std::shared_ptr<Entity> Organism::reproduce(const std::array<int, 2>& emptyPosition){

    return std::make_shared<Organism>(emptyPosition[0], emptyPosition[1], hp, type);

}

