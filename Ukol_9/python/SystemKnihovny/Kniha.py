class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, value: str):
        if len(value) != 13 or not value.isdigit():
            raise ValueError("Neplatné ISBN.")
        self._isbn = value

    def __str__(self) -> str:
        return f"{self.nazev} - {self.autor} ({self.rok_vydani}), ISBN: {self.isbn}"
