// Made by Kipkay Kit Team Member: Aaron Arenas 
// On August 21, 2014

// Clock, Stopwatch, and Alarm run asynchronously to each other

// Clock will run through time and display AM and PM

// Stopwatch will run through 2 modes: Second Mode and Minute Mode
//    Second Mode will show seconds and milliseconds until it reaches 1 min
//    After 1 min, it will go into Minute Mode and show minutes and seconds 
//      until it reaches one hour and after on hour, it will reset itself

// Alarm will run only if button_c is held while the Clock is running.
// While in Alarm mode the display will blink to let you know you are running
//   the Alarm. In this mode, you can enable the Alarm go off at a certain time
//   or to disable it so it won't go off.

// Initializing the pins on ATmega328 for Clock Stopwatch Alarm

// Seven Segment display
int seg_a = A0;
int seg_b = A1;
int seg_c = A2;
int seg_d = A3;
int seg_e = A4;
int seg_f = A5;
int seg_g = 1;
int dot = 0;
int colon = 3;

int dig_colon = 2;
int dig_1 = 4;
int dig_2 = 5;
int dig_3 = 6;
int dig_4 = 7;

// Inputs
int but_a = 10;
int but_b = 11;
int but_c = 12;

// Status: Alarm
int statusLED = 8;

//Mode
int mode = 13;

// Buzzer
int buzzer = 9;

// Varibles: Modes
boolean StopwatchMode;
boolean ClockMode;

// digits for clock,stopwatch, alarm, and buzzer
int clock_minsOnes;
int clock_minsTens;
int clock_hoursOnes;
int clock_hoursTens;
int minsOnes;
int minsTens;
int hoursOnes;
int hoursTens;
int alarm_minsOnes;
int alarm_minsTens;
int alarm_hoursOnes;
int alarm_hoursTens;
boolean alarm_AM;
int buzzer_minsOnes;
int buzzer_minsTens;
int buzzer_hoursOnes;
int buzzer_hoursTens;
boolean buzzer_AM;

// incrementors
int i, j;

// Clock: States
boolean AM;

// Stopwatch: States
boolean MinMode;
boolean SecMode;
boolean RestMode;
String LastMode;

// Alarm: States
boolean EnabledAlarm;
boolean AlarmMode;
boolean Set;
boolean AlarmTriggered;

