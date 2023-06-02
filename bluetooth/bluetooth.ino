#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth

const int ledPin = 12;
const int relPin = 9;
const int pinLM35 = 2;

void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  
  pinMode(16, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(relPin, OUTPUT);
  digitalWrite(relPin, HIGH);
}
 
void loop()
{
  if (BT.available()) {
    char command = BT.read();
    int lectura = analogRead(pinLM35);
    float voltaje = lectura * (5000 / 1023.0);
    float tempC = voltaje / 10;
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Encender el LED
      digitalWrite(relPin, LOW);
      Serial.println("Encendido");
      BT.print("Entrada: ");
      BT.print(lectura);
      BT.print(" - Volts: ");
      BT.print(voltaje/1000);
      BT.print(" - Temperatura: ");
      BT.print(tempC);
      BT.print("°C \n");
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); // Apagar el LED
      digitalWrite(relPin, HIGH);
      Serial.println("Apagado");
      BT.print("Entrada: ");
      BT.print(lectura);
      BT.print(" - Volts: ");
      BT.print(voltaje/1000);
      BT.print(" - Temperatura: ");
      BT.print(tempC);
      BT.print("°C \n");
    }
  }
}
