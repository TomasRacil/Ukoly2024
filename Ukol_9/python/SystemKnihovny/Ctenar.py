import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, hodnota: int):
        if hodnota <= 0:
            raise ValueError("Číslo průkazky musí být kladné celé číslo.")
        self._cislo_prukazky = hodnota

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1, 100000)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, průkazka č. {self.cislo_prukazky}"
