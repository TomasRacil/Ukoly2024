#pragma once
#ifndef PROSTREDI_H
#define PROSTREDI_H

#include <vector>
#include <iostream>
#include "Rostlina.h"
#include "Masozravec.h"
#include "Bylozravec.h"

struct Grid {
	bool occupied = false;
	std::string drawChar =  "_  ";
};

class Prostredi
{
public:
	std::vector <std::vector <Grid>> grid;
	int width, height;
	std::vector <Masozravec> carnivores;
	std::vector <Rostlina> vegetation;
	std::vector <Bylozravec> herbivores;

	Prostredi(int widthP, int heightP);
	void addHerbivore(Bylozravec herb);
	void addCarnivore(Masozravec carn);
	void addVegetation(Rostlina vege);
	void actions(Type type);
	Position getNearby(Position pos);
	void draw();
};

#endif