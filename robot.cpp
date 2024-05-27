//****************LIBRAIRIE*****************
#include "robot.h"
#include "interrupt.h"
//******************OBJET*******************
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
//*****************VARIABLE****************
unsigned long impulsion_echo_droite,impulsion_echo_gauche;
unsigned int distance_droite,distance_gauche;
char data_bt;
unsigned int speed = 0;
int mode_de_fonctionnement;
bool token_speed_choice = 0;
//****************FONCTION*****************
int choix_user(void) 
{
  while(1)
  {
    display.setCursor(0, 0);
    if (!digitalRead(BP_A))
    {
      display.println("bluetooth mode");
      display.print("press B to confirm");
      refresh_display();
      mode_de_fonctionnement = mode_bluetooth;
    }
    if (!digitalRead(BP_C))
    {
      display.println("automatic mode");
      display.print("press B to confirm");
      refresh_display();
      mode_de_fonctionnement = mode_auto;
    }
    if (!digitalRead(BP_B))
    {
      return mode_de_fonctionnement;
    }
  }
}

int speed_choice(void)
{
  while(!token_speed_choice)
  {
    display.setCursor(0, 0);
    display.println("speed choice");
    display.printf("speed = %d", speed);
    refresh_display();
    if (!digitalRead(BP_A) && speed < 200) 
      {
        speed += 10;
        //while(1);
      } 
    if (!digitalRead(BP_C) && speed > 0)
      {
        speed -= 10;
        //while(1);
      }
    if (!digitalRead(BP_B)) token_speed_choice = 1;
    //if ()millis()
    delay(1);
  }
  return speed;
}

void refresh_display(void)
{
  display.display();
  display.clearDisplay();
}

void avant_choix(void)
{
  display.println("user choice");
  display.print("press B to confirm");
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

void get_distance(void)
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

void display_speed(void)
{
  display.printf("speed = %d", speed);
}
void bluetooth(void)
{
  if (Serial1.available()) 
      {
        data_bt = Serial1.read();
        switch (data_bt) 
        {
          case 'A':
            avancer_droite(0);
            avancer_gauche(0);
            break;
          case 'R':
            reculer_droite(0);
            reculer_gauche(0);
            break;
          case 'B':
            freinage();
            break;
          case 'D':
            avancer_gauche(0);
            reculer_droite(0);
            break;
          case 'G':
            avancer_droite(0);
            reculer_gauche(0);
            break;
        }
      }
}
void automatic(int distance_min)
{
  if (distance_droite <= distance_min) 
  {
    tourner_gauche(200, 200);
  }
  if (distance_gauche <= distance_min) 
  {
    tourner_droite(200, 200);
  }
}