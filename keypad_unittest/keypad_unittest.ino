void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A5);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  
  //Serial.println(voltage);
  //Serial.println(sensorValue);
  
  int keypadPin = A5;
  int sampleSize = 20;
  float resStream=0;
 int resStreamCount=0;
    
    do {
      resStream+=analogRead(keypadPin) * (5.0 / 1023.0);
      //resStream+=analogRead(keypadPin);
      resStreamCount++;
    } while (resStreamCount<sampleSize);
    
    resStream = resStream/sampleSize;
    Serial.println(resStream);
    
    //delay(500);
}
