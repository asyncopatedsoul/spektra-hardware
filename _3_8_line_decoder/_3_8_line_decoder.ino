/*
Interfacing a M74HC238 3-8 Line Decoder With an Arduino (Example)
Zach Cross - Oct 19 2011
*/

const int selA[3] = {2,8,A1};
const int selB[3] = {3,12,A2};
const int selC[3] = {4,13,A3};
const int enable[3] = {7,A0,A4};
const int lastCol = A5;

//PWM/VCC pins for fading effects
//5, 6, 9, 10, 11

// cols are mutually exclusive within groups of 8 by line decoder
// so we create an array mapping active pins
// then we multiplex through the array

int columns[25];

int incomingByte;

int frameCounter;
int frameInterval;

void setup()
{
  frameCounter = 0;
  
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
//    digitalWrite(selA[i], LOW);
//    digitalWrite(selB[i], LOW);
//    digitalWrite(selC[i], LOW);
    digitalWrite(enable[i], LOW);
  }
  
  int fadeValue = 255; 
  
  
}

void setAllRows(int fadeValue) {
  analogWrite(5,fadeValue);
  analogWrite(6,fadeValue);
  analogWrite(9,fadeValue);
  analogWrite(10,fadeValue);
  analogWrite(11,fadeValue); 
}


void setCol(int pin, boolean output) {
  int s = 0;

  if (pin>=8 && pin <15) {
    s = 1;
    pin-=8;
  } else if (pin>=16 && pin <23) {
    s = 2;
    pin-=16;
  } 
  
  if (pin==24) {
    s = 3;
    digitalWrite(lastCol,HIGH);
  } else {
    digitalWrite(lastCol,LOW);
  }
  //0 - 7
  //8 - 15
  //16 - 23
  //24
  
  for (int i=0;i<3;i++){
     if (i==s) {
       digitalWrite(enable[i], HIGH);
     } else {
       digitalWrite(enable[i], LOW);
     }
  }
 
  
  switch (pin) {
    
    case 0:
      digitalWrite(selC[s], LOW);
      digitalWrite(selB[s], LOW);
      digitalWrite(selA[s], LOW);
      break;
    case 1:
      digitalWrite(selC[s], LOW);
      digitalWrite(selB[s], LOW);
      digitalWrite(selA[s], HIGH);
      break;
    case 2:
      digitalWrite(selC[s], LOW);
      digitalWrite(selB[s], HIGH);
      digitalWrite(selA[s], LOW);
      break;
    case 3:
      digitalWrite(selC[s], LOW);
      digitalWrite(selB[s], HIGH);
      digitalWrite(selA[s], HIGH);
      break;
    case 4:
      digitalWrite(selC[s], HIGH);
      digitalWrite(selB[s], LOW);
      digitalWrite(selA[s], LOW);
      break;
    case 5:
      digitalWrite(selC[s], HIGH);
      digitalWrite(selB[s], LOW);
      digitalWrite(selA[s], HIGH);
      break;
    case 6:
      digitalWrite(selC[s], HIGH);
      digitalWrite(selB[s], HIGH);
      digitalWrite(selA[s], LOW);
      break;
    case 7:
      digitalWrite(selC[s], HIGH);
      digitalWrite(selB[s], HIGH);
      digitalWrite(selA[s], HIGH);
      break;
  }
}

void renderCols() {
  for (int i=0;i<25;i++) {
    setCol(i,columns[i]);
    //delay(1000);
  } 
}

void renderFrame() {
  while (frameCounter < frameInterval) {
      renderCols();
      frameCounter++;
    }  
   frameCounter = 0;  
}

void loop() 
{
  int fadeStep = 10;
  frameInterval = 75;
  
  int fadeMin = 0;
  int fadeMax = 255;
  // set cols
  for (int i=0;i<25;i++) {
    columns[i]=1;
  }
  
  // set rows
  
  // fade in
  for(int fadeValue = fadeMin ; fadeValue <= fadeMax; fadeValue+=fadeStep) { 
    setAllRows(fadeValue);  
    renderFrame();
  } 
  
  // fade out
  for(int fadeValue = fadeMax ; fadeValue >= fadeMin; fadeValue-=fadeStep) { 
    setAllRows(fadeValue);  
    renderFrame();
  } 
  
  
  
  
  
  
  
  /*
  digitalWrite(enable[0], HIGH);
  digitalWrite(selC[0], LOW);
  digitalWrite(selB[0], LOW);
  digitalWrite(selA[0], LOW);

  delay(1000);
  
  digitalWrite(enable[0],HIGH);
  digitalWrite(selC[0], LOW);
  digitalWrite(selB[0], LOW);
  digitalWrite(selA[0], HIGH);
  
  delay(1000);
  */
  
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



