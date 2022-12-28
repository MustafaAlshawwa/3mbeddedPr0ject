#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//  WiFi credentials
const char* ssid = "OrangeFlybox_1FD4";
const char* password = "70323320";

// movement signal pins
const int RC5 = D5;
const int RC6 = D6;
const int RC7 = D7;

ESP8266WebServer server(80);

LiquidCrystal_I2C lcd(0x27,16,2);

void handleStop() {
  digitalWrite(RC5, 0);
}

void handleForward() {  
  digitalWrite(RC5, 1);
  digitalWrite(RC6, 1);
  digitalWrite(RC7, 1);
  delay(250);
  digitalWrite(RC5, 0);
}

void handleReverse() {
  digitalWrite(RC5, 1);
  digitalWrite(RC6, 0);
  digitalWrite(RC7, 0);
  delay(250);
  digitalWrite(RC5, 0);
}

void handleRight() {
  digitalWrite(RC5, 1);
  digitalWrite(RC6, 0);
  digitalWrite(RC7, 1);
  delay(250);
  digitalWrite(RC5, 0);
}

void handleLeft() {
  digitalWrite(RC5, 1);
  digitalWrite(RC6, 1);
  digitalWrite(RC7, 0);
  delay(250);
  digitalWrite(RC5, 0);
}

void handleLCD() {
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(server.arg(0));
  Serial.print(server.arg(0) + "\r\n");
}

void setup() {
//  Init Signal pins as output
  pinMode(RC5, OUTPUT);
  pinMode(RC6, OUTPUT);
  pinMode(RC7, OUTPUT);

//  Init LCD  
  lcd.init(); 
  lcd.backlight();
  

//  Init WiFi
  WiFi.begin(ssid, password);
  Serial.begin(9600);

//  Print on serial until Connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

//  Init server commands
  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/lcd", handleLCD);

// Begin Server
  server.begin();
  Serial.println("Web server started\r\n");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
