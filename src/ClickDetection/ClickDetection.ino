#include <Keyboard.h>
#include <Mouse.h>

const int indexFinger = A7; // the piezo is connected to analog pin 9 (aka D9)
const int middleFinger = A9; // the piezo is connected to analog pin 7 (aka D6)
const int ringFinger = A10; // the piezo is connected to analog pin 10 (aka D10)
//const int pinkyFinger = A11; // the piezo is connected to analog pin 11 (aka D12)
 
const int pins[] = {ringFinger, indexFinger, middleFinger};

char Keys[] =   {218,'i',217};

boolean currentPressed[] = {false, false, false};
 
const int threshold = 40;  // threshold value to decide when the detected sound is a knock or not
 
void setup()
{
  //while (!Serial)
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
 
    // check if we are sensing that a finger is touching
    // and that it wasnt already pressed
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


