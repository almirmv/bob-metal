/*CONFIGURAÇÕES DO WIFI

*/

//iniciar o ACCESS POINT-------------------------------------------------------------------------------
void wifi_setup(){  
  //vamos tentar conectar na rede configurada no SPIFFS
  serial_msg_ln_info();                                             //da nova linha e printa "[INFO]" na tela 
  DBG_OUTPUT_PORT.print("Conectando a: ");
  DBG_OUTPUT_PORT.print(_STAssid);
    
  WiFi.begin(_STAssid, _STApassword);                       //tenta conexão com roteador wifi
  int i=0;
  while(WiFi.status() != WL_CONNECTED && (i<10) ){
    delay(500);
    DBG_OUTPUT_PORT.print(".");
    i++;
  }
  DBG_OUTPUT_PORT.println("OK!");
  DBG_OUTPUT_PORT.print("IP address: ");
  DBG_OUTPUT_PORT.println(WiFi.localIP());
  
  //iniciando MDNS...
  if (MDNS.begin(host)) {
    MDNS.addService("http", "tcp", 80);
    DBG_OUTPUT_PORT.println("MDNS responder started");
    DBG_OUTPUT_PORT.print("You can now connect to http://");
    DBG_OUTPUT_PORT.print(host);
    DBG_OUTPUT_PORT.println(".local");
  }
  
  /*//CRIANDO ACCESS POINT ==========================
  serial_msg_ln_info();                           
  Serial.print("Criando Soft AP: ");
  Serial.print(_APssid);
   
  WiFi.softAP(_APssid, _APpassword);       //tenta criar uma rede wifi (AP) 
  serial_msg_ln_info();                    //da nova linha e printa "[INFO]" na tela
  Serial.print("Soft AP criada! IP: ");
  Serial.println(WiFi.softAPIP());
  */
}
