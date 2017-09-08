#include <SIM808CHS.h>
#include <UtilsCHS.h>

#define G_PROV "CTI"
// #define G_PROV "UNIFON"
//MEnsajes del modulo gsm
#define G_CCOP "AT+COPS?\r\n"
#define MG_NSIG "No signal\r\n"
#define MG_SETF "SIM800L_setup failed!\r\n"
#define MG_SETOK "SIM800L_setup success!\r\n"

SoftwareSerial SIM800LSerial(SIM800_RX, SIM800_TX);
SIM808CHS::SIM808CHS(uint32_t baudrate){
  SIM800LSerial.begin(baudrate);
}

int result;
int resultCMD;
void SIM808CHS::setup() {
  //vERIFICO QUE TENGA SE;AL
  SIM800LSerial.println(G_CCOP);
  UtilsCHS::readBuffer(&SIM800LSerial,G_PROV, "OK", TIME, &result);
  while (result != 0) {
    Serial.println(MG_NSIG);
    //TODO: Prender LED o algo que indique que no tiene señal, puedo comunicar al sistema WEB
    SIM800LSerial.println(G_CCOP);
    UtilsCHS::readBuffer(&SIM800LSerial,G_PROV, "OK", TIME, &result);
  }
  //Verificar si necesita algo mas de configuracion
  Serial.write(MG_SETOK);
}

bool SIM808CHS::sendData(char * pluv, char * lev){
  //Check the registration status
  SIM800LSerial.println("AT+CREG?");
  UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
  //Check whether bearer 1 is open.
  SIM800LSerial.println("AT+SAPBR=2,1");
  UtilsCHS::readBuffer(&SIM800LSerial,"0.0.0.0", "1,1", 3*TIME, &resultCMD);
  UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);//Este hace que limpie la consola, porque sino confunde los OK
  if (resultCMD==0){//Si no esta habilitado
    //Enable bearer 1
    SIM800LSerial.println("AT+SAPBR=1,1");
    UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
  }


  //Initialize HTTP service
  SIM800LSerial.println("AT+HTTPINIT");
  UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
  SIM800LSerial.write("AT+HTTPPARA=\"CID\",1\r\n");
  UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
  if (result!=8){//si NO hizo match con ERROR
    Serial.println("URL");
    SIM800LSerial.println("AT+HTTPPARA=\"URL\",\"satpi.herokuapp.com/api/v1/packages\"");
    UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
    if (result!=1){//si NO hizo match con ERROR
      SIM800LSerial.println("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
      UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
      if (result!=1){//si NO hizo match con ERROR
        SIM800LSerial.println("AT+HTTPDATA=40,1000");
        UtilsCHS::readBuffer(&SIM800LSerial,"DOWNLOAD", "ERROR", TIME, &result);
        if (result==0){//si NO hizo match con ERROR
          SIM800LSerial.println("{ \"sensor_id\": 1, \"data\": 988 }");//Parametrizar
        }
        UtilsCHS::readBuffer(&SIM800LSerial,"OK", "ERROR", TIME, &result);
        SIM800LSerial.println("AT+HTTPACTION=1");
        UtilsCHS::readBuffer(&SIM800LSerial,"HTTPACTION: 1,200", "ERROR", 5*TIME, &result);//Esperar que reciba un 200 de respuesta
        if (result==0){//si NO hizo match con ERROR
          Serial.println("POST OK");
          SIM800LSerial.println("AT+HTTPTERM");

        }
        else{
          Serial.println("POST FAIL");


        }
      }
    }
  }
}
