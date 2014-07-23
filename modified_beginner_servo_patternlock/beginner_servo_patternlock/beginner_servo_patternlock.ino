#include <Servo.h>

/* Detects patterns of knocks and triggers a motor to unlock
   it if the pattern is correct.
   
   By Steve Hoefer http://grathio.com
   Version 0.1.10.20.10
   Licensed under Creative Commons Attribution-Noncommercial-Share Alike 3.0
   http://creativecommons.org/licenses/by-nc-sa/3.0/us/
   (In short: Do what you want, just be sure to include this line and the four above it, and don't sell it or use it in anything you sell without contacting me.)
   
   Analog Pin 0: Piezo speaker (connected to ground with 1M pulldown resistor)
   Digital Pin 2: Switch to enter a new code.  Short this to enter programming mode.
   Digital Pin 3: DC gear reduction motor attached to the lock. (Or a motor controller or a solenoid or other unlocking mechanisim.)
   Digital Pin 4: Red LED. 
   Digital Pin 5: Green LED. 
   
   Update: Nov 09 09: Fixed red/green LED error in the comments. Code is unchanged. 
   Update: Nov 20 09: Updated handling of programming button to make it more intuitive, give better feedback.
   Update: Jan 20 10: Removed the "pinMode(knockSensor, OUTPUT);" line since it makes no sense and doesn't do anything.
 */
 Servo lockServo;
 
// Pin definitions
const int knockSensor = A3;         // Piezo sensor on pin 0.
const int programSwitch = 8;       // If this is high we program a new code.
const int lockServoPin = 9;           // Gear motor used to turn the lock.
const int greenLED = 2;            // Status LED
const int yellowLED = 4;
const int redLED = 7;              // Status LED

const int lockAngle = 179;
const int unlockAngle = 0;

// Tuning constants.  Could be made vars and hoooked to potentiometers for soft configuration, etc.
const int threshold = 25;           // Minimum signal from the piezo to register as a knock
const int rejectValue = 25;        // If an individual knock is off by this percentage of a knock we don't unlock..
const int averageRejectValue = 45; // If the average timing of the knocks is off by this percent we don't unlock.
const int knockFadeTime = 250;     // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
const int lockTurnTime = 650;      // milliseconds that we run the motor to get it to go a half turn.

const int maximumKnocks = 20;       // Maximum number of knocks to listen for.
const int knockComplete = 1200;     // Longest time to wait for a knock before we assume that it's finished.


