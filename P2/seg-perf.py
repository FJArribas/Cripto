import argparse
import sys

# seg-perf {-P | -I} [-i filein] [-o fileout]
# Método equiprobable -> seguridad perfecta
# Método no equiprobable -> seguridad no perfecta

# Debemos medir empíricamente la probabilidad de:
# p(x = a) al cifrar a, al cifrar b ... al cifrar z

# Otra posibilidad es usar la fórmula de Bayes

# TODO
def equiprobable(string):
    pass



# TODO
def no_equiprobable(string):
    pass



if __name__ == '__main__':

    parser = argparse.ArgumentParser(description="Recibiendo argumentos...")

    parser.add_argument("-P", dest="-P", help="Se utiliza el método equiprobable.")
    parser.add_argument("-I", dest="-I", help="No se utiliza el método equiprobable.")
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
            res = equiprobable (string)

        else:
            res = no_equiprobable (string)
    # Si obtenemos desde la terminal
    else:
        if args["-P"] is not None:
            string = args["-P"] # ??? Es como scanf?
            res = equiprobable (string)

        else:
            string = args["-I"] # ??? Es como scanf?
            res = no_equiprobable (string)

    # La salida consistir´a en las probabilidades Pp(x) de los elementos de texto plano, y las probabilidades
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

    # Si se desea el output en un fichero
    if args["-o"] != "terminal":
        with open(args["-o"], "w") as f:
            print(res)

    # Output por terminal
    else:
        print("Este es el output de la operacion =", res)