/*CONFIGURAÇÕES DO MOVIMENTO
*/
//MOTION SETUP-------------------------------------------------------------------------------  
void motion_setup(){
 
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  servo0.setPeriodHertz(50);      // Standard 50hz servo
  servo1.setPeriodHertz(50);      // Standard 50hz servo
  servo2.setPeriodHertz(50);      // Standard 50hz servo
  servo3.setPeriodHertz(50);      // Standard 50hz servo
    
  servo0.attach(SERVO0_PIN,500,2000);   //servo1Pin, minUs, maxUs se omitir o padrao é 1000us and 2000us
  servo1.attach(SERVO1_PIN,500,2000);
  servo2.attach(SERVO2_PIN,500,2000);
  servo3.attach(SERVO3_PIN,500,2000); 
  
}
//MOTION UPDATE-------------------------------------------------------------------------------  
void motion_update(){
  //tem pedido?
  if(motionToPlay.length() > 0){
    exec_motion_SD(motionToPlay);      //delega o cumprimento da tarefa pedida.
    motionToPlay = "";                 //zera tarefa pedida.
    isMoving = 1;          
    
    }
  //está movimenttando?
  if(isMoving != -1){
    atualiza_servos();  //recalcular e enviar para cada servo sua nova posição.
    
    }
  
  }

//recalcular e enviar para cada servo sua nova posição-----------------------------------------
void atualiza_servos(){
  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  //acabou o movimento? entao..
  isMoving= -1; 
}
