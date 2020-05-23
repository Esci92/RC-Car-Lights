#ifndef MyFunctions_H
#define MyFunctions_H

//PWM Pins
int extern Red;
int extern Orange_R;
int extern Orange_L;
int extern White;
int extern LRIN;
int extern SpeedIN;

//Var


//Defines
#define normallightbrigh 255
#define daylightbrigh 20
#define breaklightbrigh 40
#define brakinglightbrigh 255

int extern notRead;
long extern MlsCounter;
int extern LIGHTS;
int extern BREAKING;

void SoftPWM(int pin, int PWM);
int ReadPWM(int pin);
void LightsOn();
void BlinkLR();
void BreakeEnabel();
void StartUP();


#endif
