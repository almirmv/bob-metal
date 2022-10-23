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

//saida: DAC interno pino 25 "AUDIO"
const int MOTION_INTERVAL = 20;         //intervalo em ms entre cada recalculo do motion
const int LED_ESP32_ONBOARD = 2;        //LED instalado de fabrica no pino 2
const int SERVO0_PIN = 13;
const int SERVO1_PIN = 12;
const int SERVO2_PIN = 14;
const int SERVO3_PIN = 27;

//Instanciando Objetos---------------------------------------------
//WEBSERVER
File uploadFile;                    
File audio_dir;
File motion_file;
WebServer server(80);               // Set web server port number to 80
//AUDIO
AudioFileSourceSD *source = NULL;   //AudioFileSourcePROGMEM *file; //
AudioGeneratorMP3 *decoder = NULL;  //AudioGeneratorFLAC *decoder = NULL; //AudioGeneratorMOD *mod;//
AudioOutputI2S *output = NULL;
//SERVOS

Servo servo0;                       //criando objetos dos servos...
Servo servo1;
Servo servo2;
Servo servo3;

//VARIAVEIS--------------------------------------------------------
String audioToPlay = "";                //audio pedido para tocar
String motionToPlay = "";               //movimento pedido
int total_frames_arq = -1;              //tem sempre um } fechando todo o JSON e deve ser descartado...
int numServos = 4;                      //numero de servos do movimento
int motionRunning = 0;                  //movimento sendo executado
float motionFrameAtual[17];               //frame atual contendo tempo e posição final de 16 servos
float servosPosAtual[16];                 //posição atual de cada umd os 16 servos
float servosVelAtual[16];                 //velocidade atual de cada umd os 16 servos
static bool hasSD = false;
long unsigned motionUpdateTimer = 0;    //timer para atualizar ou nao o movimento
long unsigned motionServoTimer = 0;     //timer para duração de cada frame do movimento

//SETUP========================================================================================
void setup(){
  DBG_OUTPUT_PORT.begin(115200);             //inicializa serial
  pinMode(LED_ESP32_ONBOARD, OUTPUT);
  // pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(LED_ESP32_ONBOARD, LOW);
  // digitalWrite(output27, LOW);
  
  delay(1000);
  sdcard_setup();   //inicializa SDcard
  motion_setup();
  wifi_setup();
  webserver_setup();
  audio_setup();    //inicializa configurações de audio
}

//LOOP ========================================================================================
void loop()
{
  server.handleClient(); //webserver_update(); //qualquer comando dado será tratado logo em seguida...
  audio_update();
  motion_update();
 
}
