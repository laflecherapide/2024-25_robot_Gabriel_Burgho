//****************LIBRAIRIE*****************
#include "interrupt.h"
#include "robot.h"
//******************OBJET*******************
Adafruit_ZeroTimer zerotimer = Adafruit_ZeroTimer(5);
//*****************VARIABLE****************
int cpt = 0;
volatile bool togglepin = false;
//*****************FONCTION*****************
void TC5_Handler() 
{
  Adafruit_ZeroTimer::timerHandler(5);
}
void TimerCallback0(void)
{
  //display.setCursor(0, 0);
  if(token_speed_choice)
  {
    switch (mode_de_fonctionnement) 
  {
    case mode_bluetooth:
      display.setCursor(0, 0);
      display.println("bluetooth");
      display_speed();
      refresh_display();
      bluetooth(); //recupere la data bluetooth et switch case
      break;
    case mode_auto:
      display.setCursor(0, 0);
      display.println("automatic");
      display_speed();
      refresh_display();
      //distance_gauche = get_distance_gauche();
      //distance_droite = get_distance_droite();
      automatic(7); //parametre: distance min en cm
      avancer_droite(10);
      avancer_gauche(10);
      break;
    default:
      refresh_display();
      avant_choix();//todo
      mode_de_fonctionnement = choix_user();//permet le choix du mode
      break;
  }
  }
}

void init_interrupt(float freq)
{
  Serial.println("Timer callback tester");
 
  Serial.print("Desired freq (Hz):");
  Serial.println(freq);
 
  // Set up the flexible divider/compare
  uint16_t divider  = 1;
  uint16_t compare = 0;
  tc_clock_prescaler prescaler = TC_CLOCK_PRESCALER_DIV1;
 
  if ((freq < 24000000) && (freq > 800)) {
    divider = 1;
    prescaler = TC_CLOCK_PRESCALER_DIV1;
    compare = 48000000/freq;
  } else if (freq > 400) {
    divider = 2;
    prescaler = TC_CLOCK_PRESCALER_DIV2;
    compare = (48000000/2)/freq;
  } else if (freq > 200) {
    divider = 4;
    prescaler = TC_CLOCK_PRESCALER_DIV4;
    compare = (48000000/4)/freq;
  } else if (freq > 100) {
    divider = 8;
    prescaler = TC_CLOCK_PRESCALER_DIV8;
    compare = (48000000/8)/freq;
  } else if (freq > 50) {
    divider = 16;
    prescaler = TC_CLOCK_PRESCALER_DIV16;
    compare = (48000000/16)/freq;
  } else if (freq > 12) {
    divider = 64;
    prescaler = TC_CLOCK_PRESCALER_DIV64;
    compare = (48000000/64)/freq;
  } else if (freq > 3) {
    divider = 256;
    prescaler = TC_CLOCK_PRESCALER_DIV256;
    compare = (48000000/256)/freq;
  } else if (freq >= 0.75) {
    divider = 1024;
    prescaler = TC_CLOCK_PRESCALER_DIV1024;
    compare = (48000000/1024)/freq;
  } else {
    Serial.println("Invalid frequency");
    while (1) delay(10);
  }
  Serial.print("Divider:"); Serial.println(divider);
  Serial.print("Compare:"); Serial.println(compare);
  Serial.print("Final freq:"); Serial.println((int)(48000000/compare));
 
  zerotimer.enable(false);
  zerotimer.configure(prescaler,       // prescaler
          TC_COUNTER_SIZE_16BIT,       // bit width of timer/counter
          TC_WAVE_GENERATION_MATCH_PWM // frequency or PWM mode
          );
 
  zerotimer.setCompare(0, compare);
  zerotimer.setCallback(true, TC_CALLBACK_CC_CHANNEL0, TimerCallback0);
  zerotimer.enable(true);
}

 