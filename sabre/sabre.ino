#include <FastSPI_LED.h>

//#define NUM_LEDS 150
#define NUM_LEDS 6
// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

#define PIN 7
int k = 255;

void setup()
{
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
}

void loop() {
  
  for(int i = 0 ; i < NUM_LEDS; i++ ) {
      /*
      leds[i].r = k;
      leds[i].g = k;
      leds[i].b = k;
      */
      /*
      //orange
      leds[i].r = 242;
      leds[i].g = 197;
      leds[i].b = 61;
      */
      
      //green
      leds[i].r = 255;
      leds[i].g = 0;
      leds[i].b = 255;
  }
  FastSPI_LED.show();  
}
 
