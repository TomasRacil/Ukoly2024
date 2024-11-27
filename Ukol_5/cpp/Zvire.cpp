#include "Zvire.h"

Zvire::Zvire(int xP, int yP, float energyP, Type type) : Organismus(xP, yP, energyP, type) {

}

int getRandom(int val) {
	srand(time(0));
	return rand() % (val* 2) - val;
}

void Zvire::move() {
	energy -= getRandom(5) + 2;
	pos.x += getRandom(10);
	pos.y += getRandom(10);
	if (pos.x < 0) pos.x = 0;
	if (pos.x > 15) pos.x = 28;
	if (pos.y < 0) pos.y = 0;
	if (pos.y > 15) pos.y = 28;
}



void Zvire::consume(Organismus* org) {
	if (inRange(org) && type == HERBIVORE && org->type == VEGETATION) {
		energy += org->energy;
		org->energy = -100;
		std::cout << "ate vegetation\n";

	}
	else if (inRange(org) && type == CARNIVORE && org->type == HERBIVORE) {
		energy += org->energy;
		org->energy = -100;
		std::cout << "ate animal\n";

	}
}