void setup(){
  
//  Serial.begin(9600);
  
  pinMode(seg_a,OUTPUT);
  pinMode(seg_b,OUTPUT);
  pinMode(seg_c,OUTPUT);
  pinMode(seg_d,OUTPUT);
  pinMode(seg_e,OUTPUT);
  pinMode(seg_f,OUTPUT);
  pinMode(seg_g,OUTPUT);
  pinMode(dot,OUTPUT);
  pinMode(colon,OUTPUT);
  pinMode(dig_colon,OUTPUT);
  pinMode(dig_1,OUTPUT);
  pinMode(dig_2,OUTPUT);
  pinMode(dig_3,OUTPUT);
  pinMode(dig_4,OUTPUT);
  pinMode(statusLED,OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(but_a,INPUT);
  pinMode(but_b,INPUT);
  pinMode(but_c,INPUT);
  pinMode(mode,INPUT);
  
// State init
  ClockMode = true;
  StopwatchMode = false;
  
// ClockMode init
  AM = true;
  
// StopwatchMode init  
  RestMode = true;
  LastMode = "SecMode";
  SecMode = false;
  MinMode = false;
  
// Alarm init
  AlarmMode = false;
  EnabledAlarm = false;
  alarm_AM = true;
  

// Digit init for each state
  clock_minsOnes = 0;
  clock_minsTens = 0;
  clock_hoursOnes = 2;
  clock_hoursTens = 1;
  minsOnes = 0;
  minsTens = 0;
  hoursOnes = 0;
  hoursTens = 0;
  alarm_minsOnes = 0;
  alarm_minsTens = 0;
  alarm_hoursOnes = 2;
  alarm_hoursTens = 1;
  
  digitalWrite(buzzer, HIGH);
}


// Determines mode and runs the Clock or Stopwatch
void loop(){
  ClockMode = isClock();
  StopwatchMode = isStopwatch();
  AlarmMode = isAlarm();
  
//  Serial.print(EnabledAlarm);
//  Serial.print(AlarmTriggered);
//  Serial.println(ClockMode);
  
  Clock();
  Stopwatch();
  Alarm();
  SoundAlarm(AlarmTriggered);
}
  
  
// Determines if the Clock should be ran
boolean isClock(){
  
  if(AlarmTriggered == false){
    if(digitalRead(mode) == LOW){
      return false;
    } else {
      return true;
    }
  } else {
    return false;
  }
}

// Determines if the Stopwatch should be ran
boolean isStopwatch(){
  
  if(AlarmTriggered == false){
    if(digitalRead(mode) == LOW){
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

// Determines if the Alarm should be ran
boolean isAlarm(){
    if(ClockMode == true){
        if(AlarmMode == true){
           if(digitalRead(but_c) == LOW){
             if(EnabledAlarm == false){
                 Set = true;
             } else {
                 Set = false;
             }
             delay(500);
             if(digitalRead(but_c) == LOW){
//                Serial.println("AlarmMode Changed to false");
                delay(500);
                return false;
             } else {
               return true;
             }
           }
      } else if(digitalRead(but_c) == LOW){
//              Set = true;
              delay(500);
               if(digitalRead(but_c) == LOW){
//                 Set = false;
//                  Serial.println("AlarmMode Changed to true");
                  delay(500);
                  return true;
               } else {
                 return false;
               }
    } else {
        return false;
    }   
  }

}

// This runs the Clock
void Clock(){  
  
// Initializes the buttons when running the Clock
// When but_a is pressed, it adds one to the hour
// When but_b is pressed, it adds one to the minute
// When but_c is held, it goes into AlarmMode

     if(ClockMode == true && AlarmMode == false && AlarmTriggered == false){
        if(digitalRead(but_a) == LOW){
          clock_hoursOnes++;
          delay(150);
          
          if(clock_hoursOnes == 2 && clock_hoursTens ==1){
            AM = !AM;
          }
          
          if(clock_hoursOnes > 2 && clock_hoursTens == 1){
            clock_hoursTens = 0;
            clock_hoursOnes = 1;
          } 
        }
    
      if(digitalRead(but_b) == LOW){
        clock_minsOnes++;
        delay(150);
      }
     }
     
// This determines each number on the 7 seg display
      if(i == 5997){
        clock_minsOnes++;
        i = 0;
      }
      
      if(clock_hoursTens == 1 && clock_hoursOnes == 2 && clock_minsTens == 5 
              && clock_minsOnes > 9){
    //        Serial.println("Overflow to 1");
            clock_minsOnes = 0;
            clock_minsTens = 0;
            clock_hoursOnes = 1;
            clock_hoursTens = 0;
          }
          
        if(clock_minsOnes > 9){
    //        Serial.println("clock_minsOnes is more that 9");
            clock_minsTens++;
            clock_minsOnes = 0;
          }
            
          if(clock_minsTens > 5){
    //        Serial.println("clock_minsTens is more that 5");
            clock_hoursOnes++;
            clock_minsTens = 0;
          }
          
          if(clock_hoursOnes > 9){
    //        Serial.println("clock_hoursOnes is more that 9");
            clock_hoursTens++;
            clock_hoursOnes = 0;
          }
        
        if(clock_hoursTens > 1){
          clock_hoursTens = 0;
        }
        
// This checks if the alarm should be triggered 

     if(ClockMode == true && AlarmMode == false && AlarmTriggered == false){
        if(buzzer_minsOnes == clock_minsOnes &&
            buzzer_minsTens == clock_minsTens &&
            buzzer_hoursOnes == clock_hoursOnes &&
            buzzer_hoursTens == clock_hoursTens && 
            buzzer_AM == AM &&
            EnabledAlarm == true){
              
//              Serial.println("Alarm has been triggered");
              
              AlarmTriggered = true;
         }
     }
 
// This prints the numbers onto the display when running the Clock
     if(ClockMode == true && AlarmMode == false && AlarmTriggered == false){ 
       
        if(clock_hoursTens != 1){
          ShowNum(-1, 1);
        } else {
          ShowNum(clock_hoursTens, 1);
   //     Serial.print(clock_hoursTens);
        }
      
        ShowNum(clock_hoursOnes, 2);
//          Serial.print(clock_hoursOnes);
        ShowNum(clock_minsTens, 3);
//          Serial.print(clock_minsTens);
        ShowNum(clock_minsOnes, 4);
//          Serial.println(clock_minsOnes);
        TimeColon(AM);
    }
        i++;
        
//        Serial.println(i);
}

// This runs the Stopwatch
void Stopwatch(){
  
// This initalizes the buttons when running the Stopwatch
// When but_a is pressed, it starts and stops the Stopwatch
// When but_b is pressed, it resets the Stopwatch

    if(StopwatchMode == true){
      if(digitalRead(but_a) == LOW && LastMode == "MinMode" && RestMode == true){
         delay(150);
         SecMode = false;
         MinMode = true;
         RestMode = false;
         LastMode = "SecMode";
       } else if(digitalRead(but_a) == LOW && MinMode == true){
           delay(150);
           SecMode = false;
           MinMode = false;
           RestMode = true;
           LastMode = "MinMode";
       } else if(digitalRead(but_a) == LOW && RestMode == true){
           delay(150);
           SecMode = true;
           MinMode = false;
           RestMode = false;
           LastMode = "SecMode";
       } else if(digitalRead(but_a) == LOW && SecMode == true){
           delay(150);
           SecMode = false;
           MinMode = false;
           RestMode = true;
           LastMode = "SecMode";
       }
    
      if(digitalRead(but_b) == LOW){
          minsOnes = 0;
          minsTens = 0;
          hoursOnes = 0;
          hoursTens = 0;
          j = 0;
          RestMode = true;
          SecMode = false;
          MinMode = false;
          LastMode = "SecMode";
      }
    }
    
// This finds the numbers to display
    
        if(SecMode == true){
          if(j == 1){
              minsOnes++;
              j = 0;
          }
        }
       
       if(MinMode == true){
          if(j == 100){
             minsOnes++;
            j = 0;
          }
        }
        
       if(SecMode == true){
          if(hoursTens == 5 && hoursOnes == 9 && minsTens == 9 
              && minsOnes > 9){
      //      Serial.println("Overflow to MinMode");
              minsOnes = 0;
              minsTens = 0;
              hoursOnes = 1;
              hoursTens = 0;
              MinMode = true;
              SecMode = false;
              LastMode = "SecMode";
         }
       } 
      
       if(MinMode == true){
          if(hoursTens == 5 && hoursOnes == 9 && minsTens == 5 
              && minsOnes > 9){
    //      Serial.println("Overflow to RestMode");
              minsOnes = 0;
              minsTens = 0;
              hoursOnes = 0;
              hoursTens = 0;
              MinMode = false;
              SecMode = false;
              RestMode = true;
              LastMode = "SecMode";
         }
       }
         
          if(minsOnes > 9){
      //        Serial.println("clock_minsOnes is more that 9");
              minsTens++;
              minsOnes = 0;
            }
            
         if(SecMode == true){     
            if(minsTens > 9){
      //        Serial.println("clock_minsTens is more that 5");
              hoursOnes++;
              minsTens = 0;
            }
         } else if(MinMode == true){
             if(minsTens > 5){
      //        Serial.println("clock_minsTens is more that 5");
              hoursOnes++;
              minsTens = 0;
            }
            
         }
            
            if(hoursOnes > 9){
      //        Serial.println("clock_hoursOnes is more that 9");
              hoursTens++;
              hoursOnes = 0;
            }
            
//  Shows number on the display when the Stopwatch is running 
     if(StopwatchMode == true){  
        if(RestMode == true){
          ShowNum(hoursTens, 1);
        } else if(hoursTens == 0){
           ShowNum(-1, 1);
        } else { 
            ShowNum(hoursTens, 1);
//            Serial.print(hoursTens);
        }
            ShowNum(hoursOnes, 2);
//              Serial.print(hoursOnes);
            ShowNum(minsTens, 3);
//              Serial.print(minsTens);
            ShowNum(minsOnes, 4);
//              Serial.println(minsOnes);
            TimeColon(true);
        //      Serial.print("Printed Colon");
        //      Serial.println(" ");    
       }
            
      if(RestMode == false){    
          j++;
      }
    }    
    
// This is what enables the alarm    
void Alarm(){
  
  if(AlarmMode == true){
    
// This initalizes the buttons when in the Alarm Mode
// When but_a is pressed, it will add one to the hour
// When but_b is pressed, it will add one to the min
// When but_c is pressed, it sets the time for the alarm to go off
      
      if(digitalRead(but_a) == LOW){
      alarm_hoursOnes++;
      delay(150);
      
      if(alarm_hoursOnes == 2 && alarm_hoursTens == 1){
        alarm_AM = !alarm_AM;
      }
      if(alarm_hoursOnes > 2 && alarm_hoursTens == 1){
        alarm_hoursTens = 0;
        alarm_hoursOnes = 1;
        
        } 
      }
    
      if(digitalRead(but_b) == LOW){
        alarm_minsOnes++;
        delay(150);
      }
      
// This set the time the alarm should go off at
       
      if(Set == true){
            buzzer_minsOnes = alarm_minsOnes;
            buzzer_minsTens = alarm_minsTens;
            buzzer_hoursOnes = alarm_hoursOnes;
            buzzer_hoursTens = alarm_hoursTens;
            buzzer_AM = alarm_AM;
            digitalWrite(statusLED, HIGH);
            EnabledAlarm = true;
            
//            Serial.println("EnabledAlarm has been enabled");
//            Serial.print("Alarm will go off at ");
//            Serial.print(buzzer_hoursTens);
//            Serial.print(buzzer_hoursOnes);
//            Serial.print(buzzer_minsTens);
//            Serial.print(buzzer_minsOnes);
//            
//            if(buzzer_AM == false){
//              Serial.println(" AM");
//            } else {
//              Serial.println(" PM");
//            }
              
          
      } else {
            digitalWrite(statusLED, LOW);
            EnabledAlarm = false;
            
//            Serial.println("EnabledAlarm has been disabled");
      }
      
      
// This determines each number on the 7 seg display
       if(alarm_hoursTens == 1 && alarm_hoursOnes == 2 && alarm_minsTens == 5 
              && alarm_minsOnes > 9){
    //        Serial.println("Overflow to 1");
            alarm_minsOnes = 0;
            alarm_minsTens = 0;
            alarm_hoursOnes = 1;
            alarm_hoursTens = 0;
          }
          
        if(alarm_minsOnes > 9){
    //        Serial.println("clock_minsOnes is more that 9");
            alarm_minsTens++;
            alarm_minsOnes = 0;
          }
            
          if(alarm_minsTens > 5){
    //        Serial.println("clock_minsTens is more that 5");
            alarm_hoursOnes++;
            alarm_minsTens = 0;
          }
          
          if(alarm_hoursOnes > 9){
    //        Serial.println("clock_hoursOnes is more that 9");
            alarm_hoursTens++;
            alarm_hoursOnes = 0;
          }
        
        if(alarm_hoursTens > 1){
          alarm_hoursTens = 0;
        }
        
// This prints the numbers onto the 7 seg display
        
        if(alarm_hoursTens != 1){
          delay(5);
          ShowNum(-1, 1);
        } else {
          delay(5);
          ShowNum(alarm_hoursTens, 1);
//   Serial.print(alarm_hoursTens);
        }
        delay(5);
        ShowNum(alarm_hoursOnes, 2);
//    Serial.print(alarm_hoursOnes);
        delay(5);
        ShowNum(alarm_minsTens, 3);
//   Serial.print(alarm_minsTens);
        delay(5);
        ShowNum(alarm_minsOnes, 4);
//     Serial.println(alarm_minsOnes);
        delay(5);
        TimeColon(alarm_AM);
        
  }
}

// This is what sounds alarm to go off and on
void SoundAlarm(boolean state){
  if(state == true){
    
// The activates the buzzer
    
    digitalWrite(buzzer, LOW);
    
// This prints the time of the alarm you set and flashes the statusLED
    
      digitalWrite(statusLED, HIGH);
      ShowNum(buzzer_minsOnes,4);
      ShowNum(buzzer_minsTens,3);
      ShowNum(buzzer_hoursOnes,2);

      if(alarm_hoursTens != 1){
          ShowNum(-1, 1);
        } else {
          ShowNum(buzzer_hoursTens,1);
        }
        
      TimeColon(buzzer_AM);
          
// This what turns off the alarm          
      
      if(digitalRead(but_a) == LOW || digitalRead(but_b) == LOW || 
          digitalRead(but_c) == LOW){
            
//            Serial.println("Alarm deactivated");
            
            ShowNum(-1,1);
            ShowNum(-1,2);
            ShowNum(-1,3);
            ShowNum(-1,4);

// Turns off buzzer and statusLED
            digitalWrite(buzzer, HIGH);
            digitalWrite(statusLED, LOW);
            
            AlarmTriggered = false;
            EnabledAlarm = false;
            
            delay(500);
          }
  }
}
            

// This shows the right number at the right position on the display

void ShowNum(int num, int digit){
  
  if(digit == 1){
    digitalWrite(dig_1, HIGH);
  }
  else if(digit == 2){
    digitalWrite(dig_2, HIGH);
  }
  else if(digit == 3){
    digitalWrite(dig_3, HIGH);
  }  
  else if(digit == 4){
    digitalWrite(dig_4, HIGH);
  }
  
  if(num == 0){
    zero();
  } 
  else if(num == 1){
    one();
  }
  else if(num == 2){
    two();
  }  
  else if(num == 3){
    three();
  }
  else if(num == 4){
    four();
  }  
  else if(num == 5){
    five();
  }
  else if(num == 6){
    six();
  }  
  else if(num == 7){
    seven();
  }
  else if(num == 8){
    eight();
  }  
  else if(num == 9){
    nine();
  }
  else {
    Blank();
  }
  
  delayMicroseconds(1825);
  RemoveNum();
}

// This print the colon in the middle of the display
// The Clock will show AM when there is no dot between two rightmost digits
// and PM will show a dot
void TimeColon(boolean AM){
  digitalWrite(colon, HIGH);

  
  if(AM == false){
    digitalWrite(dig_colon, HIGH);
  }
  
  delayMicroseconds(1825);
  RemoveNum();
}

// This is how each number is written to the 7 segment display

void one(){
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
}

void two(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_d, 255);
  analogWrite(seg_e, 255);
  digitalWrite(seg_g, HIGH);
}

void three(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_d, 255);
  digitalWrite(seg_g, HIGH);
}

void four(){
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_f, 255);
  digitalWrite(seg_g, HIGH);
}

void five(){
  analogWrite(seg_a, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_d, 255);
  analogWrite(seg_f, 255);
  digitalWrite(seg_g, HIGH);
}

void six(){
  analogWrite(seg_a, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_d, 255);
  analogWrite(seg_e, 255);
  analogWrite(seg_f, 255);
  digitalWrite(seg_g, HIGH);
}

void seven(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
}

void eight(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_d, 255);
  analogWrite(seg_e, 255);
  analogWrite(seg_f, 255);
  digitalWrite(seg_g, HIGH);
}

