class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def nazev(self):
        return self._nazev

    @property
    def autor(self):
        return self._autor

    @property
    def rok_vydani(self):
        return self._rok_vydani

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = value

    def __str__(self) -> str:
        return f"{self.nazev} od {self.autor} (ISBN: {self.isbn})"