/*CONFIGURAÇÕES DO MOVIMENTO
*/
//MOTION SETUP-------------------------------------------------------------------------------  
void motion_setup(){
 
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  servo0.setPeriodHertz(20);      // Standard 50hz servo
  servo1.setPeriodHertz(20);      // Standard 50hz servo
  servo2.setPeriodHertz(50);      // Standard 50hz servo
  servo3.setPeriodHertz(50);      // Standard 50hz servo
    
  servo0.attach(SERVO0_PIN,500,2500);   //servo1Pin, minUs, maxUs se omitir o padrao é 1000us and 2000us
  servo1.attach(SERVO1_PIN,500,2000);
  servo2.attach(SERVO2_PIN,500,2000);
  servo3.attach(SERVO3_PIN,500,2000); 
 
  for(int i=0; i< 16; i++){
    servosPosAtual[i] = 90;
    motionFrameAtual[i+1] = 90; 
  }
}
//MOTION UPDATE-------------------------------------------------------------------------------  
void motion_update(){
  //tem pedido?
  if(motionToPlay.length() > 0){        //tem pedido?
    if(openMotionSD(motionToPlay)){     //conseguiu abrir?
      motionGetNextFrame();             //captura e carrega nas variaveis primeiro frame
      motionRunning = 1;
    }        
    motionToPlay = "";                  //zera tarefa pedida.
  }
  //está movimenttando?
  if(motionRunning == 1){                   //Estamos rodando...
    if(millis()-motionUpdateTimer > MOTION_INTERVAL){
      motionUpdateTimer = millis();         //atualiza o timer
      recalcular_frame();                   //recalcula e se precisar chama novo frame internamente. se acabou faz "motionRunning = 0"
      atualiza_servos();                    //joga no servo o valor da nova posição calculada
    }//fim timer...
  }
}

//==================================================
void recalcular_frame(){
  int i=0;
  float v;
  float ds;
  motionFrameAtual[0] = motionFrameAtual[0] - MOTION_INTERVAL;  //agora temos menos tempo para chegar ao destino...
  if(motionFrameAtual[0] < 0){                                 //FINAL DO FRAME!
     for(i=0; i<numServos; i++){
      servosPosAtual[i] = motionFrameAtual[i+1];                //apenas para terminar o frame com o valor exato do pedido
     }
    if(!motionGetNextFrame()){                                  //se nao tem próximo frame entao encerra atividades
      motionRunning = 0;
      }
               
    }else{                                                      //frame valido e com tempo... recalculando servos
      // Vangular = ds/dt ex. v = 90-10/1segundo = 80 graus em 1 segundo. S intervalo é de 0.1segundo se moveu quanto? 
      // deslocamento em 0.1seg... S=V.dt... s = 80/1 *0.1 = 8graus...
      //teremos entao nova posição apos primeira interação de 18 graus.

      // v=90-18=72 graus em 0.9 segundos... e deslocamento no intervalo de s=72/0.9 * 0.1 = 8graus!
      // nova posiçao no final dos 0.1 de 26 graus! entao Satualizado += v*dt =
      DBG_OUTPUT_PORT.println("");
      for(i=0; i<numServos; i++){
        v = (motionFrameAtual[i+1] - servosPosAtual[i]) / motionFrameAtual[0];    //calcula velocidade instantanea para atingir algo no tempo certo
        ds = v * MOTION_INTERVAL;   //agora calculamso a quantidade exata de deslocamento nesse instante para conseguir no tempo certo o destino
         
        servosPosAtual[i] += ds;    //adiciona ao angulo atual a fração que precisa se mover em nosso dt de 20ms
               
        DBG_OUTPUT_PORT.print("\t");
        DBG_OUTPUT_PORT.print(servosPosAtual[i]);
      }
        DBG_OUTPUT_PORT.println("");
      
      
      }
  } 
//recalcular e enviar para cada servo sua nova posição-----------------------------------------
void atualiza_servos(){
  servo0.write(int(servosPosAtual[0]));
  servo1.write(int(servosPosAtual[1]));
  servo2.write(int(servosPosAtual[2]));
  servo3.write(int(servosPosAtual[3]));
}

