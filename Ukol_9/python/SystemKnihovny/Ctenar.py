import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    # doplňte potřebné gettry a settry

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1, 10000)

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0 or not isinstance(value, int):
            raise ValueError("Cislo prukazky musi byt kladne cele cislo.")
        self._cislo_prukazky = value

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, {self.cislo_prukazky}"
