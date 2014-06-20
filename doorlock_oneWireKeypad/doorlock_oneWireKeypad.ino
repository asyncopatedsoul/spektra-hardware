#include <EEPROM.h>
#include "EEPROMAnything.h"

#include <Servo.h> 
 
Servo lockServo;  // create servo object to control a servo 

const int greenLed = 13;
const int yellowLed = 12;
const int redLed = 11;
const int servoPin = 9;

const int lockAngle = 179;
const int unlockAngle = 0;

int entryCode[4] = {10,10,10,10};
struct config_t
{
   int entryCode[4];
} configuration;

int keyMap[12][2] = {
 {1021,1023},{508,509},{336,338},
 {176,177},{149,150},{129,130},
 {95,96},{86,87},{79,80},
 {63,66},{59,61},{56,58}
};

char keys[12] = {
  '1','2','3',//'A',
  '4','5','6',//'B',
  '7','8','9',//'C',
  '*','0','#',//'D'
};

int entrySequence[4];
int entryCount;
boolean isLocked;
boolean isResettingEntryCode;

void clearEEPROM() {
  for (int i = 0; i < 512; i++) {
      EEPROM.write(i, 0);
  }
 EEPROM_writeAnything(0, configuration); 
}

void setup() {
 Serial.begin(9600); 
 
 lockServo.attach(servoPin);
 
//clearEEPROM();
 
 EEPROM_readAnything(0, configuration);
 
 
 Serial.println("configuration:");
 Serial.println(configuration.entryCode[0]);
 Serial.println(configuration.entryCode[1]);
 Serial.println(configuration.entryCode[2]);
 Serial.println(configuration.entryCode[3]);
 
 entryCount = 0;
 isLocked = false;
 isResettingEntryCode = false;
 
 pinMode(greenLed,OUTPUT);
 pinMode(yellowLed,OUTPUT);
 pinMode(redLed,OUTPUT);
 pinMode(A5, INPUT);
 
 switchLock();
}

void loop(){
  
  showLockState();
  
  listenForEntry();
  
  if  (entryCount==4) {
    
    if (isResettingEntryCode) {
      
      entryCount=0;
      isResettingEntryCode=false;
      
      for (int i=0;i<4;i++) {
        configuration.entryCode[i]=entrySequence[i];
      }
          
      
      EEPROM_writeAnything(0, configuration);
      
      blinkLed(yellowLed,3);
    
    } else if (validateEntry()) {
        
      //switch lockState
     isLocked = !isLocked;
     switchLock();
      
      blinkLed(greenLed,3);
      
      //turn lock
      
    } else {
       //show incorrect
        blinkLed(redLed,3);
      
    }
  }
}

void showLockState() {
  
  digitalWrite(greenLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(redLed,LOW);
  
  if (isResettingEntryCode) {
    digitalWrite(yellowLed,HIGH);
  } else if (isLocked) {
      digitalWrite(redLed,HIGH);
      
  } else {
    digitalWrite(greenLed,HIGH);
      
  }
  
}

void switchLock() {
  if (isLocked) {
   lockServo.write(lockAngle); 
  } else {
    lockServo.write(unlockAngle); 
  }
}

void blinkLed(int pin, int count) {
   
  int blinkDelay=150;
  
  for (int i=0;i<count;i++) {
      digitalWrite(pin,HIGH);
        delay(blinkDelay);
        digitalWrite(pin,LOW);
        delay(blinkDelay);
  }
}

boolean validateEntry() {
  Serial.println("validating");
  
  entryCount=0;
  
  digitalWrite(greenLed,LOW);
  digitalWrite(yellowLed,LOW);
  digitalWrite(redLed,LOW);
  
  for (int i=0;i<4;i++) {
    
     Serial.println(entrySequence[i]);
     Serial.println(entryCode[i]);
     
   if (configuration.entryCode[i]!=entrySequence[i]) {
     return false;
   } 
  }
  
  return true;  
}

void listenForEntry() {
  int keyPressSensor = checkKeyPress();
  int keyPressedIndex = mapKeyPress(keyPressSensor);
  
  
  if (keyPressedIndex!=-1) {
    
    //char keyPressed = keys[keyPressedIndex];
    
    Serial.println(keyPressedIndex);
    
    //check if reset entry code
      if (!isLocked && keyPressedIndex==9) {
        
        blinkLed(yellowLed,3);
        isResettingEntryCode = true;
        
      } else {
    
      entrySequence[entryCount] = keyPressedIndex;
      Serial.println( entrySequence[entryCount]);
      entryCount++;
    
      }
  }
}

int mapKeyPress(int sensorValue) {
 
 for (int i=0;i<12;i++) {
   if (sensorValue>=keyMap[i][0] && sensorValue<=keyMap[i][1]) {
      return i; 
   }
 } 
 return -1; 
}

int checkKeyPress() {
  
  int sampleSize = 20;
  int threshold = 10;
  int debounce = 300;
  
  if (analogRead(A0)>threshold) {
    
    int resStream=0;
    int resStreamCount=0;
    
    do {
      resStream+=analogRead(A0);
      resStreamCount++;
    } while (resStreamCount<sampleSize);
    
    resStream = resStream/sampleSize;
    Serial.println(resStream);
    
    if (isResettingEntryCode) {
      //turn green LED on
      digitalWrite(greenLed,HIGH);
    } else {
      //turn yellow LED on
      digitalWrite(yellowLed,HIGH);
    }
    
    
    delay(debounce);
    return resStream;
    
  } else {
    
     if (isResettingEntryCode) {
      //turn green LED on
      digitalWrite(greenLed,LOW);
    } else {
      //turn yellow LED on
      digitalWrite(yellowLed,LOW);
    }
    
    
   return 0; 
  }
  
}
