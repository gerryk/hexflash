import serial
from time import sleep
import sys

def sendhex(hexfile):
    try:
        ser = serial.Serial('/dev/ttyACM0', 9600)
    except:
        print "Could not open Serial Port"
    with open(hexfile) as f:
        for data in f:
            # data = "<" + data + ">"
            #ser.write(data.encode())
            ser.write(data)
            print repr(data)
            sleep(1)
            print repr(ser.readline())

def main():
    import argparse
    parser = argparse.ArgumentParser('hexflash')
    parser.add_argument('hexfile', help='HEX file to flash')
    args = parser.parse_args()
    sendhex(args.hexfile)

if __name__ == "__main__":
    main()
