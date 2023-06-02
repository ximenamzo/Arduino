const int ledPin = 9;
const int potPin = 3;
//const int pinD2 = 2;
int val=0;

void setup() {
  Serial.begin(9600); // bps
  pinMode(ledPin, OUTPUT);
  //pinMode(potPin, INPUT);
}

void loop() {
  val = analogRead(potPin);
  Serial.print(val);
  Serial.print(" - ");
  //val = map(val, 0, 1023, 0, 255);
  Serial.print(val/4);
  Serial.print("\n");
  analogWrite(ledPin, val/4);
  /*digitalWrite(pinD2,HIGH);
  delay(1);
  digitalWrite(pinD2,LOW);
  delay(1);*/
  delay(1);
}
