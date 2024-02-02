const int led = 10;
const int btn = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(btn,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int btnState = digitalRead(btn);
  digitalWrite(led, btnState);
}
