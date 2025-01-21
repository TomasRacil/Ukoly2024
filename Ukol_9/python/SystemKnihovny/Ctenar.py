import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    # Gettery
    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    # Settery
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

    # Statická metoda pro generování čísla průkazky
    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        """
        Generuje náhodné číslo průkazky (např. mezi 100000 a 999999).
        """
        return random.randint(100000, 999999)

    # Metoda pro reprezentaci čtenáře jako řetězec
    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni}, číslo průkazky: {self.cislo_prukazky}"