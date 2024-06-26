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
#define in2 13
#define in3 11
#define in4 12
//*****************VARIABLE****************
extern unsigned long impulsion_echo_droite,impulsion_echo_gauche;
extern unsigned int distance_droite,distance_gauche;
extern char data_bt;
extern unsigned int speed;
extern int mode_de_fonctionnement;
extern bool token_speed_choice;
//****************FONCTION*****************
int speed_choice(void);
void refresh_display(void);
void avant_choix(void);
void avancer_droite(int);
void avancer_gauche(int);
void reculer_droite(int);
void reculer_gauche(int);
void freinage(void);
void tourner_gauche(int,int);
int get_distance_droite(void);
int get_distance_gauche(void);
void tourner_droite(int,int);
void display_speed(void);
int choix_user(void);
void bluetooth(void);
void automatic(int);