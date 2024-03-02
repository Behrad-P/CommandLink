
"""
/**
 * @author  Behrad Pourhadi
 * @email   behradp32@gmail.com
 * @ide     Visual Studio Code
 * @brief   pyArduino (.py) 
*/
"""

from serial import Serial
import time

arduino = Serial(port= 'COM9' ,baudrate = 9600, timeout = 2)

time.sleep(2)

pwm = 0
base_cmd = "pwm .9 = "

arduino.write(b'pwmfre .9 = 120')
data = arduino.readline()
print(data)
if(data != b'OK\r\n'):
    usercmd = input('terminate? yes(y) / no(any key): ')
    if usercmd == 'y':
        exit()

while(True):
    pwm += 5
    if pwm > 100:
        pwm = 0

    pwmstr = str(pwm)
    cmd = base_cmd + pwmstr
    arduino.write(bytes(cmd, 'UTF-8'))
    data = arduino.readline()
    if(data != b'OK\r\n'):
        print(data)
        usercmd = input('terminate? yes(y) / no(any key): ')
        if usercmd == 'y':
            exit()

    time.sleep(0.1)
