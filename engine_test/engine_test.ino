const int pin1 = 12;
const int pin2 = 14;
const int tm = 2000;


void setup() {
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
}

void loop() {
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,HIGH);
  delay(tm);

  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,LOW);
  delay(tm);
}