void nine(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_f, 255);
  digitalWrite(seg_g, HIGH);
}

void zero(){
  analogWrite(seg_a, 255);
  analogWrite(seg_b, 255);
  analogWrite(seg_c, 255);
  analogWrite(seg_d, 255);
  analogWrite(seg_e, 255);
  analogWrite(seg_f, 255);
}

// Prints a blank digit
void Blank(){
  analogWrite(seg_a, 0);
  analogWrite(seg_b, 0);
  analogWrite(seg_c, 0);
  analogWrite(seg_d, 0);
  analogWrite(seg_e, 0);
  analogWrite(seg_f, 0);
  digitalWrite(seg_g, LOW);
  digitalWrite(dot, LOW);
}

// Erases a number on the display
void RemoveNum(){
  analogWrite(seg_a, 0);
  analogWrite(seg_b, 0);
  analogWrite(seg_c, 0);
  analogWrite(seg_d, 0);
  analogWrite(seg_e, 0);
  analogWrite(seg_f, 0);
  digitalWrite(seg_g, LOW);
  digitalWrite(dot, LOW);
  digitalWrite(dig_colon,LOW);
  digitalWrite(colon, LOW);
  digitalWrite(dig_1, LOW);
  digitalWrite(dig_2, LOW);
  digitalWrite(dig_3, LOW);
  digitalWrite(dig_4, LOW);
}

// Made by Kipkay Kit Team Member: Aaron Arenas  
