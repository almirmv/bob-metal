#include <Arduino.h>
#include <WiFi.h>               // Load Wi-Fi library
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ESP32Servo.h>         //#include <Servo.h>              //para controle dos servos

#include "AudioFileSourceSD.h"  //#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorMP3.h"  //#include "AudioGeneratorFLAC.h" //#include "AudioGeneratorMOD.h"
#include "AudioOutputI2S.h"
#define SPI_SPEED SD_SCK_MHZ(40)            //You may need a fast SD card. Set this as high as it will work (40MHz max).
#define DBG_OUTPUT_PORT Serial

//CONSTANTES-------------------------------------------------------
const char* _STAssid     = "xxxxxxxx";      //SSID do roteador wifi
const char* _STApassword = "xxxxxxxx";      //Senha do roteador wifi
const char* host         = "esp32sd";
const char* _APssid      = "BobMetal_AP";   //Nome da rede criada pelo robo
const char* _APpassword  = "1123456789";    //Senha da rede criada pelo robo

const int SERVO0_PIN = 13;
const int SERVO1_PIN = 12;
const int SERVO2_PIN = 14;
const int SERVO3_PIN = 27;

//Instanciando Objetos---------------------------------------------
File uploadFile;                    //usado pelo Webserver
File audio_dir;
File motion_dir;
AudioFileSourceSD *source = NULL;   //AudioFileSourcePROGMEM *file; //
AudioGeneratorMP3 *decoder = NULL;  //AudioGeneratorFLAC *decoder = NULL; //AudioGeneratorMOD *mod;//
AudioOutputI2S *output = NULL;

WebServer server(80);                       // Set web server port number to 80

Servo servo0;                       //criando objetos dos servos...
Servo servo1;
Servo servo2;
Servo servo3;

//VARIAVEIS--------------------------------------------------------
String audioToPlay = "";               //audio pedido para tocar
String motionToPlay = "";              //movimento pedido
int isMoving = -1;                  //movimento sendo executado
static bool hasSD = false;

void setup()
{
  DBG_OUTPUT_PORT.begin(115200);             //inicializa serial
  //pinMode(output26, OUTPUT);
 // pinMode(output27, OUTPUT);
  // Set outputs to LOW
  //digitalWrite(output26, LOW);
 // digitalWrite(output27, LOW);
  
  delay(1000);
  sdcard_setup();   //inicializa SDcard
  motion_setup();
  wifi_setup();
  webserver_setup();
  audio_setup();    //inicializa configurações de audio
  
  
  
 
}

void loop()
{
  server.handleClient(); //webserver_update(); //qualquer comando dado será tratado logo em seguida...
  audio_update();
  motion_update();
 
}
