#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
const int sensorPin= A3;
const int ledPin= 2;

const int threshold= 1;
const int lockAngle = 179;
const int unlockAngle = 0;

const int lockStateLocked = 0;
const int lockStateUnlocked = 1;

int lockStateDelay = 3000;
int knockCountDelay = 2000;
int knockCountRequired = 2;

int lockState;
int knockCount;

void servoLock()
{
 myservo.write(lockAngle);
 //SoftwareServo::refresh();
}

void servoUnlock()
{
  myservo.write(unlockAngle);
  //SoftwareServo::refresh();
}


void setup()
{
pinMode(ledPin, OUTPUT);
lockState = lockStateUnlocked;
knockCount = 0;

digitalWrite(ledPin,LOW);

myservo.attach(5);  // attaches the servo on pin 5 to the servo object 
Serial.begin(9600);
}


void loop()
{
int val= analogRead(sensorPin);
 //val = map(val, 0, 1023, 0, 179);
 Serial.println(val);

if (val < threshold)
{
  //digitalWrite(ledPin,HIGH);
  // knock detected
  
  knockCount++;
  checkKnockCount();
  
} else {
 digitalWrite(ledPin,LOW); 
}

}


void checkKnockCount(){
  
  if (knockCount==knockCountRequired) {
      if (lockState==lockStateUnlocked) {
        // unlock door
        lockState=lockStateLocked;
      } else if  (lockState==lockStateLocked) {
        // lock door
        lockState=lockStateUnlocked;
      }
      
      updateLockState();
      
      knockCount=0;
  }
  
  delay(knockCountDelay);
  
} 

void updateLockState(){
  if (lockState==lockStateUnlocked) {
  // unlock door
  servoUnlock();
 
} else if  (lockState==lockStateLocked) {
  // lock door
  servoLock();
  
}

 // delay(lockStateDelay);
}
