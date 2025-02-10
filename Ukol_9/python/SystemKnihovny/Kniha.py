import random
import datetime


class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn  # Použití setteru pro validaci

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("ISBN musí mít 13 číslic.")
        self._isbn = value

    @property
    def nazev(self) -> str:
        return self._nazev

    @nazev.setter
    def nazev(self, value: str):
        if not value.strip():
            raise ValueError("Název knihy nesmí být prázdný.")
        self._nazev = value

    @property
    def autor(self) -> str:
        return self._autor

    @autor.setter
    def autor(self, value: str):
        if not value.strip():
            raise ValueError("Autor nesmí být prázdný.")
        self._autor = value

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, value: int):
        if value > datetime.date.today().year:
            raise ValueError("Rok vydání nemůže být v budoucnosti.")
        self._rok_vydani = value

    def __str__(self) -> str:
        return f"{self._nazev} od {self._autor}, {self._rok_vydani}, ISBN: {self._isbn}"
