#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Villa Al-Aziz (Hamza)";
const char* password = "Saralona1996";

// Motor driver pins
//const int motor1Pin1 = D1;
//const int motor1Pin2 = D2;
//const int motor2Pin1 = D3;
//const int motor2Pin2 = D4;

ESP8266WebServer server(80);

void handleForward() {
  Serial.print("Forward Command\r\n");
}

void handleReverse() {
  Serial.print("Reverse Command\r\n");
}

void handleRight() {
  Serial.print("Right Command\r\n");
}

void handleLeft() {
  Serial.print("Left Command\r\n");
}

void setup() {
  // Initialize motor pins as output
//  pinMode(motor1Pin1, OUTPUT);
//pinMode(motor1Pin2, OUTPUT);
//pinMode(motor2Pin1, OUTPUT);
//pinMode(motor2Pin2, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.begin(9600);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);

  server.begin();
  Serial.println("Web server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

