import random


def vytvormatici(n: int, m: int) -> list[list[int]]:
    matice: list[list[int]] = []
    return matice

def reprezentacematice(matice: list[list[int]]) -> str:
    return ""

def soucetmatic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    matice: list[list[int]] = []
    return matice

def nasobenimatic(matice1: list[list[int]], matice2: list[list[int]]) -> list[list[int]]:
    matice: list[list[int]] = []
    return matice

def transpozice_matice(matice: list[list[int]]) -> list[list[int]]:
    matice: list[list[int]] = []
    return matice

if __name == "__main":
    matice1: list[list[int]] = vytvor_matici(3, 2)
    matice2: list[list[int]] = vytvor_matici(2, 4)

    print("Matice 1:")
    print(reprezentace_matice(matice1))
    print("Matice 2:")
    print(reprezentace_matice(matice2))

    soucet = soucet_matic(matice1, matice1)  # Sečteme matici1 samu se sebou
    print("Součet matic:")
    print(reprezentace_matice(soucet))

    nasobek = nasobeni_matic(matice1, matice2)
    print("Násobení matic:")
    print(reprezentace_matice(nasobek))

    transponovana = transpozice_matice(matice1)
    print("Transponovaná matice:")
    print(reprezentace_matice(transponovana))
