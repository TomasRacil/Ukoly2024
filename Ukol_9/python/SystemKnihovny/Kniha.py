class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        if len(isbn) != 13 or not isbn.isdigit():
            raise ValueError("ISBN musí mít 13 číslic")
        self.nazev = nazev
        self.autor = autor
        self.rok_vydani = rok_vydani
        self.isbn = isbn


    def __str__(self):
        return f"{self.nazev} ({self.rok_vydani}), {self.autor}, ISBN: {self.isbn}"
