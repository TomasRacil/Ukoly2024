class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self._isbn = None
        self.isbn = isbn  # Validace při inicializaci

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
    def isbn(self, hodnota: str):
        if not (hodnota.isdigit() and len(hodnota) == 13):
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = hodnota

    def __str__(self) -> str:
        return f"{self.nazev} od {self.autor}, vydáno {self.rok_vydani}, ISBN: {self.isbn}"
