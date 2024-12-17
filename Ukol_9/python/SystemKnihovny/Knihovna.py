from __future__ import annotations
from .Kniha import Kniha
from .Ctenar import Ctenar
import csv
import datetime


class Knihovna:
    def __init__(self, nazev: str):
        self.nazev = nazev
        self.knihy: list[Kniha] = []
        self.ctenari: list[Ctenar] = []
        self.vypujcene_knihy = {}

    # Dekorátor pro kontrolu existence knihy
    def kniha_existuje(funkce):
        def wrapper(self, isbn: str, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        try:
            with open(soubor, "r", encoding="utf-8") as file:
                reader = csv.reader(file)

                # Získání prvního řádku a kontrola
                prvni_radek = next(reader)
                if prvni_radek and len(prvni_radek) > 0 and "knihovna:" in prvni_radek[0]:
                    nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()
                else:
                    raise ValueError("Chybný formát názvu knihovny na prvním řádku CSV!")

                # Přeskočení záhlaví a kontrola
                zahlavi = next(reader)
                ocekavane_zahlavi = ["typ", "nazev", "autor", "rok_vydani", "isbn", "jmeno", "prijmeni"]
                if zahlavi != ocekavane_zahlavi:
                    raise ValueError("Chybný formát záhlaví CSV souboru!")

                # Inicializace knihovny
                knihovna = cls(nazev_knihovny)

                # Načítání jednotlivých řádků
                for radek in reader:
                    if radek[0] == "kniha":
                        kniha = Kniha(
                            nazev=radek[1],
                            autor=radek[2],
                            rok_vydani=int(radek[3]),
                            isbn=radek[4],
                        )
                        knihovna.pridej_knihu(kniha)
                    elif radek[0] == "ctenar":
                        ctenar = Ctenar(
                            jmeno=radek[5],
                            prijmeni=radek[6],
                        )
                        knihovna.registruj_ctenare(ctenar)

            return knihovna

        except StopIteration:
            raise ValueError("CSV soubor je prázdný nebo má nesprávný formát!")
        except Exception as e:
            raise ValueError(f"Chybný formát CSV souboru: {e}")

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [kniha for kniha in self.knihy if kniha.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        vysledky = []
        for kniha in self.knihy:
            if isbn and kniha.isbn == isbn:
                vysledky.append(kniha)
            elif klicova_slovo and (klicova_slovo.lower() in kniha.nazev.lower()
                                    or klicova_slovo.lower() in kniha.autor.lower()):
                vysledky.append(kniha)
        return vysledky

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        vysledky = []
        for ctenar in self.ctenari:
            if cislo_prukazky and ctenar.cislo_prukazky == cislo_prukazky:
                vysledky.append(ctenar)
            elif klicova_slovo and (klicova_slovo.lower() in ctenar.jmeno.lower()
                                    or klicova_slovo.lower() in ctenar.prijmeni.lower()):
                vysledky.append(ctenar)
        return vysledky

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self) -> str:
        knihy_info = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_info = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return (f"Knihovna: {self.nazev}\n"
                f"Knihy:\n{knihy_info}\n"
                f"Čtenáři:\n{ctenari_info}")
