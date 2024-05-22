//****************LIBRAIRIE*****************
#include <Arduino.h>
#include "Adafruit_ZeroTimer.h"
//******************OBJET*******************
extern Adafruit_ZeroTimer zerotimer;
//*****************VARIABLE****************
extern float freq; // 1 KHz -> 1ms
extern int cpt;
//****************FONCTION*****************
void TC5_Handler(void); 
void TimerCallback0(void);
void init_interrupt(float);
