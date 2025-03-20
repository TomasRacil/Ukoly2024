
#include "carnivore.h"
Carnivore::Carnivore(int x, int y) : Animal(x,y,100, "Carnivore"){}


void Carnivore::info()const{
    std::string sexSymbol;
    if(female){
        sexSymbol = "\u2640";
    }else{
        sexSymbol = "\u2642";
    }
    std::cout << sexSymbol << " " <<  std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}

void Carnivore::metabolize(){ hp -= 4; }


void Carnivore::consume() {}


std::shared_ptr<Entity> Carnivore::reproduce(const std::array<int,2>& emptyPosition){

    // return std::make_shared<Herbivore>(emptyPosition[0], emptyPosition[1], hp, type);
    return std::make_shared<Carnivore>(emptyPosition[0], emptyPosition[1]);

}

void Carnivore::hunt(std::list<std::shared_ptr<Herbivore>>& herbivores) {
    for (auto it = herbivores.begin(); it != herbivores.end(); ) {
        const auto& herbivore = *it;
        if (withinArea(herbivore, 5, true)) {
            int posX = herbivore->x;
            int posY = herbivore->y;
            std::cout << "Carnivore found herbivore at (" << posX << ", " << posY << "). Consuming..." << std::endl;
            hp += 80;
            herbivore->hp = 0;
            it = herbivores.erase(it);
            std::cout << "Herbivore removed from the list." << std::endl;
            //moveTo({posX, posY});
            x = posX;
            y = posY;

            std::cout << "Carnivore moved to (" << posX << ", " << posY << ")." << std::endl;
            break;
        } else {
            ++it;
        }
    }
}

