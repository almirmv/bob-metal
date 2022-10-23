//printa linha
void serial_msg_barra(){
  DBG_OUTPUT_PORT.println("==================================================");
  }
//printa [INFO]
void serial_msg_info(){
  DBG_OUTPUT_PORT.print("[INFO] ");
  }
//nova linha e depois printa [INFO]
void serial_msg_ln_info(){
  DBG_OUTPUT_PORT.println("");       //nova linha
  DBG_OUTPUT_PORT.print("[INFO] ");  //printa INFO
  }
void serial_msg_ln_erro(){
  DBG_OUTPUT_PORT.println("");       //nova linha
  DBG_OUTPUT_PORT.print("[ERRO] ");  //printa ERRO
  }

//Reinicia o ESP32 apos 4seg enquanto pisca 20 vezes o LED
void reiniciar_esp(){
  int i=0;
  while(i<10){
    delay(200);      
    digitalWrite(LED_ESP32_ONBOARD, HIGH);
    delay(200);
    digitalWrite(LED_ESP32_ONBOARD, LOW);
    i++;
  }
  ESP.restart();     //reinicia o ESP 
}
//-------------------------------------------------------------
