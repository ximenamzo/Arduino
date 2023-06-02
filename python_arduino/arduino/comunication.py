import serial
import serial.tools.list_ports  # Permite reconocer puertos
from threading import Thread, Event  # Crear subprocesos
from tkinter import StringVar  # Recibir datos de arduino en string

#https://www.youtube.com/watch?v=DJY9TFxrYbM

# Codigo para la comunicacion serial
class Comunicacion():
    # Método constructor
    def __init__(self, *args):
        self.datos_recibidos = StringVar()  # Es string

        self.arduino = serial.Serial()  # Objeto Arduino
        self.arduino.port = 'COM10'
        self.arduino.timeout = 0.5

        self.baudrates = ['1200', '2400', '4800', '9600', '19200', '38400', '115200']
        self.puertos = []

        self.senial = Event()
        self.hilo = None

    def puertos_disponibles(self):
        self.puertos = [port.device for port in serial.tools.list_ports.comports()]

    def conexion_serial(self):
        try:
            self.arduino.open()
        except:
            pass
        if self.arduino.is_open:
            self.iniciar_hilo()
            print('Conectado')

    def enviar_datos(self, data):
        try:
            if self.arduino.is_open:
                self.datos = str(data) + "\n"
                self.arduino.write(self.datos.encode())
            else:
                print('Error: Puerto serie no abierto (comunication)')
        except Exception as e:
            print('Error al enviar datos:', str(e))

    def leer_datos(self):
        try:
            while self.senial.isSet() and self.arduino.is_open:
                data = self.arduino.readline().decode("utf-8").strip()
                if len(data) > 1:
                    self.datos_recibidos.set(data)
        except TypeError:
            pass

    def iniciar_hilo(self):
        # Objeto Hilo
        self.hilo = Thread(target = self.leer_datos)
        self.hilo.setDaemon(1)
        self.senial.set()
        self.hilo.start()

    def stop_hilo(self):
        if(self.hilo is not None):
            self.senial.clear()
            self.hilo.join()
            self.hilo = None

    def desconectar(self):
        self.arduino.close()
        self.stop_hilo()

