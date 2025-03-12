import random

class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError("Číslo průkazky musí být kladné číslo.")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1, 1000000)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, Průkazka: {self.cislo_prukazky}"
