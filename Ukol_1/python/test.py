import unittest
from vypocty import soucet, soucin, prumer, median


class TestFunkci(unittest.TestCase):

    def test_soucet(self):
        self.assertEqual(soucet([1, 2, 3]), 6)
        self.assertEqual(soucet([-1, 0, 1]), 0)
        self.assertEqual(soucet([1, 1, 1]), 3)
        self.assertEqual(soucet([]), 0)  # Prázdný seznam

    def test_soucin(self):
        self.assertEqual(soucin([1, 2, 3]), 6)
        self.assertEqual(soucin([-1, 2, 3]), -6)
        self.assertEqual(soucin([0, 2, 3]), 0)
        self.assertEqual(soucin([]), 0)  # Prázdný seznam

    def test_prumer(self):
        self.assertEqual(prumer([1, 2, 3]), 2)
        self.assertEqual(prumer([-1, 0, 1]), 0)
        self.assertEqual(prumer([1, 1, 1]), 1)
        with self.assertRaises(ValueError):  # Prázdný seznam
            prumer([])

    def test_median(self):
        self.assertEqual(median([1, 2, 3]), 2)
        self.assertEqual(median([1, 3, 2]), 2)
        self.assertEqual(median([1, 1, 2]), 1)
        self.assertEqual(median([1]), 1)  # Jeden prvek
        with self.assertRaises(ValueError):  # Prázdný seznam
            median([])


if __name__ == '__main__':
    unittest.main()
