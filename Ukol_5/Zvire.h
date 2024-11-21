#pragma once
#ifndef ZVIRE_H
#define ZVIRE_H

#include "Organismus.h"
#include <time.h>
#include <random>

class Zvire : public Organismus
{
public:
	Zvire(int xP, int yP, float energyP, Type type);
	void move() override;
	void consume(Organismus* org);
};

#endif

