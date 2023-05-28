#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// O IP padrão é o 192.168.4.1
const char* ssid = "ESP8266-blink"; // Nome da rede Wi-Fi do Access Point
const char* password = "password"; // Senha para o Access Point

const int ledPin = 2; // Led do ESP8266
bool ledState = false; // Estado atual do LED

ESP8266WebServer server(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Controle do LED</h1>";
  html += "<p>LED: ";
  html += (ledState) ? "Ligado" : "Desligado";
  html += "</p>";
  html += "<p><a href=\"/on\"><button>Ligar</button></a></p>";
  html += "<p><a href=\"/off\"><button>Desligar</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleOn() {
  ledState = true;
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleOff() {
  ledState = false;
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
