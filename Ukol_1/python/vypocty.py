def soucet(cisla: list[int]) -> int: 
    """Vypočítá součet čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součet čísel.
    """
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součin čísel.
    """
    if not cisla:
        # Pro prázdný seznam vrátíme 0 místo 1
        return 0

    produkt = 1
    for c in cisla:
        produkt *= c
    return produkt


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Průměrná hodnota čísel.

    Raises:
      ValueError: Pokud je seznam prázdný.
    """
    if not cisla:
        raise ValueError("Nelze spočítat průměr z prázdného seznamu.")

    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.

    Raises:
      ValueError: Pokud je seznam prázdný.
    """
    if not cisla:
        raise ValueError("Nelze spočítat medián z prázdného seznamu.")

    s = sorted(cisla)
    n = len(s)
    stred = n // 2

    if n % 2 == 0:
        return (s[stred - 1] + s[stred]) / 2.0
    else:
        return s[stred]


def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    try:
        print("Průměrná hodnota:", prumer(cisla))
    except ValueError as e:
        print("Chyba:", e)
    try:
        print("Medián:", median(cisla))
    except ValueError as e:
        print("Chyba:", e)


if __name__ == "__main__":
    main()
