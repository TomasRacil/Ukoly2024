import random

# trida ctenare
class Ctenar: 

    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno        # (string) jmeno ctenare
        self._prijmeni = prijmeni  # (string) prijmeni ctenare
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()   # (int) cislo prukazky ctenare

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:  # vzgeneruje kladne cele cislo
      
        return random.randint(1, 999999)

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @jmeno.setter
    def jmeno(self, value: str):
        if not value.strip():
            raise ValueError("jmeno nesmi byt prazdne")
        self._jmeno = value

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @prijmeni.setter
    def prijmeni(self, value: str):
        if not value.strip():
            raise ValueError("prijmeni nesmi byt prazdne")
        self._prijmeni = value

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value <= 0:
            raise ValueError("cislo prukazky musi byt kladne")
        self._cislo_prukazky = value

    def __str__(self) -> str:
        # vraci udaje o ctenari
        return f"Čtenář: {self.jmeno} {self.prijmeni}, Číslo průkazky: {self.cislo_prukazky}"
