from typing import List

def soucet(cisla: List[int]) -> int:
    """Vypočítá součet čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součet čísel.
    """
    return sum(cisla)


def soucin(cisla: List[int]) -> int:
    """Vypočítá součin čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Součin čísel.
    """
    result = 1
    for num in cisla:
        result *= num
    return result


def prumer(cisla: List[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Průměrná hodnota čísel.
    """
    return sum(cisla) / len(cisla) if cisla else 0.0


def median(cisla: List[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.
    """
    if not cisla:
        return 0.0
    sorted_cisla = sorted(cisla)
    n = len(sorted_cisla)
    mid = n // 2
    if n % 2 == 0:
        return (sorted_cisla[mid - 1] + sorted_cisla[mid]) / 2.0
    else:
        return sorted_cisla[mid]


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
