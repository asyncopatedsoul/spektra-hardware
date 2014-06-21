const int modeSteady = 0;
const int modeFlicker = 1;

int currentMode;
//int pinLED = 0;
//int pinModeSwitch = 1;
int pinLED = 3;
int pinModeSwitch = 4;
int modeChangeDelay = 750;


void setup() {
  
  //Serial.begin(9600);
  //pinMode(5,OUTPUT);
  
  pinMode(pinLED,OUTPUT);
  pinMode(pinModeSwitch,INPUT);
  currentMode = modeSteady;
}

void loop() {
 activateMode(currentMode); 
  
 if (detectModeSwitchPressed()) {
   
   analogWrite(pinLED,0);
   delay(modeChangeDelay);
   
   currentMode = getNewMode(currentMode);
   activateMode(currentMode);
   
   
 } else {
   
 }
}

boolean detectModeSwitchPressed() {
  if (digitalRead(pinModeSwitch)==HIGH) {
    //digitalWrite(5,HIGH);
    return true;
    
  } else {
    //digitalWrite(5,LOW);
    return false; 
  }
}

int getNewMode(int currentMode) {
  
    int newMode;
    switch (currentMode) {
      case modeSteady: 
        newMode = modeFlicker;
        break;
      case modeFlicker:
        newMode = modeSteady;
        break;
    }
    return newMode;
}

void activateMode(int mode) {
  switch(mode) {
    case modeSteady: 
      analogWrite(pinLED,255);
      break;
    case modeFlicker:
      int randomBrightness;
      int randomFlickerDelay;
      
      int brightnessMin = 5;
      int brightnessMax = 10;
      int brightnessMultiple = 25;
  
      randomBrightness = random(brightnessMin,brightnessMax)*brightnessMultiple;
      
      //Serial.println(randomBrightness);
      
      int delayMin = 1;
      int delayMax = 10;
      int delayMultiple = 50;
  
      randomFlickerDelay = random(delayMin,delayMax)*delayMultiple;
      
      analogWrite(pinLED,randomBrightness);
      delay(randomFlickerDelay);
      break;
  }
}
