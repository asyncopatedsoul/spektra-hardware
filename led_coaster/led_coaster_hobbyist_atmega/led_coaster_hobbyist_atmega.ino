//#include <NewSoftSerial.h>

int pin_zero = 0;
int pin_one = 1;
int pin_two = 2;

int pin_three = 8;
int pin_four = 9;
int pin_five = 10;

int pin_six = 11;
int pin_seven = 12;
int pin_eight = 13;

int pinPressureSensor = A3;

int countPressureLevels = 8;
int colorPressureLevels[8][2] = {
{0,200},
{201,235},
{236,270},
{271,300},
{301,337},
{338,368},
{369,399},
{400, 1000}
};


int colorRGBValues[8][4] = { 
{255,255,255,255},
{0, 255, 0, 255}, 
{255, 255,0,0},
{255, 0, 0, 0},
{255, 0, 255, 0},
{0,255,255,255},
{0,0,255,255},
{0,0,0, 255}

};

void setup() {
  //Serial.begin(9600);
  
  pinMode(pinPressureSensor, INPUT);
  
  pinMode(pin_zero, OUTPUT);
  pinMode(pin_one, OUTPUT);
  pinMode(pin_two, OUTPUT);
  
  pinMode(pin_three, OUTPUT);
  pinMode(pin_four, OUTPUT);
  pinMode(pin_five, OUTPUT);
  
  pinMode(pin_six, OUTPUT);
  pinMode(pin_seven, OUTPUT);
  pinMode(pin_eight, OUTPUT);
}

void loop() {
  int pressureLevel = getPressureLevel();
 //Serial.println(pressureLevel);
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
  
  analogWrite(pin_zero,redValue);
  analogWrite(pin_one,greenValue);
  analogWrite(pin_two,yellowValue);
  
  analogWrite(pin_three, redValue);
  analogWrite(pin_four,greenValue);
  analogWrite(pin_five,yellowValue);
  
  analogWrite(pin_six, redValue);
  analogWrite(pin_seven,greenValue);
  analogWrite(pin_eight,yellowValue);
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
