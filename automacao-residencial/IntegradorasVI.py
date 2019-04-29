import mysql.connector
import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)
gpio.setwarnings (False)
pinos = (13, 12, 11, 7, 15)
for i in pinos:
    gpio.setup(i,gpio.OUT)

while(1):
    cnx = mysql.connector.connect(user='carlinho', password='123', host='localhost', database='dados')
    cursor = cnx.cursor()
    cursor.execute("SELECT descricao, status FROM acao")
    i=0
    for (descricao,status) in cursor:
        if(status=='1'):
            gpio.output(pinos[i],gpio.LOW)
            print("Rele{} - {}: ligado".format(i,descricao))
        else:
            gpio.output(pinos[i],gpio.HIGH)
            print("Rele{} - {}: desligado".format(i,descricao))
        i=i+1
    print("\n")
    cursor.close()
    cnx.close()
    time.sleep(0.3)
    
gpio.cleanup()