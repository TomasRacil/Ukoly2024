def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu."""
    return sum(cisla)


def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu."""
    if len(cisla) == 0:
        return 0  # Vrací 0 pro prázdný seznam, jak očekává test
    result = 1
    for a in cisla:
        result *= a
    return result


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu."""
    if len(cisla) == 0:
        raise ValueError("Seznam je prázdný")  # Explicitně vyvolá výjimku pro prázdný seznam
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu."""
    if len(cisla) == 0:
        raise ValueError("Seznam je prázdný")  # Vyvolá výjimku pro prázdný seznam

    sorted_cisla = sorted(cisla)  # Seřazení seznamu
    n = len(sorted_cisla)
    mid = n // 2

    if n % 2 == 0:
        return (sorted_cisla[mid - 1] + sorted_cisla[mid]) / 2
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
