def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součet čísel.
    """
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
    if not cisla: 
        return 0  
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Průměrná hodnota čísel.
    """
    if not cisla:
        raise ValueError("Seznam nesmí být prázdný.")
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.
    """
    if not cisla:
        raise ValueError("Seznam nesmí být prázdný.")  # Vyhazujeme výjimku
    cisla.sort()
    n = len(cisla)
    if n % 2 == 1:
        return cisla[n // 2]
    else:
        return (cisla[n // 2 - 1] + cisla[n // 2]) / 2.0

def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))


if __name__ == "__main__":
    main()
