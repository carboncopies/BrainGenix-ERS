import random
from random import randint

number = 1000000
file = "Source/LargeVerts.h"

def rf():
	return str( (randint(0,10000)-5000)/10000 )

vertstr = "const std::vector<Vertex> Vertices_ = {\n"
for x in range(number):
	vertstr += ('{{' + rf() + 'f,' + rf() + 'f}, {' + rf()  + 'f,' + rf() + 'f,' + rf() + 'f}},\n')

vertstr = vertstr[:-2]
vertstr += "\n};\nconst std::vector<uint32_t> Indices_ = {\n"

maxint = number
for x in range(number):
	vertstr += (str(randint(0,maxint)) + ',' + str(randint(0,maxint)) + ',' + str(randint(0,maxint)) + ',\n')

vertstr = vertstr[:-2]
vertstr += '\n};'

with open(file, 'w') as f:
	f.write(vertstr)