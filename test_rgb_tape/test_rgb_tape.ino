#include <FastSPI_LED.h>

//#define NUM_LEDS 150
#define NUM_LEDS 144
// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;

#define PIN 7

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
  
  //run all animations through various palettes of 3 colors
  int NUM_PALETTES = 3;
  
  int maxbr = 20;
  //color palettes
  /*
  array cube_matrix[3][3][3] = [
    {
        { {0}, {0}, {0} },
        { {0}, {0}, {0} },
        { {0}, {0}, {0} }
    },
    {
        { {0}, {0}, {0} },
        { {0}, {0}, {0} },
        { {0}, {0}, {0} }
    },
    {
        { {0}, {0}, {0} },
        { {0}, {0}, {0} },
        { {0}, {0}, {0} }
    }
  ];
  */
  for (int p = 0; p < NUM_PALETTES; p++) {  
  
  // one at a time
  for(int j = 0; j < 3; j++) { 
    
    //go one way
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      memset(leds, 0, NUM_LEDS * 3);
      switch(j) { 
        case 0: leds[i].r = 255; break;
        case 1: leds[i].g = 255; break;
        case 2: leds[i].b = 255; break;
      }
      FastSPI_LED.show();
      delay(10);
    }
    
    //go the other way
    for(int i = NUM_LEDS-1; i > 0; i-- ) {
      memset(leds, 0, NUM_LEDS * 3);
      switch(j) { 
        case 0: leds[i].r = maxbr; break;
        case 1: leds[i].g = maxbr; break;
        case 2: leds[i].b = maxbr; break;
      }
      FastSPI_LED.show();
      delay(10);
    }
    
  }

  // growing/receeding bars
  for(int j = 0; j < 3; j++) { 
    memset(leds, 0, NUM_LEDS * 3);
    for(int i = 0 ; i < NUM_LEDS; i++ ) {
      switch(j) { 
        case 0: leds[i].r = maxbr; break;
        case 1: leds[i].g = maxbr; break;
        case 2: leds[i].b = maxbr; break;
      }
      FastSPI_LED.show();
      delay(10);
    }
    for(int i = NUM_LEDS-1 ; i >= 0; i-- ) {
      switch(j) { 
        case 0: leds[i].r = 0; break;
        case 1: leds[i].g = 0; break;
        case 2: leds[i].b = 0; break;
      }
      FastSPI_LED.show();
      delay(1);
    }
  }
  
  // Fade in/fade out
    //repeat r times
    for (int r = 0; r < 2; r++) {
      
      for(int j = 0; j < 3; j++ ) { 
      memset(leds, 0, NUM_LEDS * 3);
        
      for(int k = 0; k < maxbr; k++) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(1);
    }
    for(int k = maxbr; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(1);
    }
      
    }
    
  }
  
  // Flash
    //repeat r times
    for (int r = 0; r < 6; r++) {
      
      int d = 500;
      
      for(int j = 0; j < 3; j++ ) { 
      memset(leds, 0, NUM_LEDS * 3);
        
      //for(int k = 0; k < 256; k++) { 
      /*
      for(int i = 0; i < NUM_LEDS; i++ ) {
        int k = 0;
        
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(d);
      */
    //}
    //for(int k = 255; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
      int k = maxbr;
        
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(d);
    }
      
    //}
    
  }//end r repeat
  
  
    
  // Strobe
    //repeat r times
    for (int r = 0; r < 25; r++) {
      
      int d = 200;
      
      for(int j = 0; j < 3; j++ ) { 
      memset(leds, 0, NUM_LEDS * 3);
        
    //all ON
    
    //for(int k = 255; k >= 0; k--) { 
      for(int i = 0; i < NUM_LEDS; i++ ) {
      int k = maxbr;
        
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
        
      } 
      FastSPI_LED.show();
      delay(d);
      
       //for(int k = 0; k < 256; k++) { 
      
      //all OFF
      for(int i = 0; i < NUM_LEDS; i++ ) {
        int k = 0;
        
        switch(j) { 
          case 0: leds[i].r = k; break;
          case 1: leds[i].g = k; break;
          case 2: leds[i].b = k; break;
        }
      }
      FastSPI_LED.show();
      delay(100);
      
    //}
    } //end r repeat
      
    }
  
    }//end palette loop
    
}//end void loop()
