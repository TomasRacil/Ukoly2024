class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self.nazev = nazev  # Opraveno na veřejný atribut
        self.autor = autor
        self.rok_vydani = rok_vydani
        self._isbn = isbn  # Zůstává chráněný, validován setterem

    @property
    def isbn(self):
        return self._isbn

    @isbn.setter
    def isbn(self, hodnota):
        if len(hodnota) != 13 or not hodnota.isdigit():
            raise ValueError("ISBN musí mít formát ISBN-13 (13 číslic).")
        self._isbn = hodnota

    def __str__(self) -> str:
        return f"'{self.nazev}' od {self.autor} ({self.rok_vydani}) - ISBN: {self.isbn}"
