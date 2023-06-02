#include <SoftwareSerial.h>

SoftwareSerial BT(10,11);

#define led1 5
#define led2 6
#define in1 A2
#define in2 A3

float lectura, signal1, signal2;
float voltaje1, voltaje2;
int coma1, n, led, i=0;
String datos, numero, indice;

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(in1, INPUT);
  pinMode(in2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  signal1 = analogRead(A2);
  signal2 = analogRead(A3);
  voltaje1 = ((signal1/1023)*5000);
  voltaje2 = ((signal2/1023)*5000);
  Serial.println(i);
  BT.print(voltaje1/10);
  BT.print(',');
  BT.print(voltaje2/10);
  BT.println("\n");
  delay(100);

  if(BT.available()>0){
    datos = BT.readString();
    coma1 = datos.indexOf(',');
    indice = datos.substring(0, coma1);
    numero = datos.substring(coma1+1);
    led = numero.toInt();
    n = indice.toInt();
    if(n==1){analogWrite(led1, led);}
    if(n==2){analogWrite(led2, led);}
    delay(100);
  }
  i++;
}
