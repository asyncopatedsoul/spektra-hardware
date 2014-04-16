

int rowCount = 3;
int colCount = 9;
int pinCount = rowCount + colCount;
int wait = 300;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i=0;i<pinCount;i++) {
    pinMode(i, OUTPUT);     
  }
   
}

void setPin(int pin, boolean output) {
  // first 9 pins mapped to columns
  // 0   1   2   3   4   5   6   7   8   
  // D0  D1  D2  D3  D4  D5  D6  D7  D8
  
  // last 3 pins mapped to rows
  // 9   10   11
  // D9  D10  D11
  
   if (output){
     digitalWrite(pin,HIGH);
   } else {
     digitalWrite(pin,LOW);
   }
   
}

void setAllCol(boolean setting) {
  for (int c=0;c<9;c++){
    setPin(c, setting);
  }  
}

void allColOn() {
  setAllCol(false);
}

void allColOff() {
  setAllCol(true);
}

void setCol(int col, boolean setting) {
  setPin(col, setting);
}


void allRow(boolean setting) {
  for (int r=9;r<12;r++) {
    setPin(r, setting);
  }  
}

void setRow(int row, boolean setting) {
  setPin(row+colCount, setting);  
}

void allRowOn(){
  allRow(true);
}

void allRowOff(){
  allRow(false);
}

void allOn() {
  allRowOn();
  allColOn();
}

void allOff() {
  allRowOff();
  allColOff();
}

void allLayer(int layer) {
  
  for (int i=0;i<3;i++) {
    if (i == layer) {
      digitalWrite(layer, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
  
  allColOff();
}

void singleOn(int col, int row) {
   allOff();
  
   for (int i=0;i<3;i++) {
    if (i == row) {
      setRow(i,true);
    } else {
      setRow(i,false);
    }
  }
  
  for (int i=0;i<9;i++) {
    if (i == col) {
      setCol(i,false);
    } else {
      setCol(i, true);
    }
  }
    
}

void allLayer(int row) {
  allOff();
  allColOn();
  setRow(row,true);
}

// the loop routine runs forever:
void loop() {
  
   // blink
   allOn();
   delay(wait);
   allOff();
   delay(wait);

   // elevator layers
   allLayer(0);
   delay(wait);
   allLayer(1);
   delay(wait);
   allLayer(2);
   delay(wait);
   allLayer(1);
   delay(wait);
   allLayer(0);
   delay(wait);
   
   // single cols
   for (int i=0;i<12;i++) {
     allOff();
     allRowOn();
     setCol(false);
     delay(wait);
   }
   
   // all individual
   for (int row=0;row<3;row++) {
   
     for (int col=0;col<9;col++) {
       singleOn(col,row);
       delay(wait);
     }
   
   }
 
}
