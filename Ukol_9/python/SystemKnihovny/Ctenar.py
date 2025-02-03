import random

class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self.jmeno = jmeno  # Používá validaci z vlastního setteru
        self.prijmeni = prijmeni  # Používá validaci z vlastního setteru
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self):
        return self._jmeno

    @jmeno.setter
    def jmeno(self, nove_jmeno):
        if not nove_jmeno.strip():
            raise ValueError("Jméno nesmí být prázdné.")
        self._jmeno = nove_jmeno.strip()

    @property
    def prijmeni(self):
        return self._prijmeni

    @prijmeni.setter
    def prijmeni(self, nove_prijmeni):
        if not nove_prijmeni.strip():
            raise ValueError("Příjmení nesmí být prázdné.")
        self._prijmeni = nove_prijmeni.strip()

    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, nove_cislo_prukazky):
        if isinstance(nove_cislo_prukazky, int) and nove_cislo_prukazky > 0:
            self._cislo_prukazky = nove_cislo_prukazky
        else:
            raise ValueError("Špatně zadané číslo průkazky, musí být kladné celé číslo.")

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1, 1000000)

    def __str__(self) -> str:
        return f"Čtenář: {self.jmeno} {self.prijmeni}, Číslo průkazky: {self.cislo_prukazky}"
