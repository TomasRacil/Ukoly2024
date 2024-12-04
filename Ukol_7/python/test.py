import unittest
import random
from matice import vytvor_matici, soucet_matic, nasobeni_matic, transpozice_matice, reprezentace_matice


class TestMatice(unittest.TestCase):

    def test_vytvor_matici(self):
        matice = vytvor_matici(3, 2)
        self.assertEqual(len(matice), 3)
        self.assertEqual(len(matice[0]), 2)
        for row in matice:
            for element in row:
                self.assertTrue(0 <= element <= 9)

        empty_matrix = vytvor_matici(0, 0)
        self.assertEqual(empty_matrix, [])

        empty_matrix_rows = vytvor_matici(0, 5)
        self.assertEqual(empty_matrix_rows, [])

        empty_matrix_cols = vytvor_matici(5, 0)
        self.assertEqual(empty_matrix_cols, [[], [], [], [], []])

    def test_reprezentace_matice(self):
        matice = [[1, 2], [3, 4]]
        expected_representation = "1 2\n3 4\n"
        self.assertEqual(reprezentace_matice(matice), expected_representation)

        self.assertEqual(reprezentace_matice([]), "")

    def test_soucet_matic(self):
        matice1 = [[1, 2], [3, 4]]
        matice2 = [[5, 6], [7, 8]]
        expected_sum = [[6, 8], [10, 12]]
        self.assertEqual(soucet_matic(matice1, matice2), expected_sum)

        matice3 = [[1, 2, 3], [4, 5, 6]]
        self.assertIsNone(soucet_matic(matice1, matice3))

        self.assertIsNone(soucet_matic([], matice1))
        self.assertIsNone(soucet_matic(matice1, []))
        self.assertEqual(soucet_matic([], []), [])

    def test_nasobeni_matic(self):
        matice1 = [[1, 2], [3, 4]]
        matice2 = [[5, 6], [7, 8]]
        expected_product = [[19, 22], [43, 50]]
        self.assertEqual(nasobeni_matic(matice1, matice2), expected_product)

        matice3 = [[1, 2], [3, 4], [5, 6]]
        self.assertIsNone(nasobeni_matic(matice1, matice3))
        self.assertIsNone(nasobeni_matic(matice3, matice1))

        self.assertEqual(nasobeni_matic([], []), [])
        self.assertIsNone(nasobeni_matic(matice1, []))
        self.assertIsNone(nasobeni_matic([], matice1))

    def test_transpozice_matice(self):
        matice = [[1, 2, 3], [4, 5, 6]]
        expected_transpose = [[1, 4], [2, 5], [3, 6]]
        self.assertEqual(transpozice_matice(matice), expected_transpose)

        self.assertEqual(transpozice_matice([]), [])
        self.assertEqual(transpozice_matice([[]]), [[]])


if __name__ == '__main__':
    unittest.main()
