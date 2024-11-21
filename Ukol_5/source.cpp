#include "Prostredi.h"
#include "Masozravec.h"
#include <string>
#include <Windows.h>

int main() {
	Prostredi pros(15, 15);

	pros.addCarnivore(Masozravec( 7,7, 15, CARNIVORE ));
	pros.addCarnivore(Masozravec(7, 8, 120, CARNIVORE));
	pros.addCarnivore(Masozravec(4, 12, 70, CARNIVORE));
	pros.addCarnivore(Masozravec(11, 5, -7, CARNIVORE));
	pros.addCarnivore(Masozravec(5, 13, 70, CARNIVORE));

	pros.addHerbivore(Bylozravec(3, 1, 70, HERBIVORE));
	pros.addHerbivore(Bylozravec(3, 2, 70, HERBIVORE));
	pros.addHerbivore(Bylozravec(8, 11, 70, HERBIVORE));
	pros.addHerbivore(Bylozravec(4, 4, 70, HERBIVORE));
	pros.addHerbivore(Bylozravec(3, 12, 70, HERBIVORE));
	pros.addHerbivore(Bylozravec(1, 8, 70, HERBIVORE));

	pros.addVegetation(Rostlina(10, 1, 10, VEGETATION));
	pros.addVegetation(Rostlina(4, 12, 10, VEGETATION));
	pros.addVegetation(Rostlina(5, 5, 10, VEGETATION));
	pros.addVegetation(Rostlina(6, 4, 10, VEGETATION));
	pros.addVegetation(Rostlina(7, 12, 10, VEGETATION));
	pros.addVegetation(Rostlina(2, 8, 10, VEGETATION));
	pros.addVegetation(Rostlina(1, 0, 10, VEGETATION));
	pros.addVegetation(Rostlina(6, 9, 10, VEGETATION));
	pros.addVegetation(Rostlina(10, 9, 10, VEGETATION));

	char end = ' ';
	std::cout << "press anything to start, x to end";
	while (end != 'x') {
		end = std::getchar();
		pros.actions(VEGETATION);
		pros.actions(HERBIVORE);
		pros.actions(CARNIVORE);
		pros.draw();


	}



}