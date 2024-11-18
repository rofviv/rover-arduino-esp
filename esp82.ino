#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "OMEN-PC"
#define STAPSK  "Pass123!"
#define EEPROM_SIZE 9
#endif

ESP8266WebServer server(80);

const char* ssid     = STASSID;
const char* password = STAPSK;

int relay1 = 5, relay2 = 4, relay3 = 0, relay4 = 15;
int relay5 = 13, relay6 = 12, relay7 = 14, relay8 = 16;
int state1 = HIGH, state2 = HIGH, state3 = HIGH, state4 = HIGH;
int state5 = HIGH, state6 = HIGH, state7 = HIGH, state8 = HIGH;

void checkStatusRelay(){
  StaticJsonBuffer<800> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["relay1"]= state1;
  root["relay2"]= state2;
  root["relay3"]= state3;
  root["relay4"]= state4;
  root["relay5"]= state5;
  root["relay6"]= state6;
  root["relay7"]= state7;
  root["relay8"]= state8;
  root["ssid"]= ssid;
  
  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate1() {
  state1 = !state1;
  digitalWrite(relay1, state1);
  EEPROM.write(1, state1);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state1;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate2() {
  state2 = !state2;
  digitalWrite(relay2, state2);
  EEPROM.write(2, state2);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state2;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate3() {
  state3 = !state3;
  digitalWrite(relay3, state3);
  EEPROM.write(3, state3);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state3;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate4() {
  state4 = !state4;
  digitalWrite(relay4, state4);
  EEPROM.write(4, state4);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state4;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate5() {
  state5 = !state5;
  digitalWrite(relay5, state5);
  EEPROM.write(5, state5);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state5;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate6() {
  state6 = !state6;
  digitalWrite(relay6, state6);
  EEPROM.write(6, state6);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state6;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate7() {
  state7 = !state7;
  digitalWrite(relay7, state7);
  EEPROM.write(7, state7);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state7;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void handlestate8() {
  state8 = !state8;
  digitalWrite(relay8, state8);
  EEPROM.write(8, state8);
  EEPROM.commit();

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();
  root["status"]= "Success";
  root["data"]= state8;

  String json;
  root.prettyPrintTo(json);
  server.send(200, "text/json", json);
}

void setrelaystate() { 
  digitalWrite(relay1, state1);
  digitalWrite(relay2, state2);
  digitalWrite(relay3, state3);
  digitalWrite(relay4, state4);
  digitalWrite(relay5, state5);
  digitalWrite(relay6, state6);
  digitalWrite(relay7, state7);
  digitalWrite(relay8, state8);
}

void getstate() { 
  state1 = EEPROM.read(1);
  state2 = EEPROM.read(2);
  state3 = EEPROM.read(3);
  state4 = EEPROM.read(4);
  state5 = EEPROM.read(5);
  state6 = EEPROM.read(6);
  state7 = EEPROM.read(7);
  state8 = EEPROM.read(8);
  setrelaystate();
}

void setup() {
  Serial.begin(115200);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    state1 = HIGH;
    digitalWrite(relay1, state1);
    delay(1000);
    state1 = LOW;
    digitalWrite(relay1, state1);
    delay(1000);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  server.on("/", checkStatusRelay);
  server.on("/relay1", handlestate1);
  server.on("/relay2", handlestate2);
  server.on("/relay3", handlestate3);
  server.on("/relay4", handlestate4);
  server.on("/relay5", handlestate5);
  server.on("/relay6", handlestate6);
  server.on("/relay7", handlestate7);
  server.on("/relay8", handlestate8);

  server.begin();
  getstate();
  delay(1000);
  state1 = HIGH;
  digitalWrite(relay1, state1);
}

void loop() {
  server.handleClient();
}
