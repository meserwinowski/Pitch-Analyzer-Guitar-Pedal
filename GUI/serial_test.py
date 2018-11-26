# -*- coding: utf-8 -*-
"""
Created on Sun Nov 18 23:42:06 2018

@author: Troy
"""

import time
import serial

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM5',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS
)

ser.isOpen()

print ('Enter your commands below.\r\nInsert "exit" to leave the application.')

input_s=1
while 1 :
    # get keyboard input
    input_s = input(">> ")
        # Python 3 users
        # input = input(">> ")
    if input_s == 'exit':
        ser.close()
        exit()
    else:
        # send the character to the device
        # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
        ser.write(str.encode(input_s))
        out = ''
        # let's wait one second before reading output (let's give device time to answer)
        time.sleep(1)
        while ser.inWaiting() > 0:
            out += (ser.read(1)).decode("utf-8")

        if out != '':
            print (">>" + out)