class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def nazev(self) -> str:
        return self._nazev

    @property
    def autor(self) -> str:
        return self._autor

    @property
    def rok_vydani(self) -> int:
        return self._rok_vydani

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("isbn musi mit 13 cislic")
        self._isbn = value

    def __str__(self) -> str:
        return f"nazev: {self._nazev} autor: {self._autor}, rok vydani: {self._rok_vydani}, isbn: {self._isbn}"
