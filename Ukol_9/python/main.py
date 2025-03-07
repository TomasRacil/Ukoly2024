from SystemKnihovny import Knihovna, Kniha, Ctenar
from os.path import realpath, dirname, join

if __name__ == "__main__":
    # 1) Načtení knihovny z CSV
    knihovna = Knihovna.z_csv(join(dirname(realpath(__file__)), "knihovna.csv"))
    print(f"Knihovna načtena z CSV: {knihovna.nazev}")

    # 2) Vytvoření a test jedné knihy s platným ISBN
    kniha1 = Kniha("Stopařův průvodce po Galaxii",
                   "Douglas Adams", 1979, "9780345391803")
    print(f"Kniha 1: {kniha1}")

    # 3) Pokus o vytvoření knihy s neplatným ISBN
    try:
        kniha2 = Kniha("Název knihy 2", "Autor 2", 2024, "invalidISBN")
    except ValueError as e:
        print(f"Chyba při vytváření knihy 2: {e}")

    # 4) Přidání, vypsání a odebrání knihy z knihovny
    knihovna.pridej_knihu(kniha1)
    print(f"Knihy v knihovně: {[str(k) for k in knihovna.knihy]}")

    knihovna.odeber_knihu("9780345391803")
    print(f"Knihy v knihovně po odebrání: {[str(k) for k in knihovna.knihy]}")

    # 5) Vytvoření čtenáře a test setteru cislo_prukazky
    ctenar1 = Ctenar("Jan", "Novák")
    print(f"Čtenář 1: {ctenar1}")
    try:
        ctenar1.cislo_prukazky = -100  # Invalid
    except ValueError as e:
        print(f"Chyba nastavení čísla průkazky: {e}")
    print(f"Čtenář 1: {ctenar1}")

    # 6) Registrace dvou čtenářů a vypsání seznamu
    ctenar2 = Ctenar("Petr", "Svoboda")
    knihovna.registruj_ctenare(ctenar1)
    knihovna.registruj_ctenare(ctenar2)
    print(f"Seznam čtenářů: {[str(c) for c in knihovna.ctenari]}")

    # 7) Zrušení registrace čtenáře ctenar1
    knihovna.zrus_registraci_ctenare(ctenar1)
    print(f"Seznam čtenářů po odebrání: {[str(c) for c in knihovna.ctenari]}")

    # 8) Vyhledání knih i čtenářů pomocí klíčových slov
    print(
        f"Vyhledávání knih dle klíčového slova '1984': {[str(k) for k in knihovna.vyhledej_knihu(klicova_slovo='1984')]}")
    print(
        f"Vyhledávání čtenářů dle klíčového slova 'Petr': {[str(ctenar) for ctenar in knihovna.vyhledej_ctenare(klicova_slovo='Petr')]}")

    # 9) Znovu přidat kniha1, vypůjčit, vrátit
    knihovna.pridej_knihu(kniha1)
    knihovna.vypujc_knihu(kniha1.isbn, ctenar2)
    print("Vypůjčené knihy:", [
          (isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()])
    knihovna.vrat_knihu(kniha1.isbn, ctenar2)
    print("Vypůjčené knihy po vrácení:", [
          (isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()])

    # 10) Výpis celé knihovny
    print(knihovna)
