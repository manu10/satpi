#include <TimerOne.h>
#include <HCSR04UNO.h>
#include <SIM808CHS.h>

//VER EL TEMA DE LOS BAUD RATES


HCSR04UNO hcsr04;
SIM808CHS mySim800l(19200);
const int analogPin = A0;

void setup() {
  Serial.begin(19200);
  mySim800l.setup();
  hcsr04.setup();


  Serial.println("Prueba de distancia");
  Serial.println(hcsr04.getDist());
  Serial.println(hcsr04.getDist());
  delay(1000);
  
  Serial.println("Prueba de adc");
  Serial.println(analogRead(analogPin));
  Serial.println(analogRead(analogPin));

  delay(5000);
  Serial.println("Prueba sim808");
  mySim800l.sendData("","");//Para probar...
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
