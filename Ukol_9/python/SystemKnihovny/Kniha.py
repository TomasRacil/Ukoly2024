class Kniha:
    def __init__(self, nazev: str, autor: str, rok_vydani: int, isbn: str):
        self._nazev = nazev
        self._autor = autor
        self._rok_vydani = rok_vydani
        self.isbn = isbn

    # doplňte potřebné gettry a setry

    def __str__(self) -> str:
        return ""
