import re

class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    # doplňte potřebné gettry a setry

    @property #property pro cteni
    def nazev(self)-> str:
        return self._nazev

    @nazev.setter #setter pro zmenu
    def nazev(self, value: str) -> None:
        self._nazev = value

    @property
    def autor(self) -> str:
        return self._autor

    @autor.setter
    def autor(self, value: str) -> None:
        self._autor = value

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, value: int) -> None:
        if value < 1000 or value > 9999:
            raise ValueError(f"Rok vydani {value} neni platny")
        self._rok_vydani = value


    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter #setter isbn kontroluje ze hodnota je ISBN-13
    def isbn(self, value: str) -> None:
        if not re.match(r'^\d{13}$', value): #regularni vyraz
            raise ValueError(f"ISBN {value} neni platne")
        self._isbn = value

    def __str__(self) -> str: #vypis objektu tridy Kniha
        return f"Kniha: {self._nazev}, autor: {self._autor}, rok vydani: {self._rok_vydani}, ISBN: {self._isbn}"
