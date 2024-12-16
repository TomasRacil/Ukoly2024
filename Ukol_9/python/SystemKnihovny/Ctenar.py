import random


class Ctenar:
    existing_ids = set()            # Množina pro sledování již existujících čísel průkazek

    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        self.cislo_prukazky = self.vygeneruj_cislo_prukazky()
        self._vypujcene_knihy = []

    # doplňte potřebné gettry a settry

    @property
    def jmeno(self) -> str:
        return self._jmeno

    @property
    def prijmeni(self) -> str:
        return self._prijmeni

    @property
    def cislo_prukazky(self) -> int:
        return self._cislo_prukazky

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        if value > 0:
            self._cislo_prukazky = value
        else:
            raise ValueError("Číslo průkazky musí být kladné číslo.")


    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
         return random.randint(10000, 99999)

    def __str__(self) -> str:
        return f"{self.jmeno} {self.prijmeni} (Průkazka: {self.cislo_prukazky})"

    def vypujcit_knihu(self, kniha_tuple) -> None:
        if kniha_tuple not in self._vypujcene_knihy:
            self._vypujcene_knihy.append(kniha_tuple)
        else:
            raise ValueError("Kniha je již vypůjčena.")

    def vratit_knihu(self, kniha_tuple) -> None:
        if kniha_tuple in self._vypujcene_knihy:
            self._vypujcene_knihy.remove(kniha_tuple)
        else:
            raise ValueError("Kniha není mezi vypůjčenými.")
