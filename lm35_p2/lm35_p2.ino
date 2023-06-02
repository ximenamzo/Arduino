const int pinLM35 = 2;

void setup() {
  Serial.begin(9600); // bps
  pinMode(16, INPUT);
}

void loop() {
  int lectura = analogRead(pinLM35);
  float voltaje = lectura * (5000 / 1023.0);
  float tempC = voltaje / 10;
  Serial.print("Entrada: ");
  Serial.print(lectura);
  Serial.print(" - Volts: ");
  Serial.print(voltaje/1000);
  Serial.print(" - Temperatura: ");
  Serial.print(tempC);
  Serial.print("°C \n");
  delay(1000);
}
