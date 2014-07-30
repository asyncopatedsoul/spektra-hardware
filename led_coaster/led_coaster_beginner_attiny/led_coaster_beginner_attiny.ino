// Indentifies the Pins used on the ATtiny
int pinLedRed = 0;
int pinLedYellow = 1;
int pinLedGreen = 2;

int pinPressureSensor = 3;

// The number of pressure levels on their ranges
int countPressureLevels = 4;
int colorPressureLevels[4][2] = {
{0,100},
{101,103},
{104,106},
{107,1000}
};

// This is the color for each pressure level
int colorRGBValues[4][3] = {
{0,0,0},
{255,0,0}, //red
{0,255,0}, //yellow
{0,0,255} //green
};

/* ATtiny's don't have the serial library due to their smaller size, so thats
   why is commented out. 
*/
void setup() {
  
  //Serial.begin(9600);
  
  pinMode(pinPressureSensor, INPUT);
  
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);
  pinMode(pinLedYellow, OUTPUT);
}

void loop() {
  int pressureLevel = getPressureLevel();
 //Serial.println(pressureLevel);
  setColor(pressureLevel);
}

// Finds the color for the right pressure vaule and turns on and off the LED's
void setColor(int pressureLevel) {

  int redValue = colorRGBValues[pressureLevel][0];
  int yellowValue = colorRGBValues[pressureLevel][1];
  int greenValue = colorRGBValues[pressureLevel][2];
  
  analogWrite(pinLedRed,redValue);
  analogWrite(pinLedGreen,greenValue);
  analogWrite(pinLedYellow,yellowValue); 
}

// This finds the pressure level between the to copper PCB's
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
