import argparse
import sys

DICC = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

def cifradoVigenere(string1, key):

    # Ponemos todas las letras en lower case
    string1.lower()

    string2 = ""
    i = 0
    for letter in string1:
        
        # Evitamos los espacios
        if letter == ' ':
            continue

        # Obtenemos valor index
        val = DICC.index(letter)

        #Valor de letra + key modulo 27
        new_val = (val + DICC.index(key[i])) % 27

        # Vamos añadiendo valores a solucion  
        string2 += DICC[new_val]
        
        # Iteramos por toda la clave infinitivamente
        i = (i + 1) % len(key)

    return string2

def descifradoVigenere(string1, key):

    # Ponemos todas las letras en lower case
    string1.lower()

    string2 = ""
    i = 0
    for letter in string1:
        
        # Evitamos los espacios
        if letter == ' ':
            continue

        # Obtenemos valor index
        val = DICC.index(letter)

        #Valor de letra + key modulo 27
        new_val = (val - DICC.index(key[i])) % 27

        # Vamos añadiendo valores a solucion  
        string2 += DICC[new_val]
        
        # Iteramos por toda la clave infinitivamente
        i = (i + 1) % len(key)

    return string2


#### TO DO testear que funciona con lectura de archivos

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Recibiendo argumentos")

    parser.add_argument("-C", dest="-C", help="Cifra la string que pases con Cifrado Vigenere")
    parser.add_argument("-D", dest="-D", help="Descifra la string que le pases")
    parser.add_argument("-k", dest="-k", help="Pasas la clave a utilizar para cifrar o descifrar")
    parser.add_argument("-i", dest="-i", nargs="?", default="terminal", help="Es para especificar un archivo como input")
    parser.add_argument("-o", dest="-o", nargs="?", default="terminal", help="Es para especificar un archivo para el output")

    args = vars(parser.parse_args())

    # Control de errores
    if args["-k"] is None:
        print("Tienes que especificar una clave")
        sys.exit()

    if args["-C"] is None and args["-D"] is None:
        print("Tienes que especificar si cifrar o descifrar")
        sys.exit()

    if args["-C"] is not None and args["-D"] is not None:
        print("Tienes que especificar si cifrar o descifrar")
        sys.exit()

    # Obtenemos la clave
    key = args["-k"]

    # Si obtenemos texto cifrado/descifrado de un fichero
    if args["-i"] != 'terminal':
        
        #Leemos el fichero con el texto a cifrar/descifrar
        with open(args["-i"], "r") as f:
            string = f.read()

        # Si queremos cifrar
        if args["-C"]:      

            # Llamamos a la funcion con la string a cifrar y la clave
            cif = cifradoVigenere(string, key)

        else:

            # Llamamos a la funcion con la string a descifrar y la clave
            cif = descifradoVigenere(string, key)

    # Si obtenemos texto cifrado/descifrado de terminal
    else:

        # Si queremos cifrar
        if args["-C"] is not None:      
                
            # Obtenemos el texto a cifrar
            string = args["-C"]

            # Llamamos a la funcion con la string a cifrar y la clave
            cif = cifradoVigenere(string, key)

        else:

            # Obtenemos el texto a descifrar
            string = args["-D"]

            # Llamamos a la funcion con la string a descifrar y la clave
            cif = descifradoVigenere(string, key)
        
    # Si quiere el output en un fichero
    if args["-o"] != "terminal":

        # Metemos solucion en fichero
        with open(args["-o"], "w") as f:
            print(cif)

    # Output por terminal
    else:
        print("Este es el output de la operacion =", cif)
