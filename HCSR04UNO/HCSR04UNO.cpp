#include <HCSR04UNO.h>

#define AUXSIZE 50

//Mensajes a mostrar en consola
const char MG_SETOK[] PROGMEM  = {"HCSR04UNO_setup success!\r\n"};
const char MG_SETF[] PROGMEM  = {"SIM800L_setup failed!\r\n"};
const char MG_NSIG[] PROGMEM  = {"No signal\r\n"};
const char MG_YSIG[] PROGMEM  = {"Yes signal\r\n"};

void setup();
float getDist();




static int iNum;
static int iMsg;//TODO:Ver si lo podemos usar como char para ahorrar memoria
static char ch;
static int cant;
static int sum;
static bool fin;
static int mens;
static bool first;
static char chAux,ind;
static char num[2];
static int result;



void HCSR04UNO::setup() {
  pinMode(TRIGGER,OUTPUT);
  pinMode(ECHO,INPUT);
  HCSR04UNO_debug(Serial,MG_SETOK)
}

// Funcion para obtener la distancia en cm
float HCSR04UNO::getDist() {
  long tiempo;
  float distance;
  digitalWrite(TRIGGER,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER,LOW);

  tiempo = (pulseIn(ECHO,HIGH)/2);
  distance = float(tiempo*0.0343);

  return distance;
}
