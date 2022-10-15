

def cifradoVigenere(string1, key):

    """dic = {"a":0, "b":1, "c":2, "d":3, "e":4, "f":5, "g":6, "h":7,
    "i":8, "j":9, "k":10, "l":11, "m":12, ""}"""

    dicc = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
    "l", "m", "n", "ñ", "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z"]

    string2 = ""
    i = 0
    for letter in string1:
        
        if letter == ' ':
            continue

        val = dicc.index(letter)    # Obtenemos valor index
        print("valor val = ", val)
        new_val = (val + dicc.index(key[i])) % 27     #Valor de letra + key modulo 27

        string2 += dicc[new_val]
        i = (i + 1) % len(key)

    return string2


if __name__ == '__main__':

    string1 = "el otro dia fui al parque y comi"
    string2 = "hakunamatata"

    cif = cifradoVigenere(string1, string2)

    print("Mensaje cifrado =", cif)
