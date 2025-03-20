#include "plant.h"




Plant::Plant(int x, int y) : Organism(x,y,15,"Plant"){}


void Plant::metabolize(){ hp-= 1; }


void Plant::info()const{
    std::cout << "  " << std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}

void Plant::consume(){ hp += rand()%3 + 2; }


void Plant::roam(const std::list<std::shared_ptr<Entity>>& entitiesInArea){}


std::shared_ptr<Entity> Plant::reproduce(const std::array<int, 2>& emptyPosition){

    return std::make_shared<Plant>(emptyPosition[0], emptyPosition[1]);

}




std::shared_ptr<Plant> Plant::makeSeedlings(){


    if(hp > 15 ){
        

    }
        return nullptr;

}