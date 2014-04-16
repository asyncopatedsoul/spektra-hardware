

int rowCount = 3;
int colCount = 9;
int pinCount = rowCount + colCount;
int wait = 300;

int dropDelay = 125;

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

void dropThroughColumn(int col,int dropDelay) {
  allOff();
  
  for (int row=3;row>=0;row--) {
      singleOn(col,row);
      delay(dropDelay);
  }
}

void rainDrops() {
  
  // random column
  // http://arduino.cc/en/Reference/Random
  
  int col = random(0,16);
  dropThroughColumn(col,dropDelay);
  
}

// the loop routine runs forever:
void loop() {

   rainDrops();
 
}
