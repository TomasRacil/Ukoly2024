import random


class Ctenar:

    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self._cislo_prukazky = self.vygeneruj_cislo_prukazky()

    @property
    def jmeno(self):
        return self._jmeno
    @property
    def prijmeni(self):
        return self._prijmeni
    @property
    def cislo_prukazky(self):
        return self._cislo_prukazky

    @jmeno.setter
    def jmeno(self,val: str):
        self._jmeno = val
    @prijmeni.setter
    def prijmeni(self,val:str):
        self._prijmeni = val
    @cislo_prukazky.setter
    def cislo_prukazky(self, val: int):
        if val > 0:
            self._cislo_prukazky = val
        else:
            raise ValueError('Membership card ID must be positive integer.')

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        #cislo_prukazky is positive integer in range <1,100>
        return random.randint(1,100)


    def __str__(self) -> str:
        out = "\n"
        out += self.jmeno + " " 
        out += self.prijmeni 
        out += "\t[membership card ID: " + str(self.cislo_prukazky) + "]"
        return out
    
    def __eq__(self, other):
        #defines equality of book objects
        return self.jmeno == other.jmeno and self.prijmeni == other.prijmeni and self.cislo_prukazky == other.cislo_prukazky
