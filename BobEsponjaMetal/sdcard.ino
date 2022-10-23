
void sdcard_setup(){
  DBG_OUTPUT_PORT.print("[INFO]: inicializando SD card...");
  delay(1000);                                 //Estava dando erro assim que energiza a primeira vez. O delay serve apara estabilizr alimentação antes de tentar iniciar o SDcard.
  if(SD.begin()){
    DBG_OUTPUT_PORT.println("OK");
    hasSD = true;
  }else{
    DBG_OUTPUT_PORT.println("deu ruim!!");
    hasSD = false;
    reiniciar_esp();    //vai reiniciar o ESP32
  }
}
