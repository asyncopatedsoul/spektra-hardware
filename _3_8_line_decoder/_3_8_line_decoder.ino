/*
Interfacing a M74HC238 3-8 Line Decoder With an Arduino (Example)
Zach Cross - Oct 19 2011
*/

const int selA[3] = {2,8,A1};
const int selB[3] = {3,12,A2};
const int selC[3] = {4,13,A3};
const int enable[3] = {7,A0,A4};

//5, 6, 9, 10, 11

int incomingByte;

void setup()
{
  // initialize the serial communication:
  //Serial.begin(9600);
  
  // initialize the control outputs
  for (int i=0;i<3;i++) {
    pinMode(selA[i], OUTPUT);
    pinMode(selB[i], OUTPUT);
    pinMode(selC[i], OUTPUT);
    pinMode(enable[i], OUTPUT);
  }
 
  for (int i=0;i<3;i++) {
    digitalWrite(selA[i], LOW);
    digitalWrite(selB[i], LOW);
    digitalWrite(selC[i], LOW);
    digitalWrite(enable[i], HIGH);
  }
  
}

void loop() 
{
 // digitalWrite(enable, HIGH);
        digitalWrite(selC[0], LOW);
        digitalWrite(selB[0], LOW);
          digitalWrite(selA[0], LOW);

  delay(1000);
  
  //digitalWrite(enable,HIGH);
        digitalWrite(selC[0], LOW);
        digitalWrite(selB[0], LOW);
          digitalWrite(selA[0], HIGH);
  
  delay(1000);
  /*
    if (Serial.available() > 0) {

    incomingByte = Serial.read();

      if (incomingByte == '0') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, LOW);
        digitalWrite(selB, LOW);
        digitalWrite(selA, LOW);
        Serial.println("Green LED 0: HIGH");
      
      }else if (incomingByte == '1') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, LOW);
        digitalWrite(selB, LOW);
        digitalWrite(selA, HIGH);
        Serial.println("Green LED 1: HIGH");
      
      }else if (incomingByte == '2') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, LOW);
        digitalWrite(selB, HIGH);
        digitalWrite(selA, LOW);
        Serial.println("Yellow LED 2: HIGH");
        
      }else if (incomingByte == '3') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, LOW);
        digitalWrite(selB, HIGH);
        digitalWrite(selA, HIGH);
        Serial.println("Yellow LED 3: HIGH");
        
      }else if (incomingByte == '4') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, HIGH);
        digitalWrite(selB, LOW);
        digitalWrite(selA, LOW);
        Serial.println("Red LED 4: HIGH");
        
      }else if (incomingByte == '5') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, HIGH);
        digitalWrite(selB, LOW);
        digitalWrite(selA, HIGH);
        Serial.println("Red LED 5: HIGH");
        
      }else if (incomingByte == '6') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, HIGH);
        digitalWrite(selB, HIGH);
        digitalWrite(selA, LOW);
        Serial.println("Y6: HIGH");
        
      }else if (incomingByte == '7') {
        digitalWrite(enable, LOW);
        digitalWrite(selC, HIGH);
        digitalWrite(selB, HIGH);
        digitalWrite(selA, HIGH);
        Serial.println("Y7: HIGH");
        
      }else if (incomingByte == '8') {
        digitalWrite(enable, HIGH);
        Serial.println("Disabled, all LEDS LOW");
    
      }
  
    }
 */   
}



