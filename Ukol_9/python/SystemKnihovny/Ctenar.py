import random

class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str, cislo_prukazky: int = None):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = cislo_prukazky or self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self):
        return self._jmeno

    @property
    def prijmeni(self):
        return self._prijmeni

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value):
        if value is None or value <= 0:
            raise ValueError("Číslo průkazky musí být kladné celé číslo.")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1, 1000000)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni} (Číslo průkazky: {self.cislo_prukazky})"