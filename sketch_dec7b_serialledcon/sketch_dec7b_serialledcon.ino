const int led1 = 10;
const int led2 = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.setTimeout(100);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
//    char a = Serial.read();
      String inputStr = Serial.readString();

//      String state1;
//      String state2;
/*    Serial.println(a,HEX); */
    if (inputStr == "1o"){
      digitalWrite(led1, HIGH);
        Serial.println("1o");
//        state1 == "1o";
    }
    else if (inputStr == "1f"){
      digitalWrite(led1, LOW);
        Serial.println("1f");
//        state1 == "1f";
    }
    else if (inputStr == "2o"){
      digitalWrite(led2, HIGH);
        Serial.println("2o");
 //       state2 == "2o";
    }
    else if (inputStr == "2f"){
      digitalWrite(led2, LOW);
        Serial.println("2f");
  //      state2 == "2f";
    }

    else if (inputStr == "1r"){
      int st = digitalRead(led1);
      if (st == 1){
        Serial.print("1o");
        Serial.write(13);
        Serial.write(10);
      }
      else if (st == 0){
        Serial.print("1f");
        Serial.write(13);
        Serial.write(10);
      }
    }

    else if (inputStr == "2r"){
      int st = digitalRead(led2);
      if (st == 1){
        Serial.print("2o");
        Serial.write(13);
        Serial.write(10);
      }
      else if (st == 0){
        Serial.print("2f");
        Serial.write(13);
        Serial.write(10);
      }
    }

    
    /*
    switch(input) {
      case '1' :
        digitalWrite(led1, HIGH);
        Serial.print("1o");
        break;

      case "2" :
        digitalWrite(led1, LOW);
        Serial.print("1f");
        break;

      case "3" :
        digitalWrite(led2, HIGH);
        Serial.print("2o");
        break;

      case "4" :
        digitalWrite(led2, LOW);
        Serial.print("2f");
        break;

      default :
      Serial.print("e");
        break;
    }
    */
  }
/*  else {
    Serial.println("Serial data received FAIL. Arduino Serial Bussfer is NULL");
  }
*/
}
