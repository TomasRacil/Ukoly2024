#pragma once
#ifndef ROSTLINA_H
#define ROSTLINA_H

#include <random>
#include "Organismus.h"

class Rostlina : public Organismus
{
public:
	Rostlina(int xP, int yP, float energyP, Type type);
	void move() override;
};

#endif // !ROSTLINA_H
