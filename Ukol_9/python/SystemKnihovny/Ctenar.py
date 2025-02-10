import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno
        self.prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @jmeno.setter
    def jmeno(self, value: str):
        if not value:
            raise ValueError("Jméno nesmí být prázdné.")
        self._jmeno = value

    @prijmeni.setter
    def prijmeni(self, value: str):
        if not value:
            raise ValueError("Příjmení nesmí být prázdné.")
        self._prijmeni = value

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError("Číslo průkazky musí být kladné.")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(100000, 999999)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"
