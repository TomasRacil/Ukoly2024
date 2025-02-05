def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu."""
    return sum(cisla)

def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu."""
    if not cisla:
        return 0
    produkt = 1
    for cislo in cisla:
        produkt *= cislo
    return produkt

def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu."""
    if not cisla:
        raise ValueError("Seznam nesmí být prázdný.")
    return sum(cisla) / len(cisla)

def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu."""
    if not cisla:
        raise ValueError("Seznam nesmí být prázdný.")
    cisla.sort()
    n = len(cisla)
    mid = n // 2
    if n % 2 == 0:
        return (cisla[mid - 1] + cisla[mid]) / 2.0
    else:
        return cisla[mid]

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
