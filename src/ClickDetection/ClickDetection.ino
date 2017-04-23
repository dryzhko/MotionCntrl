#include <Keyboard.h>
#include <Mouse.h>

//set up inputs
const int indexFinger = A7; 
const int middleFinger = A9; 
const int ringFinger = A10; 
 
const int pins[] = {ringFinger, indexFinger, middleFinger};

//actions
char Keys[] =   {218,'i',217};

boolean currentPressed[] = {false, false, false};
 
const int threshold = 40;  // threshold value to decide when the detected sound is a knock or not
 
void setup()
{
  Serial.begin(115200);
  Serial.println("start");
  Keyboard.begin();
}
 
 
void loop()                    
{ 
  for (int i=0;i<3;i++) {
    delay(1);
    long total1 = 0;
    long start = millis();
    long total = 0;
    total =  analogRead(pins[i]);
 
    if ((total > threshold) && (! currentPressed[i])) {
      Serial.print("Key pressed #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = true;
      if(i!=1){
      Keyboard.press(Keys[i]);
      total = 0;
      }
      else{
        Mouse.click();
      }
      total = 0;
    } 
    else if ((total <= threshold) && (currentPressed[i])) {      
      // key was released (no touch, and it was pressed before)
      Serial.print("Key released #"); Serial.print(i);
      Serial.print(" ("); Serial.print(Keys[i]); Serial.println(")");
      currentPressed[i] = false;
      if(i!=1){
        Keyboard.release(Keys[i]);
        total = 0;
      }
      total = 0;
      
    }
    total = 0;
    
    delay(5);
  }
}


