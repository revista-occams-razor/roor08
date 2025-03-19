from time import time, ctime
from os import uname

print ('Ejecutandonos en un sistema', uname().sysname, uname().machine)
print ('Hoy es ', ctime(time()));
