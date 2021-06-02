
void sdcard_setup(){
  DBG_OUTPUT_PORT.print("[INFO]: inicializando SD card...");
  if(SD.begin()){
    DBG_OUTPUT_PORT.println("OK");
    hasSD = true;
  }else{
    DBG_OUTPUT_PORT.println("deu ruim!!");
    while(1);
  }
}

void exec_motion_SD(String path){
  DBG_OUTPUT_PORT.println("mov iniciado");
  
  }
