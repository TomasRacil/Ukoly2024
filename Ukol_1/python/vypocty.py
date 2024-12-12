def soucet(cisla: list[int]) -> int:
    return sum(cisla)

def soucin(cisla: list[int]) -> int:
    if len(cisla)==0:
        return 0
    soucin = 1
    for cislo in cisla:
        soucin *= cislo
    return soucin

def prumer(cisla: list[int]) -> float:
    if not cisla:
        raise ValueError("Prázdný seznam")
    return sum(cisla) / len(cisla)

def median(cisla: list[int]) -> float:
    if not cisla:
        raise ValueError("Prázdný seznam")
    sorted_cisla = sorted(cisla)
    n = len(sorted_cisla)

    mid = n // 2
    if n % 2 == 0:
        return (sorted_cisla[mid - 1] + sorted_cisla[mid]) / 2
    else:
        return sorted_cisla[mid]

def main():
    vstup = input("Zadejte seznam čísel oddělených čárkou (nebo nechte prázdné pro ukončení): ")
    if not vstup.strip():
        print("Prázdný vstup, program končí.")
        return
    
    cisla = [int(cislo) for cislo in vstup.split(",") if cislo.strip().isdigit()]
    
    if not cisla:
        print("Nebyla zadána platná čísla.")
        return

    print("Součet:", soucet(cisla))
    print("Součin:", soucin(cisla))
    print("Průměrná hodnota:", prumer(cisla))
    print("Medián:", median(cisla))

if __name__ == "__main__":
    main()
