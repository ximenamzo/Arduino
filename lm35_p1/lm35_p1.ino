float tempC;
float calculo;
int pinLM35 = 0;

void setup() {
  Serial.begin(9600); // bps
}

void loop() {
  tempC = analogRead(pinLM35); // leer
  calculo = (5.0 * tempC * 100.0) / 1024.0; // calcular
  Serial.print(tempC);
  Serial.print(" - ");
  Serial.print(calculo);
  Serial.print("\n");
  delay(1000);
}
