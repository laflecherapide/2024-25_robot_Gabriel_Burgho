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
  while(true)
  {
    display.setCursor(0, 0);
    choix_vitesse();
    if (!digitalRead(BP_B)) break;
  }
}
//**************LOOP*****************
void loop() {
  mode_de_fonctionnement = mode_bluetooth;
  display.setCursor(0, 0);
  #ifdef bt_debug
  while(1)
  {
    if (Serial1.available())
    {
      char bt = Serial1.read();
      Serial.println(bt);
    }
  }
  #endif
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
      if (Serial1.available()) 
      {
        data_bt = Serial1.read();
        switch (data_bt) 
        {
          case 'A':
            avancer_droite(100);
            avancer_gauche(100);
            break;
          case 'R':
            reculer_droite(100);
            reculer_gauche(100);
            break;
          case 'B':
            freinage();
            break;
          case 'D':
            avancer_gauche(100);
            reculer_droite(100);
            break;
          case 'G':
            avancer_droite(100);
            reculer_gauche(100);
            break;
        }
      }
      break;
    case mode_auto:
      display.setCursor(0, 0);
      display.println("automatique");
      affichage_vitesse();
      refresh();      
      automatic();
      avancer_droite(100);
      avancer_gauche(100);
      if (distance_droite <= 7) 
      {
        tourner_gauche(200, 200);
      }
      if (distance_gauche <= 7) 
      {
        tourner_droite(200, 200);
      }
      break;
  }
}
