#include ".\config.h"
#include <ESP8266WiFI.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define led D8

bool stateLedApi;

void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
