//****************LIBRAIRIE*****************
#include "robot.h"
//******************OBJET*******************
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
//*****************VARIABLE****************
unsigned long impulsion_echo_droite,impulsion_echo_gauche;
unsigned int distance_droite,distance_gauche;
char data_bt;
unsigned int vitesse = 0;
int mode_de_fonctionnement;
//****************FONCTION*****************
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

void choix_vitesse(void)
{
  display.println("choix de la vitesse:");
  display.printf("vitesse = %d", vitesse);
  refresh();
  if (!digitalRead(BP_A) && vitesse < 200) 
  {
    vitesse += 10;
    //while(1);
  } 
  if (!digitalRead(BP_C) && vitesse > 0)
  {
    vitesse -= 10;
     //while(1);
  }
}

void refresh(void)
{
  display.display();
  display.clearDisplay();
}

void avant_choix(void)
{
  display.print("choix d'utilisateur");
  display.print("appuez sur B pour confirmer");
}

void avancer_droite(int time)
{
  digitalWrite(in1,1);
  digitalWrite(in2,0);
  delay(time);
}

void avancer_gauche(int time)
{
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  delay(time);
}

void reculer_droite(int time)
{
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  delay(time);
}

void reculer_gauche(int time)
{
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  delay(time);
}

void freinage(void)
{
  digitalWrite(in3,1);
  digitalWrite(in4,1);
  digitalWrite(in3,1);
  digitalWrite(in4,1); 
}

void tourner_gauche(int time_1, int time_2)
{
  freinage();
  avancer_droite(time_1);
  reculer_gauche(time_2);
}

void automatic(void)
{
  digitalWrite(pin_trig_droite, 1);
  digitalWrite(pin_trig_gauche, 1);
  delayMicroseconds(10);
  digitalWrite(pin_trig_droite, 0);
  digitalWrite(pin_trig_gauche, 0);
  impulsion_echo_gauche = pulseIn(pin_echo_gauche, 1);
  impulsion_echo_droite = pulseIn(pin_echo_droite, 1);
  delay(100);
  distance_gauche = impulsion_echo_gauche * 0.034/2;
  distance_droite = impulsion_echo_droite * 0.034/2;
}

void tourner_droite(int time_1, int time_2)
{
  freinage();
  avancer_gauche(time_1);
  reculer_droite(time_2);
}

void affichage_vitesse(void)
{
  display.printf("vitesse = %d %", vitesse);
}