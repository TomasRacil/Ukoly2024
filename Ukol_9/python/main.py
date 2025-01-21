from SystemKnihovny import Knihovna, Kniha, Ctenar
from os.path import realpath, dirname, join


if __name__ == "__main__":

    knihovna = Knihovna.z_csv(
        join(dirname(realpath(__file__)), "knihovna.csv"))
    
    # Načtení knihovny z CSV souboru
    knihovna = Knihovna.z_csv(join(dirname(realpath(__file__)), "knihovna.csv"))
    print(f"Knihovna načtena z CSV: {knihovna.nazev}")

    kniha1 = Kniha("Stopařův průvodce po Galaxii",
                   "Douglas Adams", 1979, "9780345391803")
    
    # Vytvoření nové knihy
    kniha1 = Kniha("Stopařův průvodce po Galaxii", "Douglas Adams", 1979, "9780345391803")
    print(f"Kniha 1: {kniha1}")

    # Pokus o vytvoření knihy s neplatným ISBN
    try:
        kniha2 = Kniha("Název knihy 2", "Autor 2", 2024, "invalidISBN")
    except ValueError as e:
        print(f"Chyba při vytváření knihy 2: {e}")

    # Přidání knihy do knihovny
    knihovna.pridej_knihu(kniha1)
    print(f"Knihy v knihovně: {[str(k) for k in knihovna.knihy]}")

    # Odebrání knihy z knihovny
    knihovna.odeber_knihu("9780345391803")
    print(f"Knihy v knihovně po odebrání: {[str(k) for k in knihovna.knihy]}")

    # Vytvoření čtenáře
    ctenar1 = Ctenar("Jan", "Novák")
    print(f"Čtenář 1: {ctenar1}")

    # Pokus o nastavení neplatného čísla průkazky
    try:
        ctenar1.cislo_prukazky = -100  # Invalid
    except ValueError as e:
        print(f"Chyba nastavení čísla průkazky: {e}")
    print(f"Čtenář 1: {ctenar1}")

    # Registrace čtenářů
    ctenar2 = Ctenar("Petr", "Svoboda")
    knihovna.registruj_ctenare(ctenar1)
    knihovna.registruj_ctenare(ctenar2)
    print(f"Seznam čtenářů: {[str(c) for c in knihovna.ctenari]}")

    # Odebrání čtenáře
    knihovna.zrus_registraci_ctenare(ctenar1)
    print(f"Seznam čtenářů po odebrání: {[str(c) for c in knihovna.ctenari]}")

    print(f"""Vyhledávání knih podle klíčových slov: {
          [str(kniha) for kniha in knihovna.vyhledej_knihu(klicova_slovo='1984')]}""")
    print(f"""Vyhledávání čtenářů podle klíčových slov: {
          [str(ctenar) for ctenar in knihovna.vyhledej_ctenare(klicova_slovo='Petr')]}""")
    
    # Vyhledávání knih a čtenářů
    print(f"""Vyhledávání knih podle klíčových slov: {
      [str(kniha) for kniha in knihovna.vyhledej_knihu(klicova_slovo='1984')]}""")
    print(f"""Vyhledávání čtenářů podle klíčových slov: {
      [str(ctenar) for ctenar in knihovna.vyhledej_ctenare(klicova_slovo='Petr')]}""")

    # Vypůjčení knihy
    knihovna.pridej_knihu(kniha1)
    knihovna.vypujc_knihu(kniha1.isbn, ctenar2)
    print(f"""Vypůjčené knihy: {[(isbn, str(ctenar), str(datum))
          for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}""")
    print(f"Vypůjčené knihy: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")

    # Vrácení knihy
    knihovna.vrat_knihu(kniha1.isbn, ctenar2)
    print(f"""Vypůjčené knihy po vrácení: {[(isbn, str(ctenar), str(datum))
          for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}""")
    print(f"Vypůjčené knihy po vrácení: {[(isbn, str(ctenar), str(datum)) for isbn, (ctenar, datum) in knihovna.vypujcene_knihy.items()]}")

    # Výpis knihovny
    print(knihovna)
