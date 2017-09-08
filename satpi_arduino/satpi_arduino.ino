#include <TimerOne.h>
#include <HCSR04UNO.h>
#include <SIM808CHS.h>

//VER EL TEMA DE LOS BAUD RATES


HCSR04UNO hcsr04;
SIM808CHS mySim800l(19200);
const int analogPin = A0;


char charBuf[7];  

void setup() {
  Serial.begin(115200);
  mySim800l.setup();
  hcsr04.setup();


  Serial.println("Prueba de distancia");
  Serial.println(hcsr04.getDist());
  Serial.println(hcsr04.getDist());
  delay(1000);
  
  Serial.println("Prueba de adc");
  Serial.println(analogRead(analogPin));
  Serial.println(analogRead(analogPin));

//  delay(5000);
  Serial.println("Prueba sim808");
//  mySim800l.sendData("","");//Para probar...
//  Timer1.initialize(20000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
//  Timer1.attachInterrupt( timerIsr ); // attach the service routine here



}
//
//void timerIsr()
//{
//  
////  Serial.println("algo");
//  dtostrf(hcsr04.getDist(), 3, 3, charBuf);
//  Serial.println(charBuf);
////  mySim800l.sendData(analogRead(analogPin),charBuf);
//  mySim800l.sendData("","");
//}
void loop() {
  dtostrf(hcsr04.getDist(), 3, 3, charBuf);
  Serial.println(charBuf);
  mySim800l.sendData(analogRead(analogPin),charBuf);
  delay(10000);
}
