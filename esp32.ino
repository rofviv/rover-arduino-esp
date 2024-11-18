#include <EEPROM.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "OMEN-PC"
#define STAPSK  "Pass123!"
#define EEPROM_SIZE 9
#endif

WebServer server(80);

const char* ssid     = STASSID;
const char* password = STAPSK;

int relay1 = 5, relay2 = 18, relay3 = 19, relay4 = 21;
int relay5 = 12, relay6 = 13, relay7 = 32, relay8 = 33;
int state1 = HIGH, state2 = HIGH, state3 = HIGH, state4 = HIGH;
int state5 = HIGH, state6 = HIGH, state7 = HIGH, state8 = HIGH;

void checkStatusRelay() {
  DynamicJsonDocument doc(800);
  doc["status"] = "Success";
  doc["relay1"] = state1;
  doc["relay2"] = state2;
  doc["relay3"] = state3;
  doc["relay4"] = state4;
  doc["relay5"] = state5;
  doc["relay6"] = state6;
  doc["relay7"] = state7;
  doc["relay8"] = state8;
  doc["ssid"] = ssid;

  String json;
  serializeJsonPretty(doc, json);
  server.send(200, "application/json", json);
}

void handleRelayState(int relay, int &state, int eepromAddr) {
  state = !state;
  digitalWrite(relay, state);
  EEPROM.write(eepromAddr, state);
  EEPROM.commit();

  DynamicJsonDocument doc(300);
  doc["status"] = "Success";
  doc["data"] = state;

  String json;
  serializeJsonPretty(doc, json);
  server.send(200, "application/json", json);
}

void handlestate1() { handleRelayState(relay1, state1, 1); }
void handlestate2() { handleRelayState(relay2, state2, 2); }
void handlestate3() { handleRelayState(relay3, state3, 3); }
void handlestate4() { handleRelayState(relay4, state4, 4); }
void handlestate5() { handleRelayState(relay5, state5, 5); }
void handlestate6() { handleRelayState(relay6, state6, 6); }
void handlestate7() { handleRelayState(relay7, state7, 7); }
void handlestate8() { handleRelayState(relay8, state8, 8); }

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
  // EEPROM.begin(EEPROM_SIZE);

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
}

void loop() {
  server.handleClient();
}
