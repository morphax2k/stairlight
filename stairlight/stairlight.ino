#include "Arduino.h"
#include <cstairs.h>

// ################################################################################################
// ################################################################################################

#define DEBUG 1

// ################################################################################################
// ################################################################################################

#define buttonUp              22
#define buttonDown            23

#define lightSensor           24
#define lightSensorStatusLed  25

// ################################################################################################
// ################################################################################################

bool isAnimationRunning;

CStairs stairs;

// ################################################################################################
// ################################################################################################

void setup() {

  // no Animation is running at startup so set to false
  isAnimationRunning = false;

#if DEBUG
  Serial.begin( 9600);
#endif

  stairs.addHoldTimePotentiometer(    A0 /* analog in port*/)
//stairs.addStartDelayPotentiometer(  A1 /* analog in port*/)

  stairs.addStage( 2 /* analog pwm pin 2 */);
  stairs.addStage( 3 /* analog pwm pin 3 */);
  stairs.addStage( 4 /* analog pwm pin 4 */);
  stairs.addStage( 5 /* analog pwm pin 5 */);
  stairs.addStage( 6 /* analog pwm pin 6 */);
  stairs.addStage( 7 /* analog pwm pin 7 */);
  stairs.addStage( 8 /* analog pwm pin 8 */);
  stairs.addStage( 9 /* analog pwm pin 9 */);

  pinMode(buttonUp,               INPUT); 
  pinMode(buttonDown,             INPUT); 

  // setup the light sensor 
  pinMode(lightSensor,            INPUT);   // digital pin as input
  pinMode(lightSensorStatusLed,   OUTPUT);
}

// ################################################################################################
// ################################################################################################

bool checkButton(Direction direction) {
  
  AnimationStatus animationStatus;
  if (stairs.getAnimation(direction, &animationStatus)) {

    if (animationStatus == AnimationStatusOn && isAnimationRunning == false) {
      isAnimationRunning = true;
    }
    
    return (animationStatus == AnimationStatusOff) ? true : false;  
  }  
  
  // Error case
  return false;
  
}


// ################################################################################################
// ################################################################################################

void loop() 
{
  if (digitalRead(lightSensor) == LOW) {
    // switch of the status led because the sensor means it is light enough
    digitalWrite(lightSensorStatusLed, LOW);
    if (!isAnimationRunning) {
      // if nothing is to do just idle
      delay(1000);
      return;
    }    
  } 
  
  // digitalRead(lightSensor) == HIGH case
  digitalWrite(lightSensorStatusLed, HIGH);
  
  if (checkButton(DirectionUp)) {
    int buttonUpStatus    = digitalRead(buttonUp);
    if (buttonUpStatus == HIGH){
#if DEBUG
      Serial.println("stairs.setAnimation(DirectionUp, AnimationStatusOn)");
#endif
      // Wenn der buttonUp gedrückt ist (Das Spannungssignal ist hoch)   
      stairs.setAnimation(DirectionUp, AnimationStatusOn);
    }
  }

  if (checkButton(DirectionDown)) {
    int buttonDownStatus    = digitalRead(buttonDown);
    if (buttonDownStatus == HIGH){
#if DEBUG      
      Serial.println("setAnimation(DirectionDown, AnimationStatusOn)");
#endif
      // Wenn der buttonDown gedrückt ist (Das Spannungssignal ist hoch)  
      stairs.setAnimation(DirectionDown, AnimationStatusOn); 
    }
  }
  unsigned long currentTime = millis();
  isAnimationRunning = stairs.executeAnimation(currentTime);
  
  delay(2);
}
