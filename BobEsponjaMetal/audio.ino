/*CONFIGURAÇÕES DE AUDIO

*/
void audio_setup(){
  audioLogger = &Serial;  
  source = new AudioFileSourceSD();  //fonte: SD card
  decoder = new AudioGeneratorMP3(); //decodificador mp3  //AudioGeneratorFLAC(); //decodificador FLAC
  output = new AudioOutputI2S(0, 1); //saida: DAC interno pino 25   //AudioOutputSPDIF(SPDIF_OUT_PIN);

  audio_dir = SD.open("/"); //configura audio dir
}

 void audio_update(){

  //ta tocando?
  if ((decoder) && (decoder->isRunning())) {
    if (!decoder->loop()) decoder->stop();      //se acabou entao da stop...
    
    //algum pedido enquanto estamos no play?
    if(audioToPlay.indexOf("/audio/") >= 0){
      decoder->stop();                              //qualquer que seja o pedido da stop no decoder...
      if(audioToPlay.indexOf("/STOP/") >= 0){
        audioToPlay="";                             //se era stop entao zera o pedido.
      }
    }   
  }else{
    //nao estava tocando...PEDIDO DE PLAY ?
    if(audioToPlay.length() > 0){                   //tem pedido?
      if(audioToPlay.indexOf("/STOP/") >= 0){
        audioToPlay="";                             //se era stop... ja estamos no stop... entao zera o pedido.
        return;
      }
      //decoder->stop();                          //da stop. no que tiver tocando....
      File file = SD.open(audioToPlay);         //tenta abrir o audio
        if(file){                                                   
          if(String(file.name()).endsWith(".mp3")){     //verifica se é mp3...
             source->close();                           //fecha fonte anteriror
             if(source->open(file.name())){             //tenta abrir nova fonte 
                Serial.printf_P(PSTR("Playing '%s' from SD card...\n"), file.name());
                decoder->begin(source, output);
                audioToPlay="";                         //zerando pedido
             }else{
                Serial.printf_P(PSTR("Error opening '%s'\n"), file.name());
             }
          }
       }
    } 
  }
 
  
/*  if ((decoder) && (decoder->isRunning())) {
    if (!decoder->loop()) decoder->stop();    //se acabou entao da stop.
  }else{
     if(audioToPlay.length() > 0){               //pedido do webserver?
        File file = SD.open(audioToPlay);        //tenta abrir o audio
        if(file){                                                   
          if(String(file.name()).endsWith(".mp3")){     //verifica se é mp3...
             source->close();                           //fecha fonte anteriror
             if(source->open(file.name())){             //tenta abrir nova fonte 
                Serial.printf_P(PSTR("Playing '%s' from SD card...\n"), file.name());
                decoder->begin(source, output);
                audioToPlay="";                         //zerando pedido
              }else{
                Serial.printf_P(PSTR("Error opening '%s'\n"), file.name());
              }
          } 
        }  
     }
  }
*/
  
  /*
  if ((decoder) && (decoder->isRunning())) {
    if (!decoder->loop()) decoder->stop();
  } else {
    File file = audio_dir.openNextFile();
    if (file) {      
      if (String(file.name()).endsWith(".mp3")) {
        source->close();
        if (source->open(file.name())) { 
          Serial.printf_P(PSTR("Playing '%s' from SD card...\n"), file.name());
          decoder->begin(source, output);
        } else {
          Serial.printf_P(PSTR("Error opening '%s'\n"), file.name());
        }
      } 
    } else {
      Serial.println(F("Playback form SD card done\n"));
      delay(1000);
    }       
  } 
*/  
}
