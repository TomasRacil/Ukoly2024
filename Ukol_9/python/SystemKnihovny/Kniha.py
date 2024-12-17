class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn  # Setter validuje ISBN

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
    def isbn(self, isbn: str):
        if len(isbn) == 13 and isbn.isdigit():
            self._isbn = isbn
        else:
            raise ValueError("ISBN musí mít 13 číslic.")

    def __str__(self) -> str:
        return f"{self.nazev} od {self.autor} ({self.rok_vydani}) [ISBN: {self.isbn}]"
