#reupload
class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def nazev(self) -> str:
        return self._nazev

    @nazev.setter
    def nazev(self, value: str):
        self._nazev = value

    @property
    def autor(self) -> str:
        return self._autor

    @autor.setter
    def autor(self, value: str):
        self._autor = value

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @rok_vydani.setter
    def rok_vydani(self, value: int):
        self._rok_vydani = value

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = value

    def __str__(self) -> str:
        return f"Kniha: {self._nazev}, Autor: {self._autor}, Rok vydání: {self._rok_vydani}, ISBN: {self._isbn}"
