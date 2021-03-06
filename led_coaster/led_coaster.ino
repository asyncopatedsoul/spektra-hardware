//#include <NewSoftSerial.h>

int pinLedRed = A2;
int pinLedYellow = A3;
int pinLedGreen = A1;

int pinPressureSensor = A0;

int countPressureLevels = 4;
int colorPressureLevels[4][2] = {
{0,100},
{101,200},
{201,300},
{301,400},

};


int colorRGBValues[4][3] = { 
{255,255,255},
{0,255,255}, //red
{255,0,255}, //yellow
{255,255,0} //green

};

void setup() {
  //Serial.begin(9600);
  
  pinMode(pinPressureSensor, INPUT);
  
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
}

void loop() {
  int pressureLevel = getPressureLevel();
  setColor(pressureLevel);
}

void setColor(int pressureLevel) {

  //int otherValue = colorRGBValues[pressureLevel][0];
  int redValue = colorRGBValues[pressureLevel][0];
  int yellowValue = colorRGBValues[pressureLevel][1];
  int greenValue = colorRGBValues[pressureLevel][2];

  
  //Serial.println(redValue + greenValue + yellowValue);
  //Serial.println(greenValue);
  //Serial.println(yellowValue);
  
  analogWrite(pinLedRed,redValue);
  analogWrite(pinLedGreen,greenValue);
  analogWrite(pinLedYellow,yellowValue); 
}

int getPressureLevel() {
  int pressureLevel=0;
  
  int pressureSensorValue = analogRead(pinPressureSensor);
  
  for (int i=0; i<countPressureLevels; i++) {
    int minValue = colorPressureLevels[i][0];
    int maxValue = colorPressureLevels[i][1];
    if (pressureSensorValue>=minValue && pressureSensorValue<=maxValue) {
      pressureLevel=i;
      break;
    } 
  }
  
  return pressureLevel;
}
