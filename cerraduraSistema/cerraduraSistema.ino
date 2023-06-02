#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

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

char mp[7] = {'0', '7', '0', '5', '0', '3'};
char mp2[7];
char pw[5];
char pw2[5];
boolean cerradura=false;
boolean sistema=false;
byte value;

const int VERDE=10;
const int ROJO=12;
int i;


/////////////////////////////////////////////////////////

void ingresaSistema(){
  char key = kpd.getKey();
  key = NO_KEY;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Contrasena");
  lcd.setCursor(0, 1);
  lcd.print("=> ");
  leerPW();
  comparaPW();
  Serial.println(pw);
  Serial.println(pw2);
  Serial.println(sistema);
  delay(500);
  if(sistema == true){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Contra correcta!");  
    lcd.setCursor(0, 1);
    lcd.print("Ingresando...");
    sistema = true;
    digitalWrite(VERDE, HIGH);
    delay(6000);
    sistema = false;
    digitalWrite(VERDE, LOW);
    loop();
  }else if(sistema == false){
      digitalWrite(ROJO, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Contrasena...");  
      lcd.setCursor(0, 1);
      lcd.print("INCORRECTA! X(");
      delay(3000);
      digitalWrite(ROJO, LOW);
      loop();
  }
}

void leerPW(){
  char key;
  int i = 0;
  while (i < 4){
    key = kpd.getKey();
    if (key != NO_KEY){
      if(isDigit(key)){
        lcd.setCursor(i+4, 1);
        lcd.write(key);
        pw2[i] = key;
        i++;
      }else{
        delay(200);
        break;
      }
    } 
  }
  delay(500);
}

void comparaPW(){
  delay(100);
  sistema = false;
  for(int i=0; i<4; i++){
    if(pw2[i] == pw[i]){
      sistema = true;
    }else{
      sistema = false;
      break;
    }
  }
}

void abrirConfig(){
  char key = kpd.getKey();
  key = NO_KEY;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Master password");
  lcd.setCursor(0, 1);
  lcd.print("=> ");
  leerMP();
  comparaMP();
  Serial.println(mp);
  Serial.println(mp2);
  Serial.println(cerradura);
  delay(500);
  if(cerradura == true){
    digitalWrite(VERDE, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MP correcta!!");  
    lcd.setCursor(0, 1);
    lcd.print("Ingresando...");
    cerradura = true;
    delay(1500);
    cerradura = true;
    menuConfig();
  }else if(cerradura == false){
      digitalWrite(ROJO, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Contrasena...");  
      lcd.setCursor(0, 1);
      lcd.print("INCORRECTA! X(");
      delay(1500);
      digitalWrite(ROJO, LOW);
      loop();
  }
}

void leerMP(){
  char key;
  int i = 0;
  while (i < 6){
    key = kpd.getKey();
    if (key != NO_KEY){
      if(isDigit(key)){
        lcd.setCursor(i+4, 1);
        lcd.write(key);
        mp2[i] = key;
        i++;
      }else{
        delay(200);
        break;
      }
    }
  }
  delay(500);
}

void comparaMP(){
  delay(100);
  cerradura = false;
  for(int i=0; i<6; i++){
    if(mp2[i] == mp[i]){
      cerradura = true;
    }else{
      cerradura = false;
      break;
    }
  }
}

void menuConfig(){
  lcd.clear();
  lcd.setCursor(0, 0);
           //1234567812345678
  lcd.print("A) Nueva contra");
  lcd.setCursor(0, 1);
  lcd.print("B) Borrar contra");
  int aux=0;
  while(aux!=1){
    char key2 = kpd.getKey();
    switch(key2){
      case 'A':
        // N U E V A   C O N T R A 
        nuevaContra();
        aux=1;
        break;
      case 'B':
        // B O R R A R   C O N T R A
        borrarContra();
        aux=1;
        break;
    }
  }
  delay(500);
}

void nuevaContra(){
  Serial.println("Nueva Contra");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nueva contra");
  lcd.setCursor(0, 1);
  lcd.print("=> ");
  leerContra();
  Serial.println(pw);
  delay(500);
  digitalWrite(VERDE, LOW);
  loop();
}

void leerContra(){
  char key;
  int i = 0;
  while (i < 4){
    key = kpd.getKey();
    if (key != NO_KEY){
      if(isDigit(key)){
        lcd.setCursor(i+4, 1);
        lcd.write(key);
        pw[i] = key;
        i++;
      }else{
        delay(200);
        break;
      }
    }
  }
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
           //1234567812345678
  lcd.print("Actualizacion");
  lcd.setCursor(0, 1);
  lcd.print("exitosa...");
  delay(2000);
}

void borrarContra(){
  Serial.println("Borra Contra");
  while (i < 4){
    pw[i] = ' ';
    i++;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
           //1234567812345678
  lcd.print("Contra eliminada");
  lcd.setCursor(0, 1);
  lcd.print("correctamente...");
  delay(2000);
  digitalWrite(VERDE, LOW);
  loop();
}

////////////////////////////////////////////
void setup(){
  Serial.begin(9600);
  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("LCD de Xime");
  lcd.setCursor(0, 1);
  lcd.print("Bienvenid@!");

  pinMode(VERDE, OUTPUT);
  pinMode(ROJO, OUTPUT);

  delay(2500);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
           //1234567812345678
  lcd.print("A) Ir al Sistema");
  lcd.setCursor(0, 1);
  lcd.print("B) Configuracion");
  char key = kpd.getKey();
  switch(key){
    case 'A':
      // P A N T A L L A   I N I C I A L
      ingresaSistema();
      break;
    case 'B':
      // E N T R A R   A L   S I S T E M A
      abrirConfig();
      break;
  }
  delay(500);
}
