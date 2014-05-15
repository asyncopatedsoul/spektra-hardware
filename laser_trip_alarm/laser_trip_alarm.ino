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

void loop() {

  //val = digitalRead(pinReadTripped); 
  //val = digitalRead(pinReadReset); 
  val = alarmStatus;
  // http://arduino.cc/en/Tutorial/DigitalReadSerial
  Serial.println(val);
  
  switch (alarmStatus) {
    
    case statusDeactivated:
      turnGreenOn(true);
      turnYellowOn(true);
      turnRedOn(true);
      
      setAlarm(false);
        
      if (isResetPressed()) {
        alarmStatus = statusWaitingForLaser;
      } else {
        //setAlarm(false);
      }
    break;
    
    case statusWaitingForLaser:
      turnGreenOn(true);
      turnYellowOn(false);
      turnRedOn(false);
      
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
      
      turnRedOn(false);
      delay(200);
      turnRedOn(true);
      delay(200);
      
      if (isResetPressed()) {
        alarmStatus = statusDeactivated;
        delay(1000);
      } else {
        
      }
    break;
  }
}



boolean isLaserTripped() {
  return (digitalRead(pinReadTripped)==HIGH);
}

boolean isResetPressed() {
  return (digitalRead(pinReadReset)==LOW);
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

void setAlarm(boolean on) {
  if (on) {
     digitalWrite(pinActivateAlarm,HIGH);
  } else {
     digitalWrite(pinActivateAlarm,LOW);
  }
  
}


