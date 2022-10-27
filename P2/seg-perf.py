import argparse
import sys
from random import seed
from random import random

DICC_ES = "abcdefghijklmnñopqrstuvwxyz"

ABEC_ES = 27

# Método equiprobable -> seguridad perfecta
# Método no equiprobable -> seguridad no perfecta

# Debemos medir empíricamente la probabilidad de:
# p(x = a) al cifrar a, al cifrar b ... al cifrar z

# Otra posibilidad es usar la fórmula de Bayes


## TO DO? Al ser equiprobable no puedes ejecutarlo varias
## veces porque se repite la generacion de clave. Cambiarlo?
def cipher_cesar(string, size, equi):

    dic = DICC_ES

    cipher = ''

    # Con clave equiprobable
    if equi:

        # Obtenemos la key pseudo-generada
        key = equiprobable(size)
        #print(key)

    # Con clave no equiprobable
    else:

        # Obtenemos la clave no random
        key = no_equiprobable(size)

    i = 0
    length = len(key)
    for ch in string:
        
        # Obtenemos valor a cifrar
        mod = i % length

        # Ciframos con la clave de forma iterativa
        ciph = (dic.find(ch) + key[mod]) % ABEC_ES
        cipher += dic[ciph]

        i += 1

    return cipher

def equiprobable(size):

    # Generamos semilla para los valores pseudoaleatorios
    key = []
    seed(1)
    for i in range(0, size):

        # Genera clave y redondea para ser integer
        key.append(round(random()*27))

    return key


def no_equiprobable(size):
    
    # Generamos semilla para los valores pseudoaleatorios
    key = []
    seed(1)
    for i in range(0, size):

        # Generamos claves con probabilidades modificadas
        if i%2 == 0:
            key.append(17)

        elif i%3 == 0:
            key.append(6)

        else:
            # Genera clave y redondea para ser integer
            key.append(round(random()*27))

    return key


# TODO
# Analiza el texto cifrado, y devuelve una String con el formato descrito a continuación:

# La salida consistira en las probabilidades Pp(x) de los elementos de texto plano, y las probabilidades
# condicionadas Pp(x|y) para cada elemento de texto plano y de texto cifrado, con el siguiente formato:
#
# Pp(A) = %lf
# Pp(B) = %lf
# ...
# Pp(Z) = %lf
#
# Pp(A|A) = %lf Pp(A|B) = %lf ... Pp(A|Z) = %lf
# Pp(B|A) = %lf Pp(B|B) = %lf ... Pp(B|Z) = %lf
# ...
# Pp(Z|A) = %lf Pp(Z|B) = %lf ... Pp(Z|Z) = %lf

def analisis (string, cif):
    ret = ""

    # Eliminamos todo lo que no sea una letra
    regex = re.compile('[^a-zA-Z]')
    cadena = regex.sub('', string)
    # print (string)                                # DEBUG
    # print (cadena)                                # DEBUG

    # Diccionario de frecuencias con forma: ({'a': 2, 'b': 1, 'c': 1, 'd': 1, ...})
    frecuencias_txt = Counter(cadena.lower())
    frecuencias_cif = Counter(cif)

    # for i in frecuencias:
        # print (i, frecuencias[i])                 # DEBUG

    # P(X)
    # Pp(A), Pp(B), ..., Pp(Z)
    for i in frecuencias_txt:
        ret += "Pp(" + i + ") = " + str (frecuencias_txt[i] / len(cadena)) + "\n"
        # print (i, frecuencias[i] / len(cadena))   # DEBUG

    # Ocurrencias P(X, Y)

	# Pp(X|Y) = P(X, Y)/Pp(Y)
	for i in frecuencias_txt:
		for j in frecuencias_txt:
			# Se divide por Pp(Y)
			# PpXY[i][j] = PpXY[i][j]/Py[j];

			# ret += 

# seg-perf {-P | -I} [-i filein] [-o fileout]
if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Recibiendo argumentos...")

    parser.add_argument("-P", dest="-P", help="Se utiliza el método equiprobable.")
    parser.add_argument("-I", dest="-I", help="No se utiliza el método equiprobable.")
    parser.add_argument("-s", dest="-s", nargs="+", type=int)
    parser.add_argument("-i", dest="-i", nargs="?", default="terminal", help="Especifica un archivo como input.")
    parser.add_argument("-o", dest="-o", nargs="?", default="terminal", help="Especifica un archivo como output.")

    args = vars(parser.parse_args())

    if args["-P"] is None and args["-I"] is None:
        print("Es necesario especificar si se usa un método equiprobable o uno no equiprobable.")
        sys.exit()

    if args["-P"] is not None and args["-I"] is not None:
        print("Es necesario especificar si se usa un método equiprobable o uno no equiprobable.")
        sys.exit()

    # Si obtenemos texto desde un fichero
    if args["-i"] != 'terminal':
        
        # Leemos el fichero
        with open(args["-i"], "r") as f:
            string = f.read()

        if args["-P"]:
            res = cipher_cesar (string, size[0], True)

        else:
            res = cipher_cesar (string, size[0], False)
    # Si obtenemos desde la terminal
    else:
        # Obtenemos size de clave a usar
        size = args["-s"]

        if args["-P"] is not None:
            string = args["-P"] # ??? Es como scanf?
            res = cipher_cesar (string, size[0], True)

        else:
            string = args["-I"] # ??? Es como scanf?
            res = cipher_cesar (string, size[0], False)

    res = analisis (string, cif)

    # Si se desea el output en un fichero
    if args["-o"] != "terminal":
        with open(args["-o"], "w") as f:
            print(res)

    # Output por terminal
    else:
        print("Este es el output de la operacion =", res)