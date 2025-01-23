import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self.__cislo_prukazky = Ctenar.vygeneruj_cislo_prukazky()

    # getter and setter for cislo_prukazky
    @property
    def cislo_prukazky(self):
        return self.__cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value):
        if value < 0:
            raise ValueError("Číslo průkazky nemůže být záporné.")
        self.__cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky():
        return random.randint(10000, 99999)

    def __str__(self):
        return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"
