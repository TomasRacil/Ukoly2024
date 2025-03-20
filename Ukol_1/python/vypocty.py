import statistics
from functools import reduce

def soucet(cisla: list[int]) -> int:
    """Vypočítá součet čísel v seznamu."""
    return sum(cisla)

def soucin(cisla: list[int]) -> int:
    """Vypočítá součin čísel v seznamu."""
    if not cisla:
        return 0  # Prázdný seznam vrací 0
    return reduce(lambda x, y: x * y, cisla)

def prumer(cisla: list[int]) -> float:
    """Vypočítá průměrnou hodnotu čísel v seznamu."""
    if not cisla:
        raise ValueError("Seznam čísel je prázdný")
    return sum(cisla) / len(cisla)

def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu."""
    if not cisla:
        raise ValueError("Seznam čísel je prázdný")
    return statistics.median(cisla)

def main():
    """Načte vstup od uživatele, zavolá funkce pro výpočet a vypíše výsledky."""
    vstup = input("Zadejte seznam čísel oddělených čárkou: ")
    cisla = [int(cislo) for cislo in vstup.split(",")]

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", round(prumer(cisla), 2))
    print("Medián:", median(cisla))

if __name__ == "__main__":
    main()
