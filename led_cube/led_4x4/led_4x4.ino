int led = 13;
int colCount = 16;
int rowCount = 4;
int multiplexDelay = 300;
int frameDelay = 512;
float timeCounter = 0;

int frameCount = 3;
int ledsPerFrame[3] = {8,32,8};
boolean frames[3][4][4][4] = 
  {
    //1
    {
      {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      }
    },
    //2
    {
      {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
      },
      {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
      },
      {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
      },
      {
        {1, 1, 1, 1},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {1, 1, 1, 1}
      }
    },
    //3
    {
      {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
      },
      {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      },
      {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
      },
      {
        {1, 0, 0, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {1, 0, 0, 1}
      }
    }
  };

// the setup routine runs once when you press reset:
void setup() {                
  Serial.begin(9600);
  
  // initialize the digital pin as an output.
  for (int i=0;i<14;i++) {
    pinMode(i, OUTPUT);     
  }

  pinMode(A0, OUTPUT);     
  pinMode(A1, OUTPUT);  
  
  pinMode(A2, OUTPUT);   
  pinMode(A3, OUTPUT);   
  pinMode(A4, OUTPUT);   
  pinMode(A5, OUTPUT);   
}

void setPin(int pin, boolean output) {
   if (pin <=13) {
     if (output){
       digitalWrite(pin,HIGH);
     } else {
       digitalWrite(pin,LOW);
     }
   } else if (pin==14) {
     if (output){
       digitalWrite(A0,HIGH);
     } else {
       digitalWrite(A0,LOW);
     }
   } else if (pin==15) {
     if (output){
       digitalWrite(A1,HIGH);
     } else {
       digitalWrite(A1,LOW);
     }
   } else if (pin==16) {
     if (output){
       digitalWrite(A2,HIGH);
     } else {
       digitalWrite(A2,LOW);
     }
   } else if (pin==17) {
     if (output){
       digitalWrite(A3,HIGH);
     } else {
       digitalWrite(A3,LOW);
     }
   } else if (pin==18) {
     if (output){
       digitalWrite(A4,HIGH);
     } else {
       digitalWrite(A4,LOW);
     }
   } else if (pin==19) {
     if (output){
       digitalWrite(A5,HIGH);
     } else {
       digitalWrite(A5,LOW);
     }
   }
   
}

void setAllCol(boolean setting) {
  for (int i=0;i<colCount;i++) {
    setPin(i,setting);    
  }
};

void setAllRow(boolean setting) {
  for (int i=0;i<rowCount;i++) {
    setPin(i+colCount,setting);    
  }
}

void allOn() {
  setAllCol(false);
  setAllRow(true);
}

void allOff() {
  setAllCol(true);
  setAllRow(false);
}

void singleOn(int col, int row) {
   for (int i=0;i<colCount;i++) {
     if (col==i) {
       setPin(i,false);
     } else {
       setPin(i,true); 
     }
   }
   
   for (int i=0;i<rowCount;i++) {
     if (row+colCount==i+colCount) {
       setPin(i+colCount,true);
     } else {
       setPin(i+colCount,false);
     }
   }
   
   delayMicroseconds(multiplexDelay);
   allOff();
}

int pointToCol(int x, int z) {
  return z*4+x;
}

void pointToPin(int x, int y, int z, boolean setting) {
  int col = pointToCol(x,z);
  if (setting){
    singleOn(col,y);
  }
}


void renderFrame(boolean frame[4][4][4]) {
  for (int y=0;y<4;y++) {
    for (int z=0;z<4;z++) {
      for (int x=0;x<4;x++) {
        pointToPin(x,y,z,frame[y][z][x]);
      }
    } 
  }
 //delay(frameDelay);
}



void loop() {

  for (int f=0;f<frameCount;f++) {
    
    while(timeCounter<frameDelay) {
      renderFrame(frames[f]);
      int increment = ledsPerFrame[f]/frameDelay;
      Serial.print(increment);
      Serial.print("\n");
      timeCounter+=increment;
      Serial.print(timeCounter);
      Serial.print("\n");
    }
    
    timeCounter=0;
  }
  //renderFrame(frames[0]);
  
    
//  singleOn(0,0);
//  singleOn(4,0);
//  singleOn(8,0);
//  singleOn(12,0);
//  singleOn(frames[0][0][0][0],0);
  
  //allFlash(250);
}

void allFlash(int wait) {
  allOn();
  delay(wait);
  allOff();
  delay(wait);
}
