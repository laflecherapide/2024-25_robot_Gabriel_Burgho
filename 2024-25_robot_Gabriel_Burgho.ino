//************LIBRAIRIE*************
#include "robot.h"
//************VARIABLE************
extern unsigned long impulsion_echo_droite, impulsion_echo_gauche;
extern unsigned int distance_droite, distance_gauche;
extern char data_bt;
extern int vitesse;
int mode_de_fonctionnement;
//**********FONCTION************
int choix_user(void) 
{
  if (!digitalRead(BP_C)) 
  {
    display.println("mode bluetooth");
    display.print("appuez sur B pour confirmer");
    refresh();
    while (1) 
    {
      display.setCursor(0, 0);
      if (!digitalRead(BP_B)) 
      {
        display.print("bluetooth");
        refresh();
        return mode_bluetooth;
      } else mode_de_fonctionnement = choix_user();
    }
  }
  if (!digitalRead(BP_A)) 
  {
    display.println("mode automatique");
    display.print("appuez sur B pour confirmer");
    refresh();
    while (1) 
    {
      display.setCursor(0, 0);
      if (!digitalRead(BP_B)) 
      {
        display.print("automatique");
        refresh();
        return mode_auto;
      } else mode_de_fonctionnement = choix_user();
    }
  }
  return pas_de_choix;
}

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
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setRotation(1);
  delay(1000);
  display.setCursor(0, 0);
  while(true)
  {
    display.setCursor(0, 0);
    choix_vitesse();
    if (!digitalRead(BP_B)) continue;
  }
}

void loop() {
  display.setCursor(0, 0);
  switch (mode_de_fonctionnement) 
  {
    case pas_de_choix:
      refresh();
      avant_choix();
      mode_de_fonctionnement = choix_user();
      break;
    case mode_bluetooth:
      display.println("bluetooth");
      affichage_vitesse();
      refresh();
      if (Serial1.available()) 
      {
        data_bt = Serial1.read();
        switch (data_bt) 
        {
          case 'A':
            avancer_droite();
            avancer_gauche();
            break;
          case 'R':
            reculer_droite();
            reculer_gauche();
            break;
          case 'B':
            freinage();
            break;
          case 'D':
            avancer_gauche();
            reculer_droite();
            break;
          case 'G':
            avancer_droite();
            reculer_gauche();
            break;
        }
      }
      break;
    case mode_auto:
      display.println("automatique");
      affichage_vitesse();
      refresh();      
      automatic();
      avancer_droite();
      avancer_gauche();
      if (distance_droite <= 7) 
      {
      }
      if (distance_gauche <= 7) 
      {
      }
      break;
  }
}
