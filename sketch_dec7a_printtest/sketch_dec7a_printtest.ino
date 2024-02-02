void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(1000);
  Serial.println(2000);
  Serial.println(10.23);
  Serial.println(10.23,1);
  Serial.println('A');
  Serial.println(20,DEC);
  Serial.println(20,HEX);
  Serial.println(20,BIN);
}

void loop() {
  // put your main code here, to run repeatedly:
}
