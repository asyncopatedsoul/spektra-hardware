#include <FastSPI_LED.h>
#include <Flash.h>

//LED SETUP

#define NUM_LEDS 144
// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

#define PIN 7
#define IMAGE_PIXELS 45

FLASH_TABLE(byte, images, IMAGE_PIXELS,   // use this form images[8][144]={
  {19, 18, 17, 16, 27, 32, 44, 40, 39, 51, 54, 56, 68, 65, 63, 75, 77, 80, 92, 90, 87, 99,100,104,116,111,124,125,126,127},//0
  {18, 17, 30, 41, 54, 65, 78, 89, 102,113,126},//1
  {19,18,17,16,27,28,31,32,44,39,55,56,65,64,77,78,91,90,100,116,123,124,125,126,127,128},//2
  {19,18,17,16,15,32,40,39,54,55,67,66,65,78,79,88,87,99,104,116,115,111,124,125,126,127,128},//3
  {18,15,29,32,43,39,52,56,68,63,75,76,77,78,79,80,87,104,111,128},//4
  {20,19,18,17,16,15,27,44,51,52,53,66,65,64,79,80,87,99,104,116,115,112,111,124,125,126,127},//5
  {19,18,17,16,27,28,32,44,51,68,66,65,64,75,76,79,80,92,87,99,104,116,115,112,111,124,125,126,127},//6
  {20,19,18,17,16,15,27,32,39,55,65,77,90,100,115,124},//7
  {19,18,17,16,27,32,44,39,52,55,66,65,76,79,92,87,99,104,116,111,124,125,126,127},//8
  {19,18,17,16,27,32,44,39,51,56,68,64,63,76,77,78,80,87,104,116,112,124,125,126},//9
  {22, 21, 17, 16, 15, 14, 26, 29, 34, 45, 42, 38, 37, 50, 53, 56, 58, 69, 66, 63, 61, 74, 77, 79, 82, 93, 90, 88, 85, 98,101,102,106,117,114,109,122,126,127,128,129},//10
  {21,20,16,15,27,32,44,39,51,56,68,63,75,80,92,87,99,104,116,111,123,128},//11*/
  {22,21,17,16,15,14,26,29,30,33,34,45,42,37,50,57,58,69,63,62,74,79,80,93,89,88,98,102,117,114,113,122,125,126,127,128,129,130},//12
  {22,21,17,16,15,14,13,26,34,45,38,37,50,56,57,69,65,64,63,74,80,81,93,86,85,98,101,106,117,114,113,109,122,126,127,128,129,130},//13
  {22,21,16,13,26,31,34,45,41,37,50,54,58,69,66,61,74,77,78,79,80,81,82,93,85,98,106,117,109,122,130},//14
  {22,21,18,17,16,15,14,13,26,29,45,42,50,53,54,55,69,64,63,62,74,81,82,93,85,98,101,106,117,114,113,110,109,122,126,127,128,129},//15
  {22,21,17,16,15,14,26,29,30,34,45,42,50,53,69,66,64,63,62,74,77,78,81,82,93,90,85,98,101,106,117,114,113,110,109,122,126,127,128,129},//16
  {22,21,18,17,16,15,14,13,26,29,34,45,37,50,57,69,63,74,79,93,88,98,102,117,113,122,126},//17
  {22,21,17,16,15,14,26,29,34,45,42,37,50,54,57,69,64,63,74,78,81,93,90,85,98,101,106,117,114,109,122,126,127,128,129},//18
  {22,21,17,16,15,14,26,29,34,45,42,37,50,53,58,69,66,62,61,74,78,79,80,82,93,85,98,106,117,114,110,122,126,127,128 },//19
  {22,21,20,19,15,14,13,25,28,29,31,35,42,40,36,52,53,55,59,68,67,64,60,74,75,79,83,94,93,88,84,97,103,107,118,112,108,121,122,123,124,125,128,129,130},//20
  {22,21,20,19,15,14,25,28,29,33,42,38,52,53,57,68,67,62,74,75,81,94,93,86,97,105,118,110,121,122,123,124,125,129}//21
);



int imagesLimit = 22;

int k = 100;

int r = 27;
int g = 98;
int b = 224;

int imageIndex = 0;
int totalPixels = 144;

//PUSH BUTTON SETEUP

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


void setup()
{
  
  //LED SETUP
  
  FastSPI_LED.setLeds(NUM_LEDS);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_SM16716);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_TM1809);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_LPD6803);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_HL1606);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_595);
  //FastSPI_LED.setChipset(CFastSPI_LED::SPI_WS2801);

  FastSPI_LED.setPin(PIN);
  
  FastSPI_LED.init();
  FastSPI_LED.start();

  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 
  
  
  //PUSH BUTTON SETEUP
  
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  //pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  //Serial.begin(9600);
  
}

void loop() { 
  
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      
      digitalWrite(ledPin, HIGH);

    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      digitalWrite(ledPin, LOW);
      
      
      for (int i = 0; i < totalPixels; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }
      
      // CHANGE DISPLAYED NUMBER
      //int arrayLength = 30;
      //int arrayLength =  sizeof(images[imageIndex]);
      //int arrayLength = sizeof(pgm_read_byte(&(images[imageIndex])));
  
      for (int i = 0; i < IMAGE_PIXELS; i++) {
        
        int pixel = images[imageIndex][i];  
        //int pixel = pgm_read_byte(&(images[imageIndex][i]));
        
        //leds[pixel].r = k;
        //leds[pixel].g = k;
        //leds[pixel].b = k;
        
        int dimmer = 1 * imagesLimit - imageIndex;
        
        leds[pixel].r = r - dimmer;
        leds[pixel].g = g - dimmer;
        leds[pixel].b = b - dimmer;
        
      }
      
      leds[0].r = 0;
      leds[0].g = 0;
      leds[0].b = 0;
        
      FastSPI_LED.show();
      
      imageIndex++;
      
    
      if (imageIndex == imagesLimit)
        imageIndex = 0;
      
      
      //
    }
  }
  // save the current state as the last state, 
  //for next time through the loop
  lastButtonState = buttonState;
 
}

