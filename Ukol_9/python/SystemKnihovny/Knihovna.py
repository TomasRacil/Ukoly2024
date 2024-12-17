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

    @classmethod
    def z_csv(cls, soubor: str) -> Knihovna:
        """
        Načte data knihovny ze souboru CSV.
        """
        try:
            with open(soubor, "r", encoding="utf-8") as file:
                reader = csv.reader(file)

                # Ignorování nevalidních prvních řádků
                prvni_radek = next(reader, None)
                if prvni_radek and "knihovna:" in prvni_radek[0]:
                    nazev_knihovny = prvni_radek[0].split(":", 1)[1].strip()
                else:
                    # Defaultní název knihovny, pokud první řádek není validní
                    nazev_knihovny = "Neznámá knihovna"

                # Validace záhlaví
                zahlavi = next(reader, None)
                if zahlavi != ["typ", "nazev", "autor", "rok_vydani", "isbn", "jmeno", "prijmeni"]:
                    raise ValueError("Chybný formát záhlaví CSV souboru!")

                knihovna = cls(nazev_knihovny)

                # Zpracování řádků CSV
                for radek in reader:
                    if radek[0] == "kniha":
                        kniha = Kniha(
                            nazev=radek[1],
                            autor=radek[2],
                            rok_vydani=int(radek[3]),
                            isbn=radek[4]
                        )
                        knihovna.pridej_knihu(kniha)
                    elif radek[0] == "ctenar":
                        ctenar = Ctenar(
                            jmeno=radek[5],
                            prijmeni=radek[6]
                        )
                        knihovna.registruj_ctenare(ctenar)

            return knihovna

        except Exception as e:
            raise ValueError(f"Chybný formát CSV souboru: {e}")

    def pridej_knihu(self, kniha: Kniha):
        self.knihy.append(kniha)

    def registruj_ctenare(self, ctenar: Ctenar):
        self.ctenari.append(ctenar)

    def __str__(self) -> str:
        knihy_info = "\n".join(str(kniha) for kniha in self.knihy)
        ctenari_info = "\n".join(str(ctenar) for ctenar in self.ctenari)
        return (f"Knihovna: {self.nazev}\n"
                f"Knihy:\n{knihy_info}\n"
                f"Čtenáři:\n{ctenari_info}")
