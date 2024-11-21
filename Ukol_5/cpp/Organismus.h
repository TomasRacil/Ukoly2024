#pragma once
#ifndef ORGANISMUS_H
#define ORGANISMUS_H

#include "iostream"
#include <time.h>
#include <random>

class Prostredi;

enum Type
{
	VEGETATION = 'V',
	CARNIVORE = 'C',
	HERBIVORE = 'H'
};

struct Position {
	int x;
	int y;
};
class Organismus
{
public:
	Position pos;
	float energy;
	Type type;

	Organismus(int xP, int yP, float energyP, Type typeP);
	virtual void move() = 0;
	bool isAlive();
	float getEnergy();
	Position getPosition();
	bool inRange(Organismus* org);

};


#endif // !ORGANISMUS_H