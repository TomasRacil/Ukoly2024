#include "Prostredi.h"

Prostredi::Prostredi(int wid, int hei) {
	std::vector<std::vector<Grid>> rem({ 40 }, std::vector<Grid>({ 40 }));
	grid = rem;
	width = wid; height = hei;
	for (int w = 0; w < width - 1; w++) {
		for (int h = 0; h < height - 1; h++) {
			grid[w][h] = { false,  "_  "};
		}
	}

}

Position Prostredi::getNearby(Position pos) {
	srand(time(0));
	int x = pos.x;
	int y = pos.y;
	std::cout << "orgXY: " << x << " : " << y << "\n";
	x += rand() % 10 - 5;
	y += rand() % 10 - 5;
	std::cout << "orgXY2: " << x << " : " << y << "\n";
	int reset = 100;
	if (x >= 15 || x < 0 || y >= 15 || y < 0) {
		x += rand() % 10 - 5;
		y += rand() % 10 - 5;
		std::cout << x << "," << y << " / ";
	}
	while (grid[x][y].occupied && reset > 0) {
		if (x >= 15 || x < 0 || y >= 15 || y < 0) {
			std::cout << "Out of bounds before: " << x << " / " << y;
			x += rand() % 10 - 5;
			y += rand() % 10 - 5;
			std::cout << "Out of bounds now: " << x << " / " << y;
		}
		reset--;
	}
	if (x >= 15 || x < 0 || y >= 15 || y < 0) {
		x = rand() % 14;
		y = rand() % 14;
	}
	std::cout << "newXY: " << x << " : " << y << "\n";
	return { x,y };
}

void Prostredi::addCarnivore(Masozravec carn) {
	carnivores.push_back(carn);
}

void Prostredi::addHerbivore(Bylozravec herb) {
	herbivores.push_back(herb);
}

void Prostredi::addVegetation(Rostlina vege) {
	vegetation.push_back(vege);
}

void Prostredi::actions(Type type) {
	srand(time(0));
	switch (type) {
	case HERBIVORE:
		for (int i = 0; i < herbivores.size() - 1; i++) {
			if (herbivores.at(i).getEnergy() >= 100) { // rozmnožování
				std::cout << "new herbivore\n";
				herbivores.at(i).energy -= 50;
				for (int x = 0; x < rand() % 5 + 2; x++) {
					Position rem = getNearby(herbivores.at(i).getPosition());
					addHerbivore(Bylozravec( rem.x, rem.y, 15, HERBIVORE ));
				}
			}
			grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].occupied = false;
			grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].drawChar = "_  ";
			herbivores.at(i).move();
			for (int veg = 0; veg < vegetation.size() - 1; veg++) {
				herbivores.at(i).consume(&vegetation.at(veg));
			}
			if (!herbivores.at(i).isAlive()) {
				grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].occupied = false;
				grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].drawChar =  "_  ";
				herbivores.erase(herbivores.begin() + i);

				 
			}
			else {
				grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].drawChar = HERBIVORE;
				grid[herbivores.at(i).pos.x][herbivores.at(i).pos.y].occupied = true;

			}
			std::cout << herbivores.at(i).energy << "\n";

		}
		std::cout << "HERBIVORES: " << herbivores.size() - 1 << "\n";
		break;
	case CARNIVORE:
		for (int i = 0; i < carnivores.size() - 1; i++) {
			if (carnivores.at(i).getEnergy() >= 100) { // rozmnožování
				std::cout << "new carnivore\n";

				carnivores.at(i).energy -= 50;
				for (int x = 0; x < rand() % 5 + 2; x++) {
					Position rem = getNearby(carnivores.at(i).getPosition());
					addCarnivore(Masozravec( rem.x, rem.y, 45, CARNIVORE ));
				}
			}
			grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].occupied = false;
			grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].drawChar = "_  ";
			carnivores.at(i).move();
			if (!carnivores.at(i).isAlive()) {
				grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].occupied = false;
				grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].drawChar = "_  ";
				carnivores.erase(carnivores.begin() + i);


			}
			else {
				grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].drawChar = CARNIVORE;
				grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].occupied = true;

			}
			for (int herb = 0; herb < herbivores.size() - 1; herb++) {
				carnivores.at(i).consume(&vegetation.at(herb));
			}
			grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].drawChar = CARNIVORE;
			grid[carnivores.at(i).pos.x][carnivores.at(i).pos.y].occupied = true;
			std::cout << carnivores.at(i).energy << "\n";
		}
		std::cout << "CARNIVORES: " << carnivores.size() - 1 << "\n";

		break;
	case VEGETATION:
		for (int i = 0; i < vegetation.size() - 1; i++) {
			if (vegetation.at(i).getEnergy() >= 20) { // rozmnožování
				vegetation.at(i).energy -= 10;
				for (int x = 0; x < rand() % 5 + 2; x++) {
					std::cout << "new vegetation\n";
					Position rem = getNearby(this->vegetation.at(i).getPosition());
					addVegetation(Rostlina( rem.x, rem.y, 10, VEGETATION ));
					grid[rem.x][rem.y].occupied = true;
					grid[rem.x][rem.y].drawChar = VEGETATION;

				}
			}

			vegetation.at(i).energy += rand() % 10 - 5;
			if (!vegetation.at(i).isAlive()) {

				grid[vegetation.at(i).pos.x][vegetation.at(i).pos.y].occupied = false;
				grid[vegetation.at(i).pos.x][vegetation.at(i).pos.y].drawChar =  "_  ";
				vegetation.erase(vegetation.begin() + i);

				 
			}
			std::cout << vegetation.at(i).energy << "\n";

		}
		std::cout << "VEGETATION: " << vegetation.size() - 1 << "\n";

		break;
	}
}

void Prostredi::draw() {
	for (int w = 0; w < width; w++) {
		for (int h = 0; h < height; h++) {
			std::cout << grid[w][h].drawChar;
		}
		std::cout << "\n";
	}
}