int led = 13;
int colCount = 16;
int rowCount = 4;


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
   if (pin <=13) {
     if (output){
       digitalWrite(pin,HIGH);
     } else {
       digitalWrite(pin,LOW);
     }
   } else if (pin==14) {
     if (output){
       digitalWrite(A0,HIGH);
     } else {
       digitalWrite(A0,LOW);
     }
   } else if (pin==15) {
     if (output){
       digitalWrite(A1,HIGH);
     } else {
       digitalWrite(A1,LOW);
     }
   } else if (pin==16) {
     if (output){
       digitalWrite(A2,HIGH);
     } else {
       digitalWrite(A2,LOW);
     }
   } else if (pin==17) {
     if (output){
       digitalWrite(A3,HIGH);
     } else {
       digitalWrite(A3,LOW);
     }
   } else if (pin==18) {
     if (output){
       digitalWrite(A4,HIGH);
     } else {
       digitalWrite(A4,LOW);
     }
   } else if (pin==19) {
     if (output){
       digitalWrite(A5,HIGH);
     } else {
       digitalWrite(A5,LOW);
     }
   }
   
}

void setAllCol(boolean setting) {
  
  setPin(0,setting);  
  setPin(1,setting);    
  setPin(2,setting);  
  setPin(3,setting);  
  setPin(4,setting);  
  //5 is row for PWM
  //6 is row for PWM
  setPin(7,setting);  
  setPin(8,setting);  
  //9 is row for PWM
  //10 is row for PWM
  setPin(11,setting);  
  setPin(12,setting);  
  setPin(13,setting);  
  setPin(14,setting);  
  setPin(15,setting);  
  setPin(16,setting);  
  setPin(17,setting);  
  setPin(18,setting);  
  setPin(19,setting);  
  
};

void fadeCol(int col,int fadeDelay) {
  
  // http://arduino.cc/en/Tutorial/PWM
  // PWM only works on digital pins 0-13
  // PWM pins are 3, 5, 6, 9, 10, 11
  
  setPin(col,false);
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue+=5) { 
  
    analogWrite(5,fadeValue);
    analogWrite(6,fadeValue);
    analogWrite(9,fadeValue);
    analogWrite(10,fadeValue);
      
    delay(fadeDelay);                            
  } 
  
  for(int fadeValue = 255 ; fadeValue > 0; fadeValue-=5) { 
    analogWrite(5,fadeValue);
    analogWrite(6,fadeValue);
    analogWrite(9,fadeValue);
    analogWrite(10,fadeValue);
    
    delay(fadeDelay);                            
  } 

}

void loop() {
  setAllCol(true);
  
  int columns[16] = {0,1,2,3,4,7,8,11,12,13,14,15,16,17,18,19};
  int col = random(0,16);
  
  fadeCol(columns[col],25);
}
