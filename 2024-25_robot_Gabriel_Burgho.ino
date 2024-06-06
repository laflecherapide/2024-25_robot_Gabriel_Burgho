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
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
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
          avancer_droite(1);
          avancer_gauche(1);
        break;
        default:
          refresh_display();
          avant_choix();//todo
          mode_de_fonctionnement = choix_user();//permet le choix du mode
        break;
      }
} 
