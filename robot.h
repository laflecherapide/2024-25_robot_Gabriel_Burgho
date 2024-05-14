//****************LIBRAIRIE*****************
#include <Adafruit_SH110X.h>
//******************OBJET*******************
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
//****************CONSTANTE****************
#define BP_A 9
#define BP_B 6
#define BP_C 5
#define mode_bluetooth 1
#define mode_auto 2
#define pas_de_choix 0
#define pin_trig_droite A0
#define pin_trig_gauche A2
#define pin_echo_droite A1
#define pin_echo_gauche A3
#define in1 10
#define in2 11
#define in3 12
#define in4 13
//*****************VARIABLE****************
unsigned long impulsion_echo_droite,impulsion_echo_gauche;
unsigned int distance_droite,distance_gauche;
char data_bt;
int vitesse = 0;
//****************FONCTION*****************

void avant_choix(void)
{
  display.print("choix d'utilisateur");
  display.print("appuez sur B pour confirmer");
}
void avancer_droite(void)
{
  delay(100);
  digitalWrite(in1,1);
  digitalWrite(in2,0);
}

void avancer_gauche(void)
{
  digitalWrite(in3,1);
  digitalWrite(in4,0);
  delay(100);
}

void reculer_droite(void)
{
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  delay(100);
}

void reculer_gauche(void)
{
  digitalWrite(in1,0);
  digitalWrite(in2,1);
  delay(100);
}

void freinage(void)
{
  digitalWrite(in3,1);
  digitalWrite(in4,1);
  digitalWrite(in3,1);
  digitalWrite(in4,1); 
}
void tourner_gauche(void)
{
  freinage();
  avancer_droite();
  reculer_gauche();
}

void tourner_droite(void)
{
  freinage();
  avancer_gauche();
  reculer_droite();
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

void refresh(void)
{
  display.display();
  display.clearDisplay();
}
void affichage_vitesse(void)
{
  Serial.printf("vitesse = %d %", vitesse);
}
void choix_vitesse(void)
{
  //display.println("choix de la vitesse:");
  display.printf("vitesse = %d %");
  if (!digitalRead(BP_C)) 
  {
    vitesse += 10;
    refresh();
    while(1);
  } 
  if (!digitalRead(BP_A))
  {
     vitesse -= 10;
     refresh();
     while(1);
  }
  refresh();
}