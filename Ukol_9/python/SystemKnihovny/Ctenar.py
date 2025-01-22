import random


class Ctenar:
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()

    #getry
    @property
    def jmeno(self) -> str:
        return self._jmeno
    
    @property
    def prijmeni(self) -> str:
        return self._prijmeni
    
    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky
    
    #setry
    @jmeno.setter
    def jmeno(self, jmeno: str):
        self._jmeno = jmeno
    
    @prijmeni.setter
    def prijmeni(self, prijmeni: str):
        self._prijmeni = prijmeni
    
    @cislo_prukazky.setter
    def cislo_prukazky(self, cislo_prukazky: int):
        if cislo_prukazky < 0:
            raise ValueError("Číslo průkazky nesmí být zaporne.") 
        self._cislo_prukazky = cislo_prukazky

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        return random.randint(1,1567)
        #nase knihovna ma momentalne 1567 ctenaru

    def __str__(self) -> str:
        return f"{self._jmeno} {self._prijmeni} - {self._cislo_prukazky}"