// Variables.
int secretCode[maximumKnocks] = {100, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int knockReadings[maximumKnocks];   // When someone knocks this array fills with delays between knocks.
int knockSensorValue;           // Last reading of the knock sensor.

boolean isLocked;
boolean isResettingEntryCode;

void setup() {
  Serial.begin(9600);                           // Uncomment the Serial.bla lines for debugging.
  Serial.println("Program start.");             // but feel free to comment them out after it's working right.
  
  pinMode(lockServoPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(programSwitch, INPUT);
  
  lockServo.attach(lockServoPin);
  
  knockSensorValue = 0;
  isResettingEntryCode = false;
  isLocked = false;
  
  
  updateLock();
}

void loop() {
  
  showLockState();

  if (digitalRead(programSwitch)==LOW  && !isLocked){  // is the program button pressed?
    Serial.println("reset button pressed.");
  
    if (!isResettingEntryCode) {
      Serial.println("entering reset mode...");
      isResettingEntryCode = true;
      blinkLed(yellowLED,5);
    } else {
       Serial.println("saving new code.");
      isResettingEntryCode = false;
      blinkLed(yellowLED,3); 
    }
  }
  
  // Listen for any knock at all.
  knockSensorValue = analogRead(knockSensor);
  
  if (knockSensorValue <=threshold){
    listenToSecretKnock();
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


void showLockState() {
  
  digitalWrite(greenLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(redLED,LOW);
  
  if (isResettingEntryCode) {
    digitalWrite(yellowLED,HIGH);
    digitalWrite(redLED,HIGH);
  } else if (isLocked) {
    digitalWrite(redLED,HIGH);
  } else {
    digitalWrite(greenLED,HIGH);   
  }

}

void updateLock() {
  if (isLocked) {
      Serial.println("Door locked.");
   lockServo.write(lockAngle); 
   
  } else {
      Serial.println("Door unlocked!");
    lockServo.write(unlockAngle); 
  }
}

void showKnock() {
  
  if (isResettingEntryCode){
     digitalWrite(greenLED, HIGH);
  } else {
    digitalWrite(yellowLED, HIGH); 
  }
      
  delay(knockFadeTime);       
  
  // again, a little delay to let the knock decay.
  if (isResettingEntryCode){
     digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(yellowLED, LOW); 
  }
}

void playbackEntryCode(int maxKnockInterval) {
  
  Serial.println(0);
  showKnock();
  
  for (int i = 0; i < maximumKnocks ; i++){

        int playbackDelay =  map(secretCode[i],0, 100, 0, maxKnockInterval);
        Serial.println(playbackDelay);
                    
        delay(playbackDelay); // Expand the time back out to what it was.  Roughly. 
        
        if (playbackDelay>0) {
          Serial.println(1+i);
          showKnock();
        }
   }
}

// Records the timing of knocks.
void listenToSecretKnock(){
  Serial.println("knock starting");   
  

  
  // First lets reset the listening array.
  for (int i=0;i<maximumKnocks;i++){
    knockReadings[i]=0;
  }
  
  int currentKnockNumber=0;                     // Incrementer for the array.
  int startTime=millis();                       // Reference for when this knock started.
  int now=millis();
  
  showKnock();
  
  do {
    //listen for the next knock or wait for it to timeout. 
    knockSensorValue = analogRead(knockSensor);

    if (knockSensorValue <=threshold){                   //got another knock...


      //record the delay time.
      Serial.println("knock.");
      now=millis();
      knockReadings[currentKnockNumber] = now-startTime;
      currentKnockNumber ++;                             //increment the counter
      startTime=now;          
      // and reset our timer for the next knock

      showKnock();
    }

    now=millis();
    
    //did we timeout or run out of knocks?
  } while ((now-startTime < knockComplete) && (currentKnockNumber < maximumKnocks));
  
  //we've got our knock recorded, lets see if it's valid
  if (!isResettingEntryCode){             // only if we're not in progrmaing mode.
    
    if (validateKnock()){
      switchLock(); 
    } else {
      Serial.println("Secret knock failed.");
      blinkLed(redLED,3);
    }
    
  } else { // if we're in programming mode we still validate the lock, we just don't do anything with the lock
    
    validateKnock();
    
    blinkLed(yellowLED,5);
     
    Serial.println("New lock recorded.");
  }
  
}


// Runs the motor (or whatever) to unlock the door.
void switchLock(){
  
  isLocked=!isLocked;
  updateLock();
  
  blinkLed(greenLED,3);
}

// Sees if our knock matches the secret.
// returns true if it's a good knock, false if it's not.
// todo: break it into smaller functions for readability.
boolean validateKnock(){
  int i=0;
 
  // simplest check first: Did we get the right number of knocks?
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0;                     // We use this later to normalize the times.
  
  for (i=0;i<maximumKnocks;i++){
    if (knockReadings[i] > 0){
      currentKnockCount++;
    }
    if (secretCode[i] > 0){                     //todo: precalculate this.
      secretKnockCount++;
    }
    
    if (knockReadings[i] > maxKnockInterval){   // collect normalization data while we're looping.
      maxKnockInterval = knockReadings[i];
    }
  }
  
  // If we're recording a new knock, save the info and get out of here.
  if (isResettingEntryCode){
      
      for (i=0;i<maximumKnocks;i++){ // normalize the times
        secretCode[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100); 
      }
      // And flash the lights in the recorded pattern to let us know it's been programmed.
      
      playbackEntryCode(maxKnockInterval);
      
      return false;     // We don't unlock the door when we are recording a new knock.
  }
  
  Serial.println(currentKnockCount);
  Serial.println('/');
  Serial.println(secretKnockCount);
  
  if (currentKnockCount != secretKnockCount){
    return false; 
  }
  
  /*  Now we compare the relative intervals of our knocks, not the absolute time between them.
      (ie: if you do the same pattern slow or fast it should still open the door.)
      This makes it less picky, which while making it less secure can also make it
      less of a pain to use if you're tempo is a little slow or fast. 
  */
  int totaltimeDifferences=0;
  int timeDiff=0;
  for (i=0;i<maximumKnocks;i++){ // Normalize the times
    knockReadings[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100);
    Serial.println("---"); 
    Serial.println(knockReadings[i]);    
    Serial.println("-"); 
    timeDiff = abs(knockReadings[i]-secretCode[i]);
    Serial.println(timeDiff);
    if (timeDiff > rejectValue){ // Individual value too far out of whack
      return false;
    }
    totaltimeDifferences += timeDiff;
  }
  // It can also fail if the whole thing is too inaccurate.
  if (totaltimeDifferences/secretKnockCount>averageRejectValue){
    //return false; 
  }
  
  return true;
  
}
