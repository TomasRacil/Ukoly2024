#include "prostredi.h"
#include <iostream>

Prostredi::Prostredi() {}

Prostredi::~Prostredi() {
    for (auto organismus : populace) {
        delete organismus;
    }
}

void Prostredi::pridatOrganismus(Organismus* organismus) {
    populace.push_back(organismus);
}

void Prostredi::simulace(int kola) {
    for (int kolo = 1; kolo <= kola; ++kolo) {
        std::cout << "\nKolo " << kolo << ":" << std::endl;
        for (auto& organismus : populace) {
            if (!organismus->jeMrtvy()) {
                organismus->akce(populace);
                std::cout << "Organismus s energií: " << organismus->getEnergie() << std::endl;
            }
        }
        odstranMrtve();
        std::cout << "Počet organismů: " << populace.size() << std::endl;
    }
}

void Prostredi::odstranMrtve() {
    for (size_t i = 0; i < populace.size(); ++i) {
        if (populace[i]->jeMrtvy()) {
            delete populace[i];
            populace.erase(populace.begin() + i);
            --i;
        }
    }
}
