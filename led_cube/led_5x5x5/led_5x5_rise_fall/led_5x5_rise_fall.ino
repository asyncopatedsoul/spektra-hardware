/*
Interfacing a M74HC238 3-8 Line Decoder With an Arduino
*/

const int selA[3] = {2,8,A1};
const int selB[3] = {3,12,A2};
const int selC[3] = {4,13,A3};
const int enable[3] = {7,A0,A4};
const int lastCol = A5;

//PWM/VCC pins for fading effects
//5, 6, 9, 10, 11

int row[5] = {5, 6, 9, 10, 11};

// cols are mutually exclusive within groups of 8 by line decoder + last col
// so we create an array mapping active pins
// then we multiplex through the array

int columns[25];

int incomingByte;

int frameCounter;
int frameInterval; // how many loops through rendering all cols

int fadeStep = 10;
int fadeMin = 0;
int fadeMax = 255;

void setup()
{
  frameCounter = 0;
  
  // initialize the control outputs
  for (int i=0;i<3;i++) {
    pinMode(selA[i], OUTPUT);
    pinMode(selB[i], OUTPUT);
    pinMode(selC[i], OUTPUT);
    pinMode(enable[i], OUTPUT);
  }
 
  allOff();
}

void allOff() {
  // turn off all rows
  for (int r=0;r<5;r++) {
    analogWrite(row[r],0); 
  }
  
  // turn off all cols
  
  // for cols connected to 3-8 line decoders: by setting all enable pins LOW 
  for (int i=0;i<3;i++) {
    digitalWrite(enable[i], LOW);
  }
  digitalWrite(lastCol,LOW);
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
  
  // 1st line decoder:
  //0 - 7
  
  // 2nd line decoder:
  //8 - 15
  
  // 3rd line decoder:
  //16 - 23
  
  // last col
  //24

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

void rowOn(int r) {
  for (int i=0;i<5;i++) {
    if (i==r) {
      analogWrite(row[i],255); 
    } else {
      analogWrite(row[i],0); 
    }
  }
}

void dropThroughCol(int col, int dropDelay) {
  allOff();
  
  // set cols
  setCol(col,true);
  
  for (int r=5;r>=0;r--) {
    rowOn(r); 
    delay(dropDelay);
  }
  
}

void riseThroughCol(int col, int riseDelay) {
  allOff();
  
  // set cols
  setCol(col,true);
  
  for (int r=0;r<5;r++) {
    rowOn(r); 
    delay(riseDelay);
  }
}

void fadeColIn(int col, int fadeDelay) {
  allOff();
  
  // set cols
  setCol(col,true);
  
  // set rows
  for(int fadeValue = fadeMin ; fadeValue <= fadeMax; fadeValue+=fadeStep) { 
    setAllRows(fadeValue);  
    delay(fadeDelay);
    //renderFrame();
  } 
}

void fadeColOut(int col, int fadeDelay) {
  allOff();
  
  // set cols
  setCol(col,true);
  
  // set rows
  for(int fadeValue = fadeMax ; fadeValue >= fadeMin; fadeValue-=fadeStep) { 
    setAllRows(fadeValue);
    delay(fadeDelay);  
    //renderFrame();
  } 
  
}

void loop() 
{  
  frameInterval = 75;
  
  int motionDelay = 50;
  int col = random(0,25);
  int motion = random(0,2);
  
  if (motion==0) {
    dropThroughCol(col,motionDelay);
  } else {
    riseThroughCol(col,motionDelay);
  }

  allOff();
}



