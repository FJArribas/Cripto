import argparse
import sys

DICC = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Recibiendo argumentos")

    parser.add_argument("-l", dest="-l", help="Decide la longitud de n-grama buscado")
    parser.add_argument("-i", dest="-i", nargs="?", default="terminal", help="Es para especificar un archivo como input")
    parser.add_argument("-o", dest="-o", nargs="?", default="terminal", help="Es para especificar un archivo para el output")

    args = vars(parser.parse_args())

    