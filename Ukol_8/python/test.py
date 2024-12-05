import unittest
from matice import Matice


class TestMatice(unittest.TestCase):

    def test_init(self):
        matice = Matice(3, 2)
        self.assertEqual(matice.n, 3)
        self.assertEqual(matice.m, 2)
        for row in matice.data:
            self.assertEqual(len(row), 2)
            for element in row:
                self.assertTrue(0 <= element <= 9)

        data = [[1, 2], [3, 4]]
        matice = Matice(2, 2, data)
        self.assertEqual(matice.data, data)

    def test_str(self):
        matice = Matice(2, 2, [[1, 2], [3, 4]])
        expected_representation = "1 2\n3 4"
        self.assertEqual(str(matice), expected_representation)

        matice = Matice(0, 0, [])
        self.assertEqual(str(matice), "")

    def test_add(self):
        matice1 = Matice(2, 2, [[1, 2], [3, 4]])
        matice2 = Matice(2, 2, [[5, 6], [7, 8]])
        expected_sum = Matice(2, 2, [[6, 8], [10, 12]])
        self.assertEqual(matice1 + matice2, expected_sum)

        matice3 = Matice(2, 3, [[1, 2, 3], [4, 5, 6]])
        with self.assertRaises(ValueError):
            matice1 + matice3

    def test_mul(self):
        matice1 = Matice(2, 2, [[1, 2], [3, 4]])
        matice2 = Matice(2, 2, [[5, 6], [7, 8]])
        expected_product = Matice(2, 2, [[19, 22], [43, 50]])
        self.assertEqual(matice1 * matice2, expected_product)

        matice3 = Matice(3, 2, [[1, 2], [3, 4], [5, 6]])
        with self.assertRaises(ValueError):
            matice1 * matice3

        expected_product = Matice(3, 2, [[7, 10], [15, 22], [23, 34]])
        self.assertEqual(matice3 * matice1, expected_product)

        expected_scalar_product = Matice(2, 2, [[2, 4], [6, 8]])
        self.assertEqual(matice1 * 2, expected_scalar_product)

    def test_transpozice(self):
        matice = Matice(2, 3, [[1, 2, 3], [4, 5, 6]])
        expected_transpose = Matice(3, 2, [[1, 4], [2, 5], [3, 6]])
        self.assertEqual(matice.transpozice(), expected_transpose)

        matice = Matice(0, 0, [])
        self.assertEqual(matice.transpozice().data, [])


if __name__ == '__main__':
    unittest.main()
