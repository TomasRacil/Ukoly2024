class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value):
        if not (value.isdigit() and len(value) == 13):
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = value

    def __str__(self) -> str:
        return f"{self._nazev} od {self._autor} ({self._rok_vydani}) - ISBN: {self.isbn}"
