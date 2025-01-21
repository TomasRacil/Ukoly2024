import random


def vytvor_matici(n: int, m: int) -> list[list[int]]:
    return [[random.randint(0, 9) for _ in range(m)] for _ in range(n)]


def reprezentace_matice(matice: list[list[int]]) -> str:
    if not matice:
        return ""
    return "\n".join(" ".join(map(str, radek)) for radek in matice) + "\n"


def soucet_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    if len(matice1) != len(matice2) or any(len(radek1) != len(radek2) for radek1, radek2 in zip(matice1, matice2)):
        print("Chyba, Matice nemají stejné rozměry.")
        return None
    return [[matice1[i][j] + matice2[i][j] for j in range(len(matice1[0]))] for i in range(len(matice1))]


def nasobeni_matic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]] | None:
    if not matice1 and not matice2:  # Obě matice prázdné
        return []
    if not matice1 or not matice2 or len(matice1[0]) != len(matice2):
        print("Chyba: Počet sloupců první matice se nerovná počtu řádků druhé matice.")
        return None
    return [
        [
            sum(matice1[i][k] * matice2[k][j] for k in range(len(matice2)))
            for j in range(len(matice2[0]))
        ]
        for i in range(len(matice1))
    ]

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    if not matice:
        return []
    if not matice[0]:
        return [[]]
    return [[matice[j][i] for j in range(len(matice))] for i in range(len(matice[0]))]


if __name__ == "__main__":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
