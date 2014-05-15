int pinLedRed = 5;
int pinLedYellow = 6;
int pinLedGreen = 7;
int pinActivateAlarm = 8;
int pinReadTripped = 9;
int pinReadReset = 10;
int val = 0; 

int alarmStatus;

const int statusDeactivated = 0;
const int statusWaitingForLaser = 1;
const int statusReadyToArm = 2;
const int statusArmed = 3;
const int statusTripped = 4;


void setup() {
  Serial.begin(9600);  
  //setAlarm(false); 
  pinMode(pinReadTripped, INPUT);
  pinMode(pinReadReset, INPUT);
  
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinActivateAlarm, OUTPUT);
 
   alarmStatus = 0;
}

void turnGreenOn(boolean on) {
  if (on) {
    digitalWrite(pinLedGreen,HIGH);
  } else {
    digitalWrite(pinLedGreen,LOW);
  }
}

void turnYellowOn(boolean on) {
  if (on) {
    digitalWrite(pinLedYellow,HIGH);
  } else {
    digitalWrite(pinLedYellow,LOW);
  }
}

void turnRedOn(boolean on) {
  if (on) {
    digitalWrite(pinLedRed,HIGH);
  } else {
    digitalWrite(pinLedRed,LOW);
  }
}

void loop() {

  //val = digitalRead(pinReadTripped); 
  //val = digitalRead(pinReadReset); 
  val = alarmStatus;
  // http://arduino.cc/en/Tutorial/DigitalReadSerial
  Serial.println(val);
  
  switch (alarmStatus) {
    
    case statusDeactivated:
      turnGreenOn(true);
      turnYellowOn(false);
      turnRedOn(false);
      
      setAlarm(false);
        
      if (isResetPressed()) {
        alarmStatus = statusWaitingForLaser;
      } else {
        //setAlarm(false);
      }
    break;
    
    case statusWaitingForLaser:
      if (!isLaserTripped()) {
         alarmStatus = statusReadyToArm;
      }
    break;
    
    case statusReadyToArm: 
      turnGreenOn(false);
      turnYellowOn(true);
      turnRedOn(false);
    
      if (isLaserTripped()) {
        alarmStatus = statusWaitingForLaser;
      } else if(isResetPressed()) {
        alarmStatus = statusArmed;
      }
    break;
    
    
    case statusArmed:
      turnGreenOn(false);
      turnYellowOn(false);
      turnRedOn(true);
    
      if (isLaserTripped()) {
        alarmStatus = statusTripped;
      } else {
        
      }
    break;
    
    case statusTripped:
      setAlarm(true);
      
      if (isResetPressed()) {
        alarmStatus = statusDeactivated;
        delay(1000);
      } else {
        
      }
    break;
    
    
  }
  
  // check for trip
//  if (isLaserTripped()) {
//    setAlarm(true);
//  } else {
//    setAlarm(false);
//  }
  

//  
//  
//  delay(100);
  
}

boolean isLaserTripped() {

  return (digitalRead(pinReadTripped)==HIGH);
  
}

void setAlarm(boolean on) {
   
  if (on) {
     digitalWrite(pinActivateAlarm,HIGH);
  } else {
     digitalWrite(pinActivateAlarm,LOW);
  }
  
}

boolean isResetPressed() {
 return (digitalRead(pinReadReset)==LOW);
}
