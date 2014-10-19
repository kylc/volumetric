import serial
import time

ser = serial.Serial("/dev/ttyUSB0", 38400,
        timeout=None)

data = []

lighted_col = 0
while True:
    ser.write(chr(0x00))
    time.sleep(0.01)

    lighted_col += 1
    for col in range(0, 8):
        for ang in range(0, 36):
            for chan in range(0, 3):
                if lighted_col % 8 == col:
                    ser.write(chr(chan * 30))
                else:
                    ser.write(chr(0))

    print "done"

    time.sleep(2)

ser.close()
