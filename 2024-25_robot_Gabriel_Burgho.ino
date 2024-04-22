#include "robot.h"

//*****************VARIABLE****************
unsigned long impulsion_echo_droite,impulsion_echo_gauche;
unsigned int distance_droite,distance_gauche;
//10,13,11,12 driver moteur
void setup() 
{
  //Serial1.begin(9600);
  pinMode(BP_A, INPUT_PULLUP);
  pinMode(BP_B, INPUT_PULLUP);
  pinMode(BP_C, INPUT_PULLUP);
  pinMode(pin_echo, INPUT);
  pinMode(pin_trig, OUTPUT);
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


void choix_user(bool choix)
{
  if(!digital.Read(BP_C))
  {
    display.println("mode bluetooth");
    display.print("appuez sur B pour confirmer");
    display.display();
    if(!digital.Read(BP_B)) return mode_bluetooth;
  }
  if (!digital.Read(BP_A))
  {
    display.println("mode automatique");
    display.print("appuez sur B pour confirmer");
    if(!digital.Read(BP_B)) return mode_auto;
  }
}

void loop() 
{
  switch(choix_user){
    case 0:
    display.print("bluetooth");
    if(Serial1.available)
    {
      data_rx = Serial1.read();
      switch (data_rx)
      {
        case :
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
