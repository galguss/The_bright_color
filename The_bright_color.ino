#include <ComponentObject.h>
#include <RangeSensor.h>
#include <SparkFun_VL53L1X.h>
#include <vl53l1x_class.h>
#include <vl53l1_error_codes.h>
  
#include <Wire.h>
#include "SparkFun_VL53L1X.h"

SFEVL53L1X distanceSensor;

#define sda 4
#define scl 5

#define ledBlue 6
#define ledGreen 11
#define ledYellow 10
#define ledRed 9

 
#define LONG_LEDS 4
int Leds[LONG_LEDS]= {
  ledBlue,
  ledGreen,
  ledYellow,
  ledRed
};



void setup() {
  for(int i = 0; i < LONG_LEDS; i++){
    pinMode(Leds[i], OUTPUT);
  }
  Wire.begin();
  Serial.begin(9600);
  
}

int distanceCM(){
    distanceSensor.startRanging();
    int distance = distanceSensor.getDistance();
    distanceSensor.stopRanging();

    int distanceCM = distance / 10;
    
    return distanceCM;
}
int distanceSum(){
   int sum = 0;
  for(int D = 0; D < 6; D++){
    sum += distanceCM();
  }
   sum /= 6;
  return sum;
}

void yellow_on(){
  for(int R =0; R <LONG_LEDS; R++){
    if(R == 2){
      digitalWrite(Leds[2], HIGH);
    }else{
      digitalWrite(Leds[R], LOW);
    }
  }
}
void Blue_on(){
  for(int R =0; R <LONG_LEDS; R++){
    if(R == 0){
      digitalWrite(Leds[0], HIGH);
    }else{
      digitalWrite(Leds[R], LOW);
    }
  }
}
void Green_on(){
  
  for(int R =0; R <LONG_LEDS; R++){
    if(R == 1){
      digitalWrite(Leds[1], HIGH);
    }else{
      digitalWrite(Leds[R], LOW);
    }
  }
}
void Red_on(){
  for(int R =0; R <LONG_LEDS; R++){
    if(R == 3){
      digitalWrite(Leds[3], HIGH);
    }else{
      digitalWrite(Leds[R], LOW);
    }
  }
}

void loop() { 
  if((distanceSum()> 6) && (distanceSum() < 12)){
    Red_on();
  }else if((distanceSum()> 13)&& (distanceSum() < 30)){
    Green_on();
  }else if((distanceSum()> 31)&& (distanceSum() < 40)){
    Blue_on();
  }else if((distanceSum()> 41)&& (distanceSum() < 50)){
    yellow_on();
  } else {
    for(int L = 0; L < LONG_LEDS; L++){
      digitalWrite(Leds[L], LOW);
    }
  }
  
  Serial.print("distance(CM): ");
  Serial.println(distanceSum());

  delay(500);
}
