#include "animal.h"

Animal::Animal(int x, int y, int hp, const std::string& type) : Organism(x,y,hp, type){

    female = rand()%2;
    
    if(female){
        femaleReproductionCondition = 120;
    }else{
        maleReproductionCondition = 80;
    }
}


bool Animal::isFemale() const { return female; }


void Animal::metabolize(){ hp -= 2; }


void Animal::consume(){ hp += 5; }


std::shared_ptr<Entity> Animal::reproduce(const std::array<int, 2>& emptyPosition){

    return std::make_shared<Animal>(emptyPosition[0], emptyPosition[1], hp, type);

}


// std::shared_ptr<Entity> Animal::tryToReproduce(const std::list<std::shared_ptr<Animal>>& animalsInArea, const std::list<std::shared_ptr<Entity>>& immovableObjects) {

//     for (const auto& animal : animalsInArea) {

//         if (animal) {

//             if (!isFemale() && hp > maleReproductionCondition && animal->hp > femaleReproductionCondition && animal->isFemale()){

//                 std::list<std::shared_ptr<Entity>> combinedEntitis;
//                 combinedEntitis.insert(combinedEntitis.end(), animalsInArea.begin(), animalsInArea.end());
//                 combinedEntitis.insert(combinedEntitis.end(), immovableObjects.begin(), immovableObjects.end());
//                 std::list<std::array<int,2>> emptyPositions = emptyPositionsNearby(combinedEntitis, 1, false);
//                 if(emptyPositions.size() > 0){
                      
//                     return reproduce(chooseRandomPosition(emptyPositions));
                        
//                     }
//                 }   

//             }
//         }
//     return nullptr;
//     }
    
void Animal::info()const{
std::string sexSymbol;
    if(female){
        sexSymbol = "\u2640";
    }else{
        sexSymbol = "\u2642";
    }
    std::cout << sexSymbol << " " <<  std::setw(15) << std::left << type << "| on X: " << std::setw(5) << std::left << x << " Y: " << std::setw(5) << std::left << y << "| health points: " << std::setw(5) << std::left << hp << "| hash: " << hashID << std::endl;
}


void Animal::moveTo(const std::array<int,2>& finalPosition){

    while(!withinArea(finalPosition, 1, false)){

        int deltaX = finalPosition[0] - x;
        int deltaY = finalPosition[1] - y;

        if (abs(deltaX) >= 2 && abs(deltaX) >= abs(deltaY)) {
            
            x += (deltaX > 0) ? 2 : -2;

        } else if (abs(deltaY) >= 2 && abs(deltaY) > abs(deltaX)) {
            
            y += (deltaY > 0) ? 2 : -2;

        } else {
           
            x += (deltaX > 0) ? 1 : -1;
            y += (deltaY > 0) ? 1 : -1;
        }
    }
}