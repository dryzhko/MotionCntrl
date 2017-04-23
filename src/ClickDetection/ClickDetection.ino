#include <Keyboard.h>
#include <Mouse.h>

//set up inputs
const int indexFinger = A7; 
const int middleFinger = A9; 
const int ringFinger = A10; 

const int threshold = 40;
 
void setup(){
  Keyboard.begin();
  Mouse.begin();
}

void loop(){
  int clck = analogRead(indexFinger);
  int dwn = analogRead(middleFinger);
  int up = analogRead(ringFinger);

  if(clck > threshold){
    Mouse.click();
    delay(500);
  }

  if(dwn > threshold){
    Keyboard.press(217);
    delay(1000);
    Keyboard.release(217);
  }

  if(up > threshold){
    Keyboard.press(218);
    delay(1000);
    Keyboard.release(218);
  }

  
}

