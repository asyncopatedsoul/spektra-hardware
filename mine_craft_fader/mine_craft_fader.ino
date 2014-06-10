

#define NR_OF_LIGHTS 6
int pins[NR_OF_LIGHTS] = { 3, 5, 6, 9, 10, 11 }; 

int values[NR_OF_LIGHTS];
int steps[NR_OF_LIGHTS];

#define NR_OF_FADESTEPS 5
int fadesteps[NR_OF_FADESTEPS] = { 128, 64, 32, 6, 0 }; 
int fade_delay = 30; // millisec
int fade_cycles = 1000;


int randomlights[NR_OF_LIGHTS];
bool chosenlights[NR_OF_LIGHTS];

void setup() { 
  randomSeed(analogRead(0));
  for (int i = 0; i < NR_OF_LIGHTS; i++) {
    values[i] = (int)random(230) + 15; // start values between 'max min' and 'min max'
    steps[i] = (int)random(4) + 1; // steps between 1 and 4
  }
} 

void loop() { 

  for (int j = 0; j < fade_cycles; j++) {
    for (int i = 0; i < NR_OF_LIGHTS; i++) {
      fadingLight(i);  
    }
    delay(fade_delay);
 
} 
}

void fadingLight(int i) {
  
  int minvalue = (NR_OF_FADESTEPS * abs(steps[i])) + 1;
  int maxvalue = 255 - minvalue;

  int fs = NR_OF_FADESTEPS;
  for (int j = 0; fs > 0; fs--, j++) {
    if (values[i] > fadesteps[j]) {
        break;
    }
  }
  values[i] += fs * steps[i];
  
  if (values[i] > maxvalue  ||  values[i] < minvalue) {
      steps[i] *= -1;
  }
  
  analogWrite(pins[i], values[i]);
}















