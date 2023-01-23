#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OrangeFlybox_1FD4";
const char* password = "70323320";
WebServer server(80); 

const int RC5 = 13;
const int RC6 = 12;
const int RC7 = 14;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void handleStop() {
  digitalWrite(RC5, LOW);
  digitalWrite(RC6, LOW);
  digitalWrite(RC7, LOW);
}

void handleForward() {  
  digitalWrite(RC5, HIGH);
  digitalWrite(RC6, HIGH);
  digitalWrite(RC7, HIGH);
}

void handleReverse() {
  digitalWrite(RC5, HIGH);
  digitalWrite(RC6, LOW);
  digitalWrite(RC7, LOW);
}

void handleRight() {
  digitalWrite(RC5, HIGH);
  digitalWrite(RC6, LOW);
  digitalWrite(RC7, HIGH);
}

void handleLeft() {
  digitalWrite(RC5, HIGH);
  digitalWrite(RC6, HIGH);
  digitalWrite(RC7, LOW);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(RC5, OUTPUT);
  pinMode(RC6, OUTPUT);
  pinMode(RC7, OUTPUT);

  initWiFi();


  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
}

void loop() {
  server.handleClient();
}
