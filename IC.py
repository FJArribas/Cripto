import argparse
import sys

DICC = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

TABLE = {"a":11.96, "b":0.92, "c":2.92, "d":6.87, "e":16.78, "f":0.52,
    "g":0.73, "h":0.89, "i":4.15, "j":0.30, "k":0, "l":8.37, "m":2.12,
    "n":7.01, "o":8.69, "p":2.77, "q":1.53, "r":4.94, "s":7.88,
    "t":3.31, "u":4.80, "v":0.39, "w":0, x:0.06, "y":1.54, "z":0.15}


def kasiki(string1, size):

    ic = ""

    # Obtenemos el valor de la coincidencia a buscar
    for i in range(size):
        ic += string[i]

    # Buscamos distancias entre las coincidencias
    num = []
    substring = string1[size:]
    while idx != 0:
    
        # Obtenemos indice de las coincidencias
        idx = substring.find("ic")
        num.append(idx)

        # Reducimos substring para buscar la proxima coincidencia
        substring = string1[idx:]

    return num



if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Recibiendo argumentos")

    parser.add_argument("-l", dest="-l", help="Decide la longitud de n-grama buscado")
    parser.add_argument("-i", dest="-i", nargs="?", default="terminal", help="Es para especificar un archivo como input")
    parser.add_argument("-o", dest="-o", nargs="?", default="terminal", help="Es para especificar un archivo para el output")

    args = vars(parser.parse_args())

    if args["-l"] is None:
        sys.exit()

    # Obtenemos el texto al que aplicar el criptoanalisis
    if args["-i"] is None:
        string = args["-l"]
    else:
        with open(args["-i"], "r") as f:
            string = f.read()

    n = 3
    # n es el tamano de la coincidencia buscada
    num = kasiki(string, n)

    # Ahora hay que obtener el mcd de la distancia de valores
    # en num



