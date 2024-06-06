//************LIBRAIRIE*************
#include "robot.h"
#include "interrupt.h"
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
  init_interrupt(10); //freq
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
  speed = speed_choice();
}
//**************LOOP*****************
void loop() {
  display.setCursor(0, 0);
  //TimerCallback0();
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
      automatic(5); //parametre: distance min en cm
      avancer_droite(10);
      avancer_gauche(10);
      break;
    default:
      refresh_display();
      avant_choix();//todo
      mode_de_fonctionnement = choix_user();//permet le choix du mode
      break;
  }
  }}
