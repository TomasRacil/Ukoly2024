#include "rostlina.h"

Rostlina::Rostlina(int pocatecniEnergie) : Organismus(pocatecniEnergie) {}

void Rostlina::akce(std::vector<Organismus*>& populace) {
    energie += 10;
    if (energie >= 50) {
        populace.push_back(new Rostlina(20));
        energie -= 20;
        std::cout << "Rostlina se rozmnožila." << std::endl;
    }
}

bool Rostlina::jeRostlina() const {
    return true;
}
