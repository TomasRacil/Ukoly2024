import random

class Ctenar:
    """
    Třída reprezentující čtenáře.
    """
    def __init__(self, jmeno: str, prijmeni: str):
        self._jmeno = jmeno
        self._prijmeni = prijmeni
        # Nastavíme výchozí číslo průkazky pomocí statické metody
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

    @cislo_prukazky.setter
    def cislo_prukazky(self, value: int):
        """
        Validuje a nastavuje číslo průkazky.
        Musí být kladné celé číslo.
        """
        if not isinstance(value, int) or value <= 0:
            raise ValueError(f"Číslo průkazky musí být kladné celé číslo, zadáno: {value}")
        self._cislo_prukazky = value

    @staticmethod
    def vygeneruj_cislo_prukazky() -> int:
        """
        Vygeneruje náhodné kladné celé číslo jako číslo průkazky.
        """
        return random.randint(1, 999999)

    def __str__(self) -> str:
        """
        Textová reprezentace čtenáře.
        """
        return f"{self._jmeno} {self._prijmeni}, průkazka: {self._cislo_prukazky}"
