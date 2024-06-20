/*code robot 
Burgho Gabriel 
feather M0 express(SAMD21) HC-08 télémètre ultrason (SR04)
20/06/2024*/

//************LIBRAIRIE*************
#include "robot.h"
//#define bt_debug
//**************SETUP*****************
void setup() 
{
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(BP_A, INPUT_PULLUP);
  pinMode(BP_B, INPUT_PULLUP);
  pinMode(BP_C, INPUT_PULLUP);
  pinMode(pin_echo_droite, INPUT);
  pinMode(pin_trig_droite, OUTPUT);
  pinMode(pin_echo_gauche, INPUT);
  pinMode(pin_trig_gauche, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  display.begin(0x3C, true);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setRotation(1);
  digitalWrite(in1, 0); //mise à l'état bas par défaut
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
  #ifdef bt_debug //affiche la réception bluetooth
    while(1)
      {
        if (Serial1.available())
          {
            char bt = Serial1.read();
            Serial.printf("contenu Buetooth recuperer : %c \n", bt);
          }
      }
  #endif
  speed = speed_choice(); //bloquant tant que B n'est pas appuyé
}
//**************LOOP*****************
void loop() 
{
  display.setCursor(0, 0);
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
          automatic(3); //parametre: distance min en cm
          forward_right(1);
          forward_left(1);
        break;
        default:
          refresh_display();
          before_choice();//affiche "user choice"
          mode_de_fonctionnement = user_choice();//permet le choix du mode bloquant tant que B n'est pas appuyé
        break;
      }
} 
