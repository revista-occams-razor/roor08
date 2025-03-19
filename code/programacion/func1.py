import sys
import mimod

def foo (s, a, b):
    print ("cadena: " + s)
    #mimod.test1 (123, 321)
    # print (c);
    c = mimod.test1 ("Adios Mundo", 1234, 4321)
    print (c)
    return a + b

