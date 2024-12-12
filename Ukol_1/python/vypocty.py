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
        raise ValueError("Seznam je prázdný")
    return sum(cisla) / len(cisla)


def median(cisla: list[int]) -> float:
    """Vypočítá medián čísel v seznamu.

    Args:
      cisla: Seznam čísel.

    Returns:
      Medián čísel.
    """
    if not cisla:
        raise ValueError("Seznam je prázdný")
    cisla.sort()
    n = len(cisla)
    mid = n // 2
    if n % 2 == 0:
        return (cisla[mid - 1] + cisla[mid]) / 2
    else:
        return cisla[mid]