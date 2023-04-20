/* Universidad de Colima
 *  Facultad de Ingeniería Electromecánica
 *  Ingeniería en Software
 *  Sistemas Embebidos
 *  Alumna: Ximena Manzo Castrejón
 *  4to Semestre Grupo D
 *  Jueves 20 de Abril de 2023
*/

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "DHT.h"

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

const byte filas = 4;
const byte columnas = 4;
char teclas[filas][columnas] = {{'1','2','3','A'},
                                {'4','5','6','B'},   
                                {'7','8','9','C'},
                                {'*','0','#','D'}};                         
byte filasPins[filas] = { 9, 8, 7, 6 };
byte colsPins[columnas] = { 5, 4, 3, 2 }; 

Keypad kpd = Keypad( makeKeymap(teclas), filasPins, colsPins, filas, columnas );

//Sensor
#define DHTPIN 11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int VERDE = 10;
int BLANCO = 12;

int dinero=0;

byte cora[] = {
  B00000,
  B00000,
  B01010,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

void limpiarLineaCero(){
  lcd.setCursor(0, 0);
  for(int i=0; i<16; i++){
    lcd.print(" ");
  }
}

void gracias(){
  void limpiarLineaCero();
  lcd.setCursor(0,0);
           //0123456789012345
  lcd.print("Gracias x Compra");
  delay(3000);
}

void setup(){
  Serial.begin(9600);
  dht.begin();
  lcd.clear();
  lcd.begin(16, 2);
  lcd.createChar(1, cora);
  lcd.setCursor(0, 0);
  lcd.print("Examen de Xime");
  lcd.setCursor(0, 1);
  lcd.print("Manzo Cast 4D");
  lcd.setCursor(14, 0);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  pinMode(VERDE, OUTPUT);
  pinMode(BLANCO, OUTPUT);

  delay(2500);
  lcd.clear();
}

void loop() {
  // T E M P E R A T U R A
  float T = dht.readTemperature();
  lcd.setCursor(0, 1);
  lcd.print("Temp: "); 
  lcd.print(T);
  lcd.print((char)223);
  lcd.print("C");

  // P A G O
  limpiarLineaCero();
  lcd.setCursor(0, 0);
           //0123456789012345
  lcd.print("Dinero: $");
  lcd.setCursor(9,0);
  lcd.print(dinero);
  while (dinero < 10){
    char key = kpd.getKey();
    switch(key){
      case '1':
        dinero = dinero + 1;
        break;
      case '2':
        dinero = dinero + 2;
        break;
      case '5':
        dinero = dinero + 5;
        break;
      case '0':
        dinero = dinero + 10;
        break;
    }
    lcd.setCursor(9,0);
    lcd.print(dinero);
  }

  /*/Cambio
  if(dinero==10){
    dinero = dinero - 10;
  }
  if(dinero>=10){
    delay(2000);
    dinero = dinero - 10;
    limpiarLineaCero();
    lcd.setCursor(0,0);
    lcd.print(">>Cambio: $");
    lcd.print(cambio);
  }*/


  // B E B I D A
  if(dinero>9){
    delay(2000);
    limpiarLineaCero();
    lcd.setCursor(0,0);
             //0123456789012345
    lcd.print("Selecc. bebida");
    int aux=0;
    while(aux!=1){
      char key2 = kpd.getKey();
      switch(key2){
        case 'A':
          limpiarLineaCero();
          lcd.setCursor(0,0);
                   //0123456789012345
          lcd.print("Sale CocaCola...");
          digitalWrite(VERDE, HIGH);
          delay(10000);
          digitalWrite(VERDE, LOW);
          digitalWrite(BLANCO, HIGH);
          gracias();
          digitalWrite(BLANCO, LOW);
          aux=1;
          break;
        case 'B':
          limpiarLineaCero();
          lcd.setCursor(0,0);
                   //0123456789012345
          lcd.print("Sale Sprite...");
          digitalWrite(VERDE, HIGH);
          delay(10000);
          digitalWrite(VERDE, LOW);
          digitalWrite(BLANCO, HIGH);
          gracias();
          digitalWrite(BLANCO, LOW);
          aux=1;
          break;
        case 'C':
          limpiarLineaCero();
          lcd.setCursor(0,0);
                   //0123456789012345
          lcd.print("Sale Sidral...");
          digitalWrite(VERDE, HIGH);
          delay(10000);
          digitalWrite(VERDE, LOW);
          digitalWrite(BLANCO, HIGH);
          gracias();
          digitalWrite(BLANCO, LOW);
          aux=1;
          break;
        case 'D':
          limpiarLineaCero();
          lcd.setCursor(0,0);
                   //0123456789012345
          lcd.print("Sale Fanta...");
          digitalWrite(VERDE, HIGH);
          delay(10000);
          digitalWrite(VERDE, LOW);
          digitalWrite(BLANCO, HIGH);
          gracias();
          digitalWrite(BLANCO, LOW);
          aux=1;
          break;
      }
    }
  }
  limpiarLineaCero();
  dinero=dinero-10;
  delay(500);
}
