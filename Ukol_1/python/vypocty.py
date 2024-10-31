import math


def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součet čísel.
    """
    if not cisla:
        raise ValueError("Seznam čísel je prázdný.")
    return sum(cisla)



def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součin čísel.
    """
    if not cisla:
        raise ValueError("Seznam čísel je prázdný.")
    return math.prod(cisla)


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Průměrná hodnota čísel.
    """
    if not cisla:
        raise ValueError("Seznam čísel je prázdný.")

    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.
    """
    cisla.sort()
    if not cisla:
        raise ValueError("Seznam čísel je prázdný.")  # Teoreticky by tu stačil jen tento raie VError, ale pokud chápu testy správně tak si volají funkci jako takovou proto je toto v každé funkci
    delka = len(cisla)
    if delka % 2 == 0:
        return (cisla[delka // 2 - 1] + cisla[delka // 2]) / 2
    else:
        return cisla[delka // 2]


def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",") if cislo.strip() != "" and cislo.strip().isdigit()]
    if not cisla:
        raise ValueError("Nebyla zadána žádná čísla.")  #
        
    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
