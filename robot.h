//****************LIBRAIRIE*****************
#include <Adafruit_SH110X.h>
//******************OBJET*******************
extern Adafruit_SH1107 display;
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
extern unsigned long impulsion_echo_droite,impulsion_echo_gauche;
extern unsigned int distance_droite,distance_gauche;
extern char data_bt;
extern unsigned int vitesse;
extern int mode_de_fonctionnement;
//****************FONCTION*****************
void choix_vitesse(void);
void refresh(void);
void avant_choix(void);
void avancer_droite(void);
void avancer_gauche(void);
void reculer_droite(void);
void reculer_gauche(void);
void freinage(void);
void tourner_gauche(void);
void automatic(void);
void tourner_droite(void);
void affichage_vitesse(void);
int choix_user(void);