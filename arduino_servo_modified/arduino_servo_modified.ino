#include <SoftwareServo.h> 
 
SoftwareServo myservo;  // create servo object to control a servo 
 
const int sensorPin= 3;
const int ledPin= 2;

const int threshold= 7;
const int lockAngle = 179;
const int unlockAngle = 0;

const int lockStateLocked = 0;
const int lockStateUnlocked = 1;

int lockState;

void servoLock()
{
 myservo.write(lockAngle);
 SoftwareServo::refresh();
}

void servoUnlock()
{
  myservo.write(unlockAngle);
  SoftwareServo::refresh();
}


void setup()
{
pinMode(ledPin, OUTPUT);
lockState = lockStateUnlocked;

digitalWrite(ledPin,LOW);

myservo.attach(0);  // attaches the servo on pin 5 to the servo object 
//Serial.begin(9600);
}


void loop()
{
int val= analogRead(sensorPin);
 val = map(val, 0, 1023, 0, 179);
//Serial.println(val);

if (val >= threshold)
{
  digitalWrite(ledPin,HIGH);
  // knock detected
  if (lockState==lockStateUnlocked) {
    lockState = lockStateLocked;
  
  } else if (lockState==lockStateLocked) {
    lockState = lockStateUnlocked;
   
  }
} else {
 digitalWrite(ledPin,LOW); 
}

if (lockState==lockStateUnlocked) {
  // unlock door
  servoUnlock();
 
} else if  (lockState==lockStateLocked) {
  // lock door
  servoLock();
  
}

delay(3000);

} 
