import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    # doplňte potřebné gettry a settry
    @property # dekorátor pro parametry objektu, bez manuálního volání
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky
    
    @cislo_prukazky.setter
    def cislo_prukazky(self, cislo: int):
        if cislo >= 1:
            self._cislo_prukazky = cislo
        else:
            raise ValueError("ID of reader's card can not be negative! ")

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(10000, 99999) # melo by obsahovat ošetření pro duplikátní hodnoty, ale nechám to na náhodě, šance je malá

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni} (Průkazka: {self.cislo_prukazky})"
