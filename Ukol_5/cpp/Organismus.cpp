#include "Organismus.h"

Organismus::Organismus(int xP, int yP, float energyP, Type typeP) { pos.x = xP; pos.y = yP; energy = energyP; type = typeP; }

bool Organismus::isAlive() {return energy > 0 ? true : false;}

Position Organismus::getPosition() {
	return pos;
}

float Organismus::getEnergy() {
	return energy;
}

bool Organismus::inRange(Organismus* org) {
	if (pos.x == org->pos.x && pos.y == org->pos.y) {
		return true;
		std::cout << "inRange!";
	}
	return false;
}