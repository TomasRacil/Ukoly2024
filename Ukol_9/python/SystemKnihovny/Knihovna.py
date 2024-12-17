import csv
from .Kniha import Kniha
from .Ctenar import Ctenar
import datetime


class Knihovna:
    def __init__(self, nazev: str = "Neznámá knihovna"):
        self.nazev = nazev
        self.knihy = []
        self.ctenari = []
        self.vypujcene_knihy = {}  # Klíč: ISBN, Hodnota: (čtenář, datum výpůjčky)

    @classmethod
    def z_csv(cls, soubor: str):
        """
        Načte data knihovny ze souboru CSV.
        """
        try:
            with open(soubor, "r", encoding="utf-8") as file:
                reader = csv.reader(file)

                prvni_radek = next(reader, None)
                if prvni_radek and "Knihovna:" in prvni_radek[0]:
                    nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()
                else:
                    raise ValueError("Chybný formát názvu knihovny na prvním řádku CSV!")

                zahlavi = next(reader, None)
                if zahlavi != ["typ", "nazev", "autor", "rok_vydani", "isbn", "jmeno", "prijmeni"]:
                    raise ValueError("Chybný formát záhlaví CSV souboru!")

                knihovna = cls(nazev_knihovny)

                for radek in reader:
                    if radek[0] == "kniha":
                        knihovna.knihy.append(Kniha(radek[1], radek[2], int(radek[3]), radek[4]))
                    elif radek[0] == "ctenar":
                        knihovna.ctenari.append(Ctenar(radek[5], radek[6]))
                return knihovna

        except Exception as e:
            raise ValueError(f"Chybný formát CSV souboru: {e}")

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = ""):
        return [k for k in self.knihy if isbn in k.isbn or klicova_slovo.lower() in k.nazev.lower()]

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        self.ctenari = [c for c in self.ctenari if c.cislo_prukazky != ctenar.cislo_prukazky]

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None):
        return [c for c in self.ctenari if (klicova_slovo.lower() in c.jmeno.lower() or klicova_slovo.lower() in c.prijmeni.lower())
                or (cislo_prukazky and c.cislo_prukazky == cislo_prukazky)]

    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        self.vypujcene_knihy[isbn] = (ctenar, datetime.date.today())

    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn not in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")
        if self.vypujcene_knihy[isbn][0] != ctenar:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena tímto čtenářem.")
        del self.vypujcene_knihy[isbn]

    def __str__(self):
        knihy_str = "\n".join(str(k) for k in self.knihy)
        ctenari_str = "\n".join(str(c) for c in self.ctenari)
        return f"Knihovna: {self.nazev}\n\nKnihy:\n{knihy_str}\n\nČtenáři:\n{ctenari_str}"
