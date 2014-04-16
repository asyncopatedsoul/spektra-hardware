int led = 13;
int colCount = 16;
int rowCount = 4;

int dropDelay = 125;


// the setup routine runs once when you press reset:
void setup() {                

  // initialize the digital pin as an output.
  for (int i=0;i<14;i++) {
    pinMode(i, OUTPUT);     
  }

  pinMode(A0, OUTPUT);     
  pinMode(A1, OUTPUT);  
  
  pinMode(A2, OUTPUT);   
  pinMode(A3, OUTPUT);   
  pinMode(A4, OUTPUT);   
  pinMode(A5, OUTPUT);   
}

void setPin(int pin, boolean output) {
  // first 16 pins mapped to columns
  // 0   1   2   3   4   5   6   7   8    9    10  11  12  13  14  15  
  // D0  D1  D2  D3  D4  D5  D7  D8  D12  D13  A0  A1  A2  A3  A4  A5
  
  // last 4 pins mapped to rows
  // 16  17  18   19
  // D6  D9  D10  D11
  
   if (pin <=5) {
     if (output){
       digitalWrite(pin,HIGH);
     } else {
       digitalWrite(pin,LOW);
     }
   } else if (pin==6) {
     if (output){
       digitalWrite(7,HIGH);
     } else {
       digitalWrite(7,LOW);
     }
   } else if (pin==7) {
     if (output){
       digitalWrite(8,HIGH);
     } else {
       digitalWrite(8,LOW);
     }
   } else if (pin==8) {
     if (output){
       digitalWrite(12,HIGH);
     } else {
       digitalWrite(12,LOW);
     } 
   } else if (pin==9) {
     if (output){
       digitalWrite(13,HIGH);
     } else {
       digitalWrite(13,LOW);
     }
   } else if (pin==10) {
     if (output){
       digitalWrite(A0,HIGH);
     } else {
       digitalWrite(A0,LOW);
     }
   } else if (pin==11) {
     if (output){
       digitalWrite(A1,HIGH);
     } else {
       digitalWrite(A1,LOW);
     }
   } else if (pin==12) {
     if (output){
       digitalWrite(A2,HIGH);
     } else {
       digitalWrite(A2,LOW);
     }
   } else if (pin==13) {
     if (output){
       digitalWrite(A3,HIGH);
     } else {
       digitalWrite(A3,LOW);
     }
   } else if (pin==14) {
     if (output){
       digitalWrite(A4,HIGH);
     } else {
       digitalWrite(A4,LOW);
     }
   } else if (pin==15) {
     if (output){
       digitalWrite(A5,HIGH);
     } else {
       digitalWrite(A5,LOW);
     }
   } 
   
   else if (pin==16) {
     if (output){
       digitalWrite(6,HIGH);
     } else {
       digitalWrite(6,LOW);
     }
   } else if (pin==17) {
     if (output){
       digitalWrite(9,HIGH);
     } else {
       digitalWrite(9,LOW);
     }
   } else if (pin==18) {
     if (output){
       digitalWrite(10,HIGH);
     } else {
       digitalWrite(10,LOW);
     }
   } else if (pin==19) {
     if (output){
       digitalWrite(11,HIGH);
     } else {
       digitalWrite(11,LOW);
     }
   }
   
}


void singleOn(int col, int row, int wait) {
   for (int i=0;i<colCount;i++) {
     if (col==i) {
       setPin(i,false);
     } else {
       setPin(i,true); 
     }
   }
   
   for (int i=0;i<rowCount;i++) {
     if (row+colCount==i+colCount) {
       setPin(i+colCount,true);
     } else {
       setPin(i+colCount,false);
     }
   }
   
   delayMicroseconds(wait);
}

void setAllCol(boolean setting) {
  for (int i=0;i<colCount;i++) {
    setPin(i,setting);    
  }
};

void setAllRow(boolean setting) {
  for (int i=0;i<rowCount;i++) {
    setPin(i+colCount,setting);    
  }
}

void allOn() {
  setAllCol(false);
  setAllRow(true);
}

void allOff() {
  setAllCol(true);
  setAllRow(false);
}

void dropThroughColumn(int col,int dropDelay) {
  allOff();
  
  for (int row=3;row>=0;row--) {
      singleOn(col,row,dropDelay-1);
      delay(dropDelay);
  }
}

void rainDrops() {
  
  // random column
  // http://arduino.cc/en/Reference/Random
  
  int col = random(0,16);
  dropThroughColumn(col,dropDelay);
  
}

void loop() {

  rainDrops();

}
