class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def isbn(self) -> str:
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if not (len(value) == 13 and value.isdigit()):
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = value

    def __str__(self) -> str:
        return f"{self.nazev} od {self.autor} ({self.rok_vydani}) - ISBN: {self.isbn}"
