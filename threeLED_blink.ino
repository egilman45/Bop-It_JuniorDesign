void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  LED1_blink();

}

void LED1_blink() {
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}

void LED2_blink() {
  digitalWrite(14,HIGH);
  delay(500);
  digitalWrite(14, LOW);
  delay(500));
}

void LED3_blink() {
  digitalWrite(15,HIGH);
  delay(500);
  digitalWrite(15, LOW);
  delay(500));
}
