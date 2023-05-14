#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

// WiFi Esp8266 Config
IPAddress localIp(192,168,1,1);
IPAddress gatewayIp(192,168,1,1);
IPAddress subnet(255,255,255,0);
const char *ssid="esp8266_swa";
const char *pwd="swa12345678";

// Home Page
void handle_home_page() {
  String html = "<html><body><h1>Hello, world!</h1></body></html>";
  server.send(200, "text/html", html);
}

void setup() {
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
  // server.on("/led/on", handle_led_on);
  // server.on("/led/off", handle_led_off);
  server.begin();
}

void loop() {
  server.handleClient();
}