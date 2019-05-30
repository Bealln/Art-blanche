
import serial
import time



while 1:
    with serial.Serial('/dev/tty.usbmodem14601', 9600, timeout = 1) as arduino:
        time.sleep(2)
        message = '<+50,-20>'
        command = message.encode()
        
        arduino.write(command)  
        time.sleep(1.5)
        
        start = time.time()
        while (time.time() - start) < 200:
            line = arduino.readline().decode()
            print(line)
