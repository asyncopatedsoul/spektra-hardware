int pinLedRed = 5;
int pinLedYellow = 6;
int pinLedGreen = 7;
int pinActivateAlarm = 8;
int pinReadTripped = 9;
int pinReadReset = 10;
int val = 0; 

int disarmingDelay = 3000;

int alarmStatus;

const int statusDeactivated = 0;
const int statusWaitingForLaser = 1;
const int statusReadyToArm = 2;
const int statusArmed = 3;
const int statusTripped = 4;
const int statusDisarming = 5;


void setup() {
  Serial.begin(9600);  
  //setAlarm(false); 
  pinMode(pinReadTripped, INPUT);
  pinMode(pinReadReset, INPUT);
  
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinActivateAlarm, OUTPUT);
 
   alarmStatus = statusDeactivated;
}

void loop() {

 
  Serial.println(alarmStatus);
  Serial.println(isResetPressed());
  Serial.println(isLaserTripped());
  Serial.println("---");
  delay(500);
  
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
         alarmStatus = statusDisarming;
      }
    break;
    
    case statusDisarming:
      turnRedOn(false);
      setAlarm(false);
      alarmStatus = statusDeactivated;
      delay(disarmingDelay);
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
    digitalWrite(pinLedGreen,LOW);
  } else {
    digitalWrite(pinLedGreen,HIGH);
  }
}

void turnYellowOn(boolean on) {
  if (on) {
    digitalWrite(pinLedYellow,LOW);
  } else {
    digitalWrite(pinLedYellow,HIGH);
  }
}

void turnRedOn(boolean on) {
  if (on) {
    digitalWrite(pinLedRed,LOW);
  } else {
    digitalWrite(pinLedRed,HIGH);
  }
}

void setAlarm(boolean on) {
  if (on) {
     digitalWrite(pinActivateAlarm,HIGH);
  } else {
     digitalWrite(pinActivateAlarm,LOW);
  }
  
}


