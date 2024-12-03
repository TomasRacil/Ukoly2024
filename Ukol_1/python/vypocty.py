def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu."""
    soucet = 0
    for cislo in cisla:
        soucet += cislo
    return soucet


def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu."""
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin


def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu."""
    prumer = round((soucet(cisla) / len(cisla)),2)
    return prumer

    


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu."""
    sorted_cisla = sorted(cisla)
    if len(cisla) % 2 == 0:
        return (sorted_cisla[len(cisla) // 2 - 1] + sorted_cisla[len(cisla) // 2]) / 2
    else:
        return sorted_cisla[len(cisla) // 2]
    pass  # TODO: Implementujte funkci


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
