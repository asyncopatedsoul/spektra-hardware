int colCount = 16;
int rowCount = 4;

int delayMin = 1;
int delayMax = 1;
int delayMultiple = 1;

int fadeStep = 1;
int onDelay = 50;
int offDelay = 100;


// the setup routine runs once when you press reset:
void setup() {                
  
  // initialize all digitals pin as outputs
  for (int i=0;i<=13;i++) {
    pinMode(i, OUTPUT);     
  }
  
  // initialize all analog pins as outputs
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
  
   if (pin>=0 && pin<=5) {
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

void setAllCol(boolean setting) {
  
  for (int c=0;c<colCount;c++) {
    setPin(c,setting); 
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

  // http://arduino.cc/en/Tutorial/PWM
  // http://arduino.cc/en/Reference/analogWrite
  
  // PWM pins on ATmega238 are 3, 5, 6, 9, 10, 11
  // PWM pins on ATmega8 are 9, 10, 11

void fadeAllOn() {
  
  int fadeDelay = random(delayMin*delayMultiple,delayMax*delayMultiple);
  
  setAllCol(false);
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue+=1) { 
  
    analogWrite(6,fadeValue);
    analogWrite(9,fadeValue);
    analogWrite(10,fadeValue);
    analogWrite(11,fadeValue);
      
    delay(fadeDelay);                            
  } 
  

}
void fadeAllOff() {
  
  int fadeDelay = random(delayMin*delayMultiple,delayMax*delayMultiple);
  
  setAllCol(false);
    
  for(int fadeValue = 255 ; fadeValue > 0; fadeValue-=1) { 
    analogWrite(6,fadeValue);
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
