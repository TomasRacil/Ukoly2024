import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    # doplňte potřebné gettry a settry

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        pass

    def __str__(self) -> str:
        return ""
