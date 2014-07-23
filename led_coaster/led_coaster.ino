int pinLedRed = 5;
int pinLedGreen = 6;
int pinLedBlue = 7;

int pinPressureSensor = A0;

int countPressureLevels = 4;
int colorPressureLevels[4][2] = {
{0,100},
{101,200},
{201,300},
{301,400},
};

int colorRGBValues[4][3] = { 
{0,0,0},
{229,39,38}, //red
{119,192,67}, //green
{66,195,210}, //blue

};

void setup() {
  //Serial.begin(9600);
  
  pinMode(pinPressureSensor, INPUT);
  
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedBlue, OUTPUT);
}

void loop() {
  int pressureLevel = getPressureLevel();
  //Serial.println(pressureLevel);
  setColor(pressureLevel);
}

void setColor(int pressureLevel) {

  int redValue = colorRGBValues[pressureLevel][0];
  int greenValue = colorRGBValues[pressureLevel][1];
  int blueValue = colorRGBValues[pressureLevel][2];
  
  analogWrite(pinLedRed,redValue);
  analogWrite(pinLedGreen,greenValue);
  analogWrite(pinLedBlue,blueValue); 
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
