import argparse
from binascii import b2a_hqx
import sys
from uuid import RFC_4122

DICC_ES = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

ABEC_ES = 27

TABLE_ES = {"a":11.96, "b":0.92, "c":2.92, "d":6.87, "e":16.78, "f":0.52,
    "g":0.73, "h":0.89, "i":4.15, "j":0.30, "k":0, "l":8.37, "m":2.12,
    "n":7.01, "o":8.69, "p":2.77, "q":1.53, "r":4.94, "s":7.88,
    "t":3.31, "u":4.80, "v":0.39, "w":0, "x":0.06, "y":1.54, "z":0.15}

DICC_EN = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

ABEC_ES = 26

TABLE_EN = {"a":8.04, "b":1.54, "c":3.06, "d":3.99, "e":12.51, "f":2.30,
    "g":1.96, "h":5.49, "i":7.26, "j":0.16, "k":0.67, "l":4.14, "m":2.53,
    "n":7.09, "o":7.60, "p":2.00, "q":0.11, "r":6.12, "s":6.54,
    "t":9.25, "u":2.71, "v":0.99, "w":1.92, "x":0.19, "y":1.73, "z":0.19}

def euclides(values):

    b = values[0]
    for a in values[1:]:

        print("valores antes de euclides", a, b)

        q = a % b

        # Algoritmo de euclides
        while q != 0:

            q =  a % b
            a = b
            b = q

            print("a after iteration", a)

        # Para seguir calculando mcd
        b = a
        print("mcd por ahora", a)

    return a


def ic_key_size(string1, size):

    # Para guardar el numero de elementos que se repiten de cada uno
    c = []
    ic = []

    # Iteramos por el numero de caracteres utilizados
    for i in range(0, size):

        print("Iteracion numero",i)

        # Obtenemos el numero de cada uno de ellos
        c.append(string1.count(string1[i]))

        # Obtenemos el indice de coincidencia
        ic.append(c[i]*(c[i]-1) / (ABEC_ES * (ABEC_ES-1)))

        print("Valores de count del elemento", string1[i], c[i])

    return ic
        
        
def kasiki_key_size(string1, size):

    # Obtenemos el valor de la coincidencia a buscar
    ic = string1[:size]

    print("Incidencia buscada", ic)

    # Buscamos distancias entre las coincidencias
    num = []
    substring = string1[size:]
    idx = 1
    val = 0
    while idx != -1:
    
        # Obtenemos indice de las coincidencias
        idx = substring.find(ic)

        # Si no hay mas coincidencias
        if idx == -1:
            continue

        # Teniendo encuenta size de clave buscada
        idx += size

        # Valor que acumula los indexes para el posterior mcd
        val += idx

        print("Index de coincidencia encontrado", idx)
        
        # Guarda las distancias entre las coincidencias
        num.append(val)

        print("substring antes de update", substring)

        # Reducimos substring para buscar la proxima coincidencia
        substring = substring[idx:]

        print("substring tras update", substring)


    # Bucle en el que calcula el mcd de los valores obtenidos
    mcd = euclides(num)

    return mcd


## TO DO o hacer una funcion que haga combinatorio
## o descubrir funcion python que haga combinatorio



if __name__ == '__main__':

    ## TODO que al no poner nada al ejecutar te explique que hacer
    ## TO DO cambiar los args, el de -l esta mal

    parser = argparse.ArgumentParser(description="Recibiendo argumentos")

    parser.add_argument("-l", dest="-l", help="Decide la longitud de n-grama buscado")
    parser.add_argument("-i", dest="-i", nargs="?", help="Es para especificar un archivo como input")
    parser.add_argument("-o", dest="-o", nargs="?", help="Es para especificar un archivo para el output")

    args = vars(parser.parse_args())

    if args["-l"] is None:
        sys.exit()

    # Obtenemos el texto al que aplicar el criptoanalisis
    if args["-i"] is None:
        string = args["-l"]

    ### TO DO implementar lectura archivo
    else:
        print("exit")
        sys.exit()
        """with open(args["-i"], "r") as f:
            string = f.read()"""

    print("string obtained", string)

    n = 3
    # n es el tamano de la coincidencia buscada
    num = kasiki_key_size(string, n)

    print("Este es el mcd y probable tamano de clave", num)

    ## TO DO Obtener tamano de clave con indice de coincidencias
    
    n = 5
    print("\n\n")
    lista = ic_key_size(string, n)

    print("lista recibida", lista)

    print("Este es el indice de coincidencia de cada uno")
    for e in lista:
        print(e)
