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
//-------------------------------------------------------------
