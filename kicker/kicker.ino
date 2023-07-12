#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

// O IP padrão é o 192.168.4.1
const char* ssid = "KickBall-player2"; // Nome da rede Wi-Fi do Access Point
const char* password = "KB102030"; // Senha para o Access Point

// Indicação do Led 
const int ledPin = 2; // Led do ESP8266
bool ledState = false; // Estado atual do LED

// Pinos para Ponte H e Motor DC
const int pin1 = 12;
const int pin2 = 14;
const int tm = 1000;

// Pino para controlar a solenoide
const int solenoidPin = 16;

ESP8266WebServer server(80);

const char* html = R"html(
<html> 
  <head>   
    <title>KickBall</title> 
    <style>

      body {
        background-color: grey;
      }
      #title {
        text-align: center;
        margin-right: 150px;
        font-size: 20px;
        font-family:'Trebuchet MS', 'Lucida Sans Unicode', 'Lucida Grande', 'Lucida Sans', Arial, sans-serif;
      }

      #rotate-message {
        display: none;
      }

      .joystick {
        display: flex;
        align-items: center;
        justify-content: center;
        padding-top: 40px;
        padding-right: 90px;
      }

      .button-lr {
        background-color: #FFC700;
        font-family:'Trebuchet MS', 'Lucida Sans Unicode', 'Lucida Grande', 'Lucida Sans', Arial, sans-serif;
        font-size: 60px;
        width: 120px;
        height: 120px;
        margin-right: 30px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
        
      }

      #button-hit{
        background-color: #FFC700;
        font-family:'Trebuchet MS', 'Lucida Sans Unicode', 'Lucida Grande', 'Lucida Sans', Arial, sans-serif;
        font-size: 30px;
        width: 200px;
        height: 200px;
        margin-right: 50px;
        padding: 50px;
        margin-left: 70px;
        padding-left: 10px;
        padding-right: 10px;
        border-radius: 50%;
      }
      
      @media screen and (orientation: portrait) {
        .joystick{
          display: none;
        }

        #rotate-message {
          display: flex;
          align-items: center;
          justify-content: center;
          font-size: 24px;
          color: white;
          background-color: rgba(0, 0, 0, 0.7);
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          z-index: 9999;
    }
    }
    </style>
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>  
   </head>  
   <body> 

    <header>
      <div>
        <h1 id="title">Kick Ball</h1>
      </div>
    </header>
    
    <div class="joystick">
      <a href="http://192.168.4.1/on">
        <button class="button-lr"><</button>
      </a>
      <a href="http://192.168.4.1/off">
        <button class="button-lr">></button>
      </a>
      <a href="http://192.168.4.1/hit">
        <button id="button-hit">Kick</button>
      </a>  
    </div>

    <div id="rotate-message">
      Por favor, Vire o seu celular na horizontal.
    </div>

    </body>  
</html>
)html";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleOn() {
  ledState = true;
  digitalWrite(ledPin, HIGH);

  // Mover para Esquerda
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,HIGH);
  delay(tm);

  // Para o Motor
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,LOW);

  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  ledState = false;
  digitalWrite(ledPin, LOW);

  // Mover para Direita
  digitalWrite(pin1,HIGH);
  digitalWrite(pin2,LOW);
  delay(tm);

  // Para o Motor
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,LOW);

  server.sendHeader("Location", "/");
  server.send(303);
}

void handleHit() {
  digitalWrite(solenoidPin, LOW); // Aciona a solenoide
  delay(120); // Aguarda 1 segundo
  digitalWrite(solenoidPin, HIGH); // Desliga a solenoide

  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, HIGH); // Inicialmente desligado
  
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.on("/hit", handleHit); // Nova rota para acionar a solenoide

  server.begin();
}

void loop() {
  server.handleClient();

}
