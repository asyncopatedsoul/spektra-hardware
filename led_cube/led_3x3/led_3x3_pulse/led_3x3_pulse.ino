int rowCount = 3;
int colCount = 9;
int pinCount = rowCount+colCount;

int delayMin = 1;
int delayMax = 1;
int delayMultiple = 1;

int fadeStep = 1;

int onDelay = 50;
int offDelay = 100;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i=0;i<pinCount;i++) {
    pinMode(i, OUTPUT);     
  }
   
}

void setPin(int pin, boolean output) {
  // first 9 pins mapped to columns
  // 0   1   2   3   4   5   6   7   8   
  // D0  D1  D2  D3  D4  D5  D6  D7  D8
  
  // last 3 pins mapped to rows
  // 9   10   11
  // D9  D10  D11
  
   if (output){
     digitalWrite(pin,HIGH);
   } else {
     digitalWrite(pin,LOW);
   }
   
}

void setAllCol(boolean setting) {
  for (int c=0;c<9;c++){
    setPin(c, setting);
  }  
}

void allColOn() {
  setAllCol(false);
}

void allColOff() {
  setAllCol(true);
}

void setCol(int col, boolean setting) {
  setPin(col, setting);
}


void allRow(boolean setting) {
  for (int r=9;r<12;r++) {
    setPin(r, setting);
  }  
}

void setRow(int row, boolean setting) {
  setPin(row+colCount, setting);  
}

void allRowOn(){
  allRow(true);
}

void allRowOff(){
  allRow(false);
}

void allOn() {
  allRowOn();
  allColOn();
}

void allOff() {
  allRowOff();
  allColOff();
}


void singleOn(int col, int row) {
   allOff();
  
   for (int i=0;i<3;i++) {
    if (i == row) {
      setRow(i,true);
    } else {
      setRow(i,false);
    }
  }
  
  for (int i=0;i<9;i++) {
    if (i == col) {
      setCol(i,false);
    } else {
      setCol(i, true);
    }
  }
    
}

 // http://arduino.cc/en/Tutorial/PWM
  // http://arduino.cc/en/Reference/analogWrite
  
  // PWM pins on ATmega238 are 3, 5, 6, 9, 10, 11
  // PWM pins on ATmega8 are 9, 10, 11

void fadeAllOn() {
  
  int fadeDelay = random(delayMin*delayMultiple,delayMax*delayMultiple);
  
  setAllCol(false);
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue+=fadeStep) { 
  
    analogWrite(9,fadeValue);
    analogWrite(10,fadeValue);
    analogWrite(11,fadeValue);
      
    delay(fadeDelay);                            
  } 

}


void fadeAllOff() {
  
  int fadeDelay = random(delayMin*delayMultiple,delayMax*delayMultiple);
  
  setAllCol(false);
    
  for(int fadeValue = 255 ; fadeValue > 0; fadeValue-=fadeStep) { 

    analogWrite(9,fadeValue);
    analogWrite(10,fadeValue);
    analogWrite(11,fadeValue);
    
    delay(fadeDelay);                            
  } 

}

void loop() {
  
  fadeAllOn();
  allOn();
  delay(onDelay);
  fadeAllOff();
  allOff();
  delay(offDelay);
  
}
