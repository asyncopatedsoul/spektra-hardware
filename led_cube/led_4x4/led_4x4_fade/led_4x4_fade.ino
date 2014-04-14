int led = 13;
int colCount = 16;
int rowCount = 4;
int multiplexDelay = 300;
int frameDelay = 100;
//int frameDelay = 512;
float timeCounter = 0;

int frameCount = 3;
//int ledsPerFrame[3] = {8,32,8};
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
}

void dropThroughColumn(int col,int dropDelay) {
  for (int row=3;row>=0;row--) {
      singleOn(col,row);
      delay(dropDelay);
  }
}

void rainDrops() {
 int col = random(0,16);
  dropThroughColumn(col,75);
  
}

void fadeAll(int fadeDelay) {
  setAllCol(false);
  
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(A5, fadeValue); 
    analogWrite(A4, fadeValue);  
    analogWrite(A3, fadeValue);
    analogWrite(A2, fadeValue);
    // wait for 30 milliseconds to see the dimming effect    
    delay(fadeDelay);                            
  } 
  
}

void loop() {
  fadeAll(30);
}
