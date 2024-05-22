//************LIBRAIRIE*************
#include "robot.h"
//#define bt_debug
//**************SETUP*****************
void setup() 
{
  Serial1.begin(9600);
  pinMode(BP_A, INPUT_PULLUP);
  pinMode(BP_B, INPUT_PULLUP);
  pinMode(BP_C, INPUT_PULLUP);
  pinMode(pin_echo_droite, INPUT);
  pinMode(pin_trig_droite, OUTPUT);
  pinMode(pin_echo_gauche, INPUT);
  pinMode(pin_trig_gauche, OUTPUT);
  display.begin(0x3C, true);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setRotation(1);
  init_interrupt(10);
  while(true)
  {
    display.setCursor(0, 0);
    choix_vitesse();
    if (!digitalRead(BP_B)) break;
  }
}
//**************LOOP*****************
void loop() {
  #ifdef bt_debug //affiche la réception bluetooth
  while(1)
  {
    if (Serial1.available())
    {
      char bt = Serial1.read();
      Serial.println(bt);
    }
  }
  #endif
  //mode_de_fonctionnement = mode_bluetooth;
  display.setCursor(0, 0);
  switch (mode_de_fonctionnement) 
  {
    case pas_de_choix:
      refresh();
      avant_choix();
      mode_de_fonctionnement = choix_user();
      break;
    case mode_bluetooth:
      display.setCursor(0, 0);
      display.println("bluetooth");
      affichage_vitesse();
      refresh();
      bluetooth();
      break;
    case mode_auto:
      display.setCursor(0, 0);
      display.println("automatique");
      affichage_vitesse();
      refresh();
      get_distance();
      avancer_droite(100);
      avancer_gauche(100);
      TimerCallback0();      
      break;
  }
}
