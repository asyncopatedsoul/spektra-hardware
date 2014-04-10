int led = 13;
int pinCount = 12;
int wait = 300;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (int i=0;i<pinCount;i++) {
    pinMode(i, OUTPUT);     
  }
   
}

void allColOff() {
   digitalWrite(3, LOW);  
   digitalWrite(4, LOW); 
   digitalWrite(5, LOW);
   digitalWrite(6, LOW);  
   digitalWrite(7, LOW); 
   digitalWrite(8, LOW);
   digitalWrite(9, LOW);  
   digitalWrite(10, LOW); 
   digitalWrite(11, LOW);
}

void allColHigh() {
  digitalWrite(3, HIGH);  
   digitalWrite(4, HIGH); 
   digitalWrite(5, HIGH);
   digitalWrite(6, HIGH);  
   digitalWrite(7, HIGH); 
   digitalWrite(8, HIGH);
   digitalWrite(9, HIGH);  
   digitalWrite(10, HIGH); 
   digitalWrite(11, HIGH);
}

void allOn() {
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);     
  digitalWrite(2, HIGH);
  
   allColOff();
}

void allOff() {
   digitalWrite(0, LOW);
   digitalWrite(1, LOW);     
   digitalWrite(2, LOW);
  
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

void allCol(int col){
  
  
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);     
    digitalWrite(2, HIGH);
    
    allColHigh();
    
    digitalWrite(col+3, LOW);
}

void singleOn(int col, int layer) {
   allOff();
  
   for (int i=0;i<3;i++) {
    if (i == layer) {
      digitalWrite(layer, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
  
  for (int i=0;i<9;i++) {
    if (i == col) {
      digitalWrite(i+3, LOW);
    } else {
      digitalWrite(i+3, HIGH);
    }
  }
    
}

// the loop routine runs over and over again forever:
void loop() {
  //allOff();
  //allOn();
  //singleOn(0,1);
 
   allOn();
   delay(wait);
   allOff();
   delay(wait);
   ///*
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
     allCol(i);
     delay(wait);
   }
   
   // all individual
   for (int row=0;row<3;row++) {
   
     for (int col=0;col<9;col++) {
       singleOn(col,row);
       delay(wait);
     }
   
   }
  //*/ 
}
