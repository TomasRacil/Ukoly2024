#include "herbivore.h"



//Herbivore::Herbivore(int x, int y, int hp, const std::string type) : Animal(x,y,hp, "Herbivore"){}
Herbivore::Herbivore(int x, int y) : Animal(x,y,50, "Herbivore"){}


void Herbivore::info()const{
    std::string sexSymbol;
    if(female){
        sexSymbol = "\u2640";
    }else{
        sexSymbol = "\u2642";
    }
    std::cout << sexSymbol << " " <<  std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}

void Herbivore::metabolize(){ hp -= 2; }


void Herbivore::consume() {}


std::shared_ptr<Entity> Herbivore::reproduce(const std::array<int,2>& emptyPosition){

    // return std::make_shared<Herbivore>(emptyPosition[0], emptyPosition[1], hp, type);
    return std::make_shared<Herbivore>(emptyPosition[0], emptyPosition[1]);

}





void Herbivore::lookForFood(std::list<std::shared_ptr<Plant>>& plants) {
    for (auto it = plants.begin(); it != plants.end(); ) {
        const auto& plant = *it;
        if (withinArea(plant, 2, true)) {
            int posX = plant->x;
            int posY = plant->y;
            std::cout << "Herbivore found plant at (" << posX << ", " << posY << "). Consuming..." << std::endl;
            hp += 40;
            plant->hp = 0;
            it = plants.erase(it);
            std::cout << "Plant removed from the list." << std::endl;
            //moveTo({posX, posY});
            x = posX;
            y = posY;

            std::cout << "Herbivore moved to (" << posX << ", " << posY << ")." << std::endl;
            break;
        } else {
            ++it;
        }
    }
}