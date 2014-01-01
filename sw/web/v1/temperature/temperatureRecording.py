import time
from datetime import datetime
from temperature import *

def writeTemperature():
	dt = datetime.now()
	t = temperature()
	with open("temperature.csv", "a") as tFile:
		tFile.write('{0},{1}\n'.format(dt,t))

def main():
	while True:
        	writeTemperature()
        	time.sleep(300)

if __name__=="__main__":
        main()

