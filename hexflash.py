import serial
from time import sleep
import sys

def sendhex(hexfile):
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600)
    except:
        print "Could not open Serial Port"
    with open(hexfile) as f:
        data = f.read()
        ser.write(data)
        print data
        sleep(0.12)

def main():
    import argparse
    parser = argparse.ArgumentParser('hexflash')
    parser.add_argument('hexfile', help='HEX file to flash')
    args = parser.parse_args()
    sendhex(args.hexfile)

if __name__ == "__main__":
    main()