bool motionGetNextFrame(){
  String aux="";
  String aux2="";
  int i=0 , j=1;
  char c;
  int inicio=0; 
  String frame = motion_file.readStringUntil('{');    //lemos ate checar no inicio do frame. obs: ele na inclui o {
  frame = motion_file.readStringUntil('}');           //agora vamos ler ae o final do frame
    
  inicio = frame.indexOf("a\":")+4;                                                 //acha indice do inicio do audio a tocar
  audioToPlay = "/audio/" + frame.substring(inicio, frame.indexOf("\"", inicio));   //acha o indice da " que fica depois do nome e corta do inicio ate ela.   
   
  inicio = frame.indexOf("t\":")+3;                                         //acha indice do inicio do tempo
  aux = frame.substring(inicio, frame.indexOf(",", inicio));                //acha o indice da vigula que fica depois do numero e corta do inicio ate ela.   
  motionFrameAtual[0] = aux.toInt();                                        //converte string para numero 
  
  inicio = frame.indexOf("s\":[")+4;                                        //captura inicio do primeiro servo
  aux = frame.substring(frame.indexOf("s\":[")+4);                          //aux fca com algo como 108,92,90,90]
  while(i <= aux.length()){                                                //vai checar um a um os caracteres
    c = aux.charAt(i);
    if(c == ',' || c == ']'){                                                //chegou na virgula?
      motionFrameAtual[j] = aux2.toInt();                                   //converte o numero
      //DBG_OUTPUT_PORT.print(" S: " + aux2);
      j++;
      aux2 = "";
      }else{
        aux2 += c;                                                            //adiciona novo numero
        }
    i++;                                                                    //proximo char da string
    }
  
  if(frame.length() > 10){
    DBG_OUTPUT_PORT.println("String Frame: " + frame);
    DBG_OUTPUT_PORT.print("Processado - A: " + audioToPlay);
    DBG_OUTPUT_PORT.print(" T: ");
    DBG_OUTPUT_PORT.print(motionFrameAtual[0]);
    DBG_OUTPUT_PORT.print(" S:");
    for(i=1; i<=numServos; i++){
      DBG_OUTPUT_PORT.print("\t");
      DBG_OUTPUT_PORT.print(motionFrameAtual[i]);
      }
    return 1;//tem frame novo carregado =D
    }else{
      return 0;//acabaram os frames!
      }
  }
//-------------------------------------------------------------------------
int openMotionSD(String path){
  char c;
  int inicio;
  String stringJSON ="";
  String aux="";
  
  motion_file = SD.open(path.c_str());                             //abrindo arquivo do SD
  if(!motion_file){
    DBG_OUTPUT_PORT.print("Erro ao abrir arquivo motion");
    return 0;
    }
  
  //contabilizar numero de linhas...
  total_frames_arq = -1;
  while(motion_file.available()){                    //
      c = motion_file.read();                        //le proximo caracter...  
      if(c == '}'){                           //completou uma linha?
          total_frames_arq++;
          }
      }
  motion_file.close();                               //fecha o arquivo    
  
  
  motion_file = SD.open(path.c_str());                             //abrindo arquivo do SD
  //loop procurando frames do "animation"...
//{"motionName":"andar","roboName":"BOB Metal","numServos":4,"animation":[{"a":"Beginning.mp3","t":729,"s":["42","90","90","63"]},{"a":"STOP","t":2328,"s":["43","90","90","106"]}]}
  
  stringJSON = motion_file.readStringUntil('[');                         //lemos ate checar no inicio do frame obc ele na inclui o {
  //temos algo como {"motionName":"andar","roboName":"BOB Metal","numServos":4,"animation":      dentro da string.
  
  inicio = stringJSON.indexOf("numServos")+11;                           //acha indice do inicio do numero de servos
  aux = stringJSON.substring(inicio, stringJSON.indexOf(",", inicio));   //acha o indice da , que fica depois do numero e corta do inicio ate ela.
  numServos = aux.toInt();                                               //converte o numero para inteiro
  
  serial_msg_barra();
  DBG_OUTPUT_PORT.print("Arquivo: ");
  DBG_OUTPUT_PORT.print(path);
  DBG_OUTPUT_PORT.print(" possui ");
  DBG_OUTPUT_PORT.print(total_frames_arq);
  DBG_OUTPUT_PORT.print(" frames e ");    
  DBG_OUTPUT_PORT.print(numServos);
  DBG_OUTPUT_PORT.println(" servo(s)");
  return 1;   
}
//=======================================================
void exec_motion_SD(String path){
  DBG_OUTPUT_PORT.println("mov iniciado");
  
  }
