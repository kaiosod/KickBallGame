#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// Exemplo 
const int LED_PIN = 2;

// WiFi Esp8266 Config
IPAddress localIp(192,168,1,1);
IPAddress gatewayIp(192,168,1,1);
IPAddress subnet(255,255,255,0);
const char *ssid="KickBall";
const char *pwd="kgb102030";

// Home Page
void handle_home_page() {
  String html = "<html><body><h1>Hello, world!</h1></body></html>";
  // File file = SPIFFS.open("/index.html", "r");
  // String html = file.readString();
  server.send(200, "text/html", html);
}

// Exemplo
void handle_led_on() {
  digitalWrite(LED_PIN, HIGH);
}

//Exemplo
void handle_led_off() {
  digitalWrite(LED_PIN, LOW);
}

void setup() {

  // Exemplo
  pinMode(LED_PIN, OUTPUT);

  // Setup Wifi
  Serial.begin(9600);
  Serial.println("Inicializando AP...");
  if (WiFi.softAP(ssid, pwd)) {
    Serial.println("AP disponivel....");
    WiFi.softAPConfig(localIp, gatewayIp, subnet);
    delay(200);
  }
  Serial.println("Wifi AP disponivel...");
  server.on("/", handle_home_page);
  server.on("/led/on", handle_led_on);
  server.on("/led/off", handle_led_off);
  server.begin();
}

void loop() {
  server.handleClient();
}