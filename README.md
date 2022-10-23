
# Bob Esponja Metal

Este software controla audio sincronizado com até 16 servos motores em um robô baseado em ESP32 da Expressif. O robô possui um altofalante ligado ao esp32.
O controle se dá pelo navegador e as configurações como movimentos e áudios ficam armazenados em micro SD no próprio robô.
Sendo possível a cópia e edição de comportamentos e audios através da interface web.

Por enquanto apenas upload/play/stop de áudio estão funcionando.
já é possivel criar os movimentos sincronizados com áudio, sendo que apenas o audio será reproduzido.

[Link para Blog com mais informações](https://omecatronico.com.br/blog/bob-esponja-metal/)


## Screenshots

![App Screenshot](https://omecatronico.com.br/blog/wp-content/uploads/2021/03/IMG_20210305_202945.jpg)


Tela Principal de execução de movimentos ou somente audio.
![App Screenshot](https://omecatronico.com.br/blog/wp-content/uploads/2021/06/tela_control.png)


Tela motion
![App Screenshot](https://omecatronico.com.br/blog/wp-content/uploads/2021/06/tela_motion_editar.png)


## Roadmap

- codificar o acionamento dos servos com interpolação.

- criar um socket para interagir com os servos em tempo real através do navegador.


## Funcionalidades

- controle de até 16 servos
- movimentos ficam armazenados em microSD
- Áudio também sincronizado com servos e fica armazenado no micro SD
- Controle total pela interface web
- Sem necessidade de alterar firmware para adicionar/editar/apagar movimentos ou áudio



## Licença

[MIT](https://choosealicense.com/licenses/mit/)

se o código for útil... gostaria de saber ;D

![Logo](https://omecatronico.com.br/blog/wp-content/uploads/2018/09/omecatronico1260x240.gif)

