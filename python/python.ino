long randNumber;
String inputString;
const int pinLM35 = 2;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  pinMode(16, INPUT);
}

void loop() {
  delay(100);
  SerialEvent();
}

void SerialEvent(){
  int lectura = analogRead(pinLM35);
  float voltaje = lectura * (5000 / 1023.0);
  float tempC = voltaje / 10;
  voltaje = voltaje / 1000;
  
  while(Serial.available()){
    char inputChar = Serial.read();
    inputString += inputChar;
  }
  if(inputString.indexOf("getValue")>=0){
    randNumber = random(100);
    String json_data = "{\"Temperatura\":" + (String)tempC + "}";
    Serial.println(json_data);
  }
  inputString = "";
}
