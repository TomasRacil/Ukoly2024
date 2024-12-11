import unittest
from SystemKnihovny import Knihovna, Kniha, Ctenar
import datetime
import csv
import os


class TestKniha(unittest.TestCase):
    def test_isbn_validation(self):
        valid_isbn = "9780345391803"
        invalid_isbn = "12345"
        Kniha("Title", "Author", 2000, valid_isbn)
        with self.assertRaises(ValueError):
            Kniha("Title", "Author", 2000, invalid_isbn)


class TestCtenar(unittest.TestCase):
    def test_card_number_validation(self):
        ctenar = Ctenar("Jan", "Novák")
        self.assertGreater(ctenar.cislo_prukazky, 0)
        with self.assertRaises(ValueError):
            ctenar.cislo_prukazky = -1


class TestKnihovna(unittest.TestCase):
    def setUp(self):
        self.knihovna = Knihovna("Městská knihovna")
        self.kniha1 = Kniha("Kniha 1", "Autor 1", 2020, "9780123456789")
        self.kniha2 = Kniha("Kniha 2", "Autor 2", 2021, "9780987654321")
        self.ctenar1 = Ctenar("Jan", "Novák")

    def test_z_csv(self):
        # Create a temporary CSV file for testing
        csv_data = [
            ["Knihovna:Testovaci knihovna"],
            ["typ", "nazev", "autor", "rok_vydani", "isbn", "jmeno", "prijmeni"],
            ["kniha", "Kniha z CSV", "Autor z CSV",
                "2022", "9781234567890", "", ""],
            ["ctenar", "", "", "", "", "Test", "Ctenar"]
        ]
        with open("test_knihovna.csv", "w", newline="") as csvfile:
            writer = csv.writer(csvfile)
            writer.writerows(csv_data)

        knihovna = Knihovna.z_csv("test_knihovna.csv")

        self.assertEqual(knihovna.nazev, "Testovaci knihovna")
        self.assertEqual(len(knihovna.knihy), 1)
        self.assertEqual(len(knihovna.ctenari), 1)
        self.assertEqual(knihovna.knihy[0].nazev, "Kniha z CSV")
        self.assertEqual(knihovna.ctenari[0].jmeno, "Test")

        os.remove("test_knihovna.csv")

    def test_kniha_existuje_decorator(self):
        knihovna = Knihovna("Městská knihovna")
        kniha1 = Kniha("Kniha 1", "Autor 1", 2020, "9780123456789")
        knihovna.pridej_knihu(kniha1)

        knihovna.odeber_knihu("9780123456789")
        self.assertEqual(len(knihovna.knihy), 0)

        with self.assertRaises(ValueError) as context:
            knihovna.odeber_knihu("9780987654321")
        self.assertEqual(str(context.exception),
                         "Kniha s ISBN 9780987654321 neexistuje.")

        knihovna.pridej_knihu(kniha1)
        ctenar1 = Ctenar("Jan", "Novák")
        knihovna.vypujc_knihu("9780123456789", ctenar1)

        with self.assertRaises(ValueError) as context:
            knihovna.vypujc_knihu("9780987654321", ctenar1)
        self.assertEqual(str(context.exception),
                         "Kniha s ISBN 9780987654321 neexistuje.")

        with self.assertRaises(ValueError) as context:
            knihovna.vypujc_knihu("9780123456789", ctenar1)
        self.assertEqual(str(context.exception),
                         "Kniha s ISBN 9780123456789 je již vypůjčena.")

    def test_pridej_knihu(self):
        self.knihovna.pridej_knihu(self.kniha1)
        self.assertEqual(len(self.knihovna.knihy), 1)

    def test_odeber_knihu(self):
        self.knihovna.pridej_knihu(self.kniha1)
        self.knihovna.odeber_knihu("9780123456789")
        self.assertEqual(len(self.knihovna.knihy), 0)
        with self.assertRaises(ValueError):
            self.knihovna.odeber_knihu("NonExistentISBN")

    def test_vyhledej_knihu(self):
        self.knihovna.pridej_knihu(self.kniha1)
        results = self.knihovna.vyhledej_knihu(klicova_slovo="Kniha 1")
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].nazev, "Kniha 1")
        results = self.knihovna.vyhledej_knihu(isbn="9780123456789")
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].nazev, "Kniha 1")
        results = self.knihovna.vyhledej_knihu(klicova_slovo="NonExistent")
        self.assertEqual(len(results), 0)

    def test_registruj_ctenare(self):
        self.knihovna.registruj_ctenare(self.ctenar1)
        self.assertEqual(len(self.knihovna.ctenari), 1)

    def test_zrus_registraci_ctenare(self):
        self.knihovna.registruj_ctenare(self.ctenar1)
        self.knihovna.zrus_registraci_ctenare(self.ctenar1)
        self.assertEqual(len(self.knihovna.ctenari), 0)

    def test_vyhledej_ctenare(self):
        self.knihovna.registruj_ctenare(self.ctenar1)
        results = self.knihovna.vyhledej_ctenare(klicova_slovo="Jan")
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].jmeno, "Jan")
        results = self.knihovna.vyhledej_ctenare(
            cislo_prukazky=self.ctenar1.cislo_prukazky)
        self.assertEqual(len(results), 1)
        self.assertEqual(results[0].jmeno, "Jan")
        results = self.knihovna.vyhledej_ctenare(klicova_slovo="NonExistent")
        self.assertEqual(len(results), 0)

    def test_vypujc_knihu(self):
        self.knihovna.pridej_knihu(self.kniha1)
        self.knihovna.registruj_ctenare(self.ctenar1)
        self.knihovna.vypujc_knihu("9780123456789", self.ctenar1)
        self.assertEqual(len(self.knihovna.vypujcene_knihy), 1)
        self.assertEqual(
            self.knihovna.vypujcene_knihy["9780123456789"][0], self.ctenar1)
        today = datetime.date.today()
        self.assertEqual(
            self.knihovna.vypujcene_knihy["9780123456789"][1], today)
        with self.assertRaises(ValueError):
            self.knihovna.vypujc_knihu(
                "9780123456789", self.ctenar1)

        with self.assertRaises(ValueError):
            self.knihovna.vypujc_knihu("NonExistentISBN", self.ctenar1)

    def test_vrat_knihu(self):
        self.knihovna.pridej_knihu(self.kniha1)
        self.knihovna.registruj_ctenare(self.ctenar1)
        self.knihovna.vypujc_knihu("9780123456789", self.ctenar1)
        self.knihovna.vrat_knihu("9780123456789", self.ctenar1)
        self.assertEqual(len(self.knihovna.vypujcene_knihy), 0)
        with self.assertRaises(ValueError):
            self.knihovna.vrat_knihu("9780123456789", self.ctenar1)


if __name__ == '__main__':
    unittest.main()
