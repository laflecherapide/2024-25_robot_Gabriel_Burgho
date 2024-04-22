
//****************LIBRAIRIE*****************
#include <Adafruit_SH110X.h>
//******************OBJET*******************
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
//****************CONSTANTE****************
#define BP_A 9
#define BP_B 6
#define BP_C 5
#define mode_bluetooth 0
#define mode_auto 1
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

void bluetooth(void)
{

}

void avancer_droite(void)
{
  digital.Write(in1,1);
  digital.Write(in2,0);
}

void avancer_gauche(void)
{
  digital.Write(in3,1);
  digital.Write(in4,0);
}

void reculer_droite(void)
{
  digital.Write(in1,0);
  digital.Write(in2,1);
}

void reculer_gauche(void)
{
  digital.Write(in1,0);
  digital.Write(in2,1);
}

void freinage(void)
{
  digital.Write(in3,1);
  digital.Write(in4,1);
  digital.Write(in3,1);
  digital.Write(in4,1); 
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
    /*if(Serial1.available)
    {
      data_rx = Serial1.read();
      switch (data_rx)
      {
        case :
        break;
      }
    }*/
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
