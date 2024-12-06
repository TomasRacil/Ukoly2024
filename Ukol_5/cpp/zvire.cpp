#include "zvire.h"

Zvire::Zvire(int pocatecniEnergie) : Organismus(pocatecniEnergie) {}

void Zvire::akce(std::vector<Organismus*>& populace) {
    energie -= 8;
    for (auto& organismus : populace) {
        if (organismus->jeRostlina() && !organismus->jeMrtvy()) {
            organismus->pridejEnergii(-10);
            energie += 15;
            std::cout << "Zvíře snědlo rostlinu." << std::endl;
            break;
        }
    }
    if (energie >= 100) {
        populace.push_back(new Zvire(50));
        energie -= 50;
        std::cout << "Zvíře se rozmnožilo." << std::endl;
    }
}

bool Zvire::jeRostlina() const {
    return false;
}
