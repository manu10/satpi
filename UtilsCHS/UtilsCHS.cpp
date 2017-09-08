#include <UtilsCHS.h>

char *response;
char *temp;
int ibufferWifi;
char bufferWifi[BUFFER_SIZE];
boolean found;
bool fin;

/*
Lee caracteres hasta que machea o se le temina el tiempo y devuelve el resultado
en result. Ademas imprime el motivo por el que termino(TODO:Quitar eso para optimizar)
*/
static char * UtilsCHS::readBuffer(Stream * printer,char * cond1, char * cond2, signed long timeout, int * res) {
  ibufferWifi=0;
  // (*printer).listen();//No se puede
  while ((--timeout) > 0 && ibufferWifi < BUFFER_SIZE) {
    //ibufferWifi=0;
    found=false;
    while ((--timeout > 0) & !found) {
      while (!(*printer).available() & (--timeout > 0));
      bufferWifi[ibufferWifi++] = (*printer).read();
      Serial.write(bufferWifi[ibufferWifi-1]);
      found=!(bufferWifi[ibufferWifi-1] != '\n' && bufferWifi[ibufferWifi-1] != '>' && ibufferWifi < BUFFER_SIZE);

    }
    response = bufferWifi;
    bufferWifi[ibufferWifi]=0;
    temp = strstr(response, cond1);
    if (temp != NULL) {
      *res = 0;
      #ifdef DEBUGU
      Serial.println(cond1);
      #endif
      return bufferWifi;
      // response = bufferWifi;
      // return response;
    }
    temp = strstr(response, cond2);
    if (temp != NULL) {
      *res = 1;
      #ifdef DEBUGU
      Serial.println(cond2);
      #endif
      return bufferWifi;
    }

  }
  if (ibufferWifi >= BUFFER_SIZE) {
    *res = 3;
    Serial.println("Lleno");
    // Serial.println(bufferWifi);
    // delay(3000);
    return "";
  }
  if (timeout < 0) {
    Serial.println("timeout");
    *res = 2;
  }
  return bufferWifi;
}
