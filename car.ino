#include "MyFunctions.h"

int Red = 10;
int Orange_R = 4;
int Orange_L = 5;
int White = 9;
int LRIN = 6;
int SpeedIN = 3;
int oneshot = 0;

void setup() 
{
  pinMode(Red,      OUTPUT);
  pinMode(White,    OUTPUT);
  pinMode(Orange_R, OUTPUT);
  pinMode(Orange_L, OUTPUT);
  pinMode(LRIN,     INPUT);
  pinMode(SpeedIN,  INPUT);
  Serial.begin(9600);
}


void loop() 
{
  if(oneshot == 0) 
  {
    StartUP();
    oneshot = 1;
  }
    LightsOn();
    BlinkLR();
    BreakeEnabel();
    
    
}
