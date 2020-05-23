#include <Arduino.h>
#include "MyFunctions.h"


int notRead = 1;
long MlsCounter = 0;
int LIGHTS= 0;
int BREAKING=0;
int BreakingSpeedold=0;
int Blink = 0;


void SoftPWM(int pin, int PWM) // 960 Hz
{
  int periode = (PWM<<2); //Periode 1024  durch 256 = >>8 also 10-8 << 
  if((MlsCounter <= micros())&&(notRead == 1)&&(periode!=0))
  {
    digitalWrite(pin, HIGH);
    MlsCounter = (micros()+periode);
    if(periode <= 256)
    {
      notRead = 0;
    }    
  }  
  
  if ((MlsCounter <= micros()) && (notRead == 0))
  {
    digitalWrite(pin, LOW);
    MlsCounter = (micros()+(1024-periode));
    notRead = 1;
  }  
}

int ReadPWM(int pin)
{
   int output = pulseIn(pin, HIGH, 25000);  
   return output;
}


void DayLightOn(int light)
{
  analogWrite(White ,light);
}

void NormalLightOn(int light)
{
  analogWrite(White ,light);
}

void Breaking(int light)
{
  analogWrite(Red ,light);
}

void BreakOn(int light)
{
  analogWrite(Red ,light);
}

void LightsOn()
{
  if(LIGHTS==0)
  { 
    DayLightOn(daylightbrigh);
    if(BREAKING==1)
    {
      Breaking(brakinglightbrigh);
    }
    else
    {
      BreakOn(breaklightbrigh);
    }
  }
  else
  { 
    NormalLightOn(normallightbrigh);
    if(BREAKING==1)
    {
      Breaking(brakinglightbrigh);
    }
    else
    {
      BreakOn(breaklightbrigh);
    }
  }
}

void BlinkLR()
{
  long OrangeBlinkArray[2] = {0, 0};
  
  
  for(int i=0; i < 1;i++)
  {
    OrangeBlinkArray[i] = ReadPWM(LRIN);
  }
  
  long OrangeBlink = 0;
  
  for(int i=0; i < 1;i++)
  {
    OrangeBlink += OrangeBlinkArray[i];  
    Serial.println(OrangeBlink);
  }

  if(millis() >= MlsCounter)
  {
    
    if(Blink == 1)
    {
      if (OrangeBlink >= 1560)
      {
        digitalWrite(Orange_R, HIGH);
        digitalWrite(Orange_L, LOW);
        Blink = 0;
        MlsCounter = millis()+500;
      }
      else if (OrangeBlink <= 2 )
      {
        digitalWrite(Orange_R, HIGH);
        digitalWrite(Orange_L, HIGH);
        Blink = 0;
        MlsCounter = millis()+500;
        if(LIGHTS==0)
        {
          LIGHTS=1;
        }
        else
        {
          LIGHTS=0;
        }
      }
      else if (OrangeBlink <= 1460)
      {
        digitalWrite(Orange_L, HIGH);
        digitalWrite(Orange_R, LOW);
        Blink = 0;
        MlsCounter = millis()+500;
      }
      else 
      {
        digitalWrite(Orange_R, LOW);
        digitalWrite(Orange_L, LOW);
        Blink = 1;
        MlsCounter = millis();
      }
    }
     else
    {
      digitalWrite(Orange_R, LOW);
      digitalWrite(Orange_L, LOW);
      Blink = 1;
      MlsCounter = millis()+500;
    }
  }
}

void BreakeEnabel()
{
  long BreakingSpeednew = ReadPWM(SpeedIN);

  if ((BreakingSpeednew < 1500)&&(BreakingSpeednew > 1470))
  {
    BREAKING=1;
    BreakingSpeedold = BreakingSpeednew;
  }
  else
  {
    BREAKING=0;
    BreakingSpeedold = BreakingSpeednew;  
  }
}

void StartUP()
{
  for (int a=0; a < 2; a++)
  {
    for(int i=0; i < 256; i++)  
    {
        analogWrite(Red,i);
        delay(4);
    }
    for(int i=0; i < 256; i++)  
    {
        analogWrite(Red,255-i);
        delay(2);
    }
    for(int i=0; i < 256; i++)  
    {
      analogWrite(White,i);
      delay(4);
    }
    for(int i=0; i < 256; i++)  
    {
      analogWrite(White,255-i);
      delay(2);
    }
    for(int i=0; i < 2; i++)  
    {
      digitalWrite(Orange_R,HIGH);
      delay(100);
      digitalWrite(Orange_R,LOW);
      delay(100);
      
    }
    for(int i=0; i < 2; i++)  
    {
      digitalWrite(Orange_L,HIGH);
      delay(100);
      digitalWrite(Orange_L,LOW);
      delay(100);
    }
  }
}
