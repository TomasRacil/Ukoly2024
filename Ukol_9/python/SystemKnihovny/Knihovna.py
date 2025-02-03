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
        self.vypujcene_knihy: dict[str, Ctenar] = {}  # Mapování ISBN -> Čtenář

    def kniha_existuje(funkce):
        """
        Dekorátor kontrolující existenci knihy v knihovně.
        """

        def wrapper(self, isbn: str, *args, **kwargs):
            if not any(kniha.isbn == isbn for kniha in self.knihy):
                raise ValueError(f"Kniha s ISBN {isbn} neexistuje.")
            return funkce(self, isbn, *args, **kwargs)
        return wrapper

    @classmethod
    def z_csv(cls, soubor: str) -> "Knihovna":
        """
        Načte data knihovny ze souboru CSV, kde první řádek obsahuje název knihovny.
        
        Args:
            soubor: Cesta k souboru CSV.
        
        Returns:
            Objekt Knihovna načtený ze souboru.
        """
        knihovna = None

        try:
            with open(soubor, mode="r", encoding="utf-8") as f:
                reader = csv.reader(f)
                # Přečteme první řádek pro název knihovny
                first_line = next(reader, None)
                if first_line is None or not first_line[0].startswith("Knihovna:"):
                    raise ValueError("První řádek CSV souboru musí obsahovat název knihovny ve formátu 'Knihovna:Název_knihovny'")
                
                nazev_knihovny = first_line[0].split(":", 1)[1].strip()  # Extrahujeme název knihovny
                knihovna = cls(nazev_knihovny)

                # Čteme zbytek souboru
                reader = csv.DictReader(f)
                
                for radek in reader:
                    # Rozlišení podle typu
                    typ = radek.get("typ", "").strip().lower()
                    if typ == "kniha":
                        try:
                            rok_vydani = int(radek["rok_vydani"]) if radek["rok_vydani"] else None
                        except ValueError:
                            rok_vydani = None  # Pokud je rok_vydani neplatné, nastavíme None

                        knihovna.pridej_knihu(Kniha(
                            nazev=radek["nazev"],
                            autor=radek["autor"],
                            rok_vydani=rok_vydani,
                            isbn=radek["isbn"]
                        ))
                    elif typ == "ctenar":
                        knihovna.registruj_ctenare(Ctenar(
                            jmeno=radek["jmeno"],
                            prijmeni=radek["prijmeni"]
                        ))

        except Exception as e:
            raise ValueError(f"Chyba při načítání CSV: {e}")
        
        if not knihovna:
            raise ValueError("Soubor neobsahuje validní data knihovny.")
        
        return knihovna


    def pridej_knihu(self, kniha: Kniha):
        if any(k._isbn == kniha.isbn for k in self.knihy):
            raise ValueError(f"Kniha s ISBN {kniha.isbn} již existuje v knihovně.")
        self.knihy.append(kniha)

    @kniha_existuje
    def odeber_knihu(self, isbn: str):
        self.knihy = [k for k in self.knihy if k.isbn != isbn]

    def vyhledej_knihu(self, klicova_slovo: str = "", isbn: str = "") -> list[Kniha]:
        return [
            k
            for k in self.knihy
            if isbn and k.isbn == isbn
            or klicova_slovo.lower() in k.nazev.lower()
            or klicova_slovo.lower() in k.autor.lower()
        ]

    def registruj_ctenare(self, ctenar: Ctenar):
        if any(c._cislo_prukazky == ctenar.cislo_prukazky for c in self.ctenari):
            raise ValueError(f"Čtenář s číslem průkazky {ctenar.cislo_prukazky} je již registrován.")
        self.ctenari.append(ctenar)

    def zrus_registraci_ctenare(self, ctenar: Ctenar):
        if ctenar not in self.ctenari:
            raise ValueError("Čtenář není registrován.")
        self.ctenari.remove(ctenar)

    def vyhledej_ctenare(self, klicova_slovo: str = "", cislo_prukazky: int = None) -> list[Ctenar]:
        return [
            c
            for c in self.ctenari
            if (cislo_prukazky and c.cislo_prukazky == cislo_prukazky)
            or klicova_slovo.lower() in c.jmeno.lower()
            or klicova_slovo.lower() in c.prijmeni.lower()
        ]

    @kniha_existuje
    def vrat_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            del self.vypujcene_knihy[isbn]  # odstraníme knihu, když je vrácena
        else:
            raise ValueError(f"Kniha s ISBN {isbn} není vypůjčena.")

    @kniha_existuje
    def vypujc_knihu(self, isbn: str, ctenar: Ctenar):
        if isbn in self.vypujcene_knihy:
            raise ValueError(f"Kniha s ISBN {isbn} je již vypůjčena.")
        datum = datetime.date.today()
        self.vypujcene_knihy[isbn] = (ctenar, datum)

    def __str__(self) -> str:
        knihy_vypis = "\n".join([str(kniha) for kniha in self.knihy])
        ctenari_vypis = "\n".join([str(ctenar) for ctenar in self.ctenari])
        return f"Knihovna: {self.nazev}\n\nKnihy:\n{knihy_vypis}\n\nČtenáři:\n{ctenari_vypis}"

