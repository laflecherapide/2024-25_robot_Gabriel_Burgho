#include "robot.h"

extern unsigned long impulsion_echo_droite,impulsion_echo_gauche;
extern unsigned int distance_droite,distance_gauche;
extern char data_bt;

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
  display.setRotation(2);
  display.setCursor(0, 0);
  display.print("choix d'utilisateur");
  display.print("appuez sur B pour confirmer");
  display.display();
  display.clearDisplay();
}


bool choix_user(int choix)
{
  if(!digitalRead(BP_C))
  {
    display.println("mode bluetooth");
    display.print("appuez sur B pour confirmer");
    display.display();
    if(!digitalRead(BP_B)) return mode_bluetooth;
  }
  if (!digitalRead(BP_A))
  {
    display.println("mode automatique");
    display.print("appuez sur B pour confirmer");
    if(!digitalRead(BP_B)) return mode_auto;
  }
  return 3;
}

void loop() 
{
  switch(choix_user){
    case 0:
    display.print("bluetooth");
    if(Serial1.available())
    {
      data_bt = Serial1.read();
      switch (data_bt)
      {
        case 'A':
        avancer_droite();
        avancer_gauche();
        break;
      }
    }
    break;
    case 1:
    display.print("automatique");
    automatic();
    if (distance_droite)
    {

    }
    if (distance_gauche)
    {

    }
    break;
  }
  display.display();
  display.clearDisplay();
}
