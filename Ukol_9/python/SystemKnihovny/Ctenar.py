import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()


    @property
    def jmeno(self)-> str:
        return self._jmeno

    @jmeno.setter
    def jmeno(self, value: str)->None:
        self._jmeno = value

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @prijmeni.setter
    def prijmeni(self, value: str) -> None:
        self._prijmeni = value

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int) -> None:
        if value <= 0:
            raise ValueError(f"Cislo prukazky {value} musi byt kladne cislo")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1000, 9999)

    def __str__(self) -> str:
        return f"Ctenar: {self._jmeno} {self._prijmeni}, cislo prukazky: {self._cislo_prukazky}"
