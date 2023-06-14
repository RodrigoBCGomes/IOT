#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define led D8

bool stateLedApi;

void setup() {
//Conctando no WIFI
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.print("Conectando no WIFI: ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi connected!");
  
  pinMode(led,OUTPUT);

//Criar um cliente para o site
  WiFiClientSecure client;
  HTTPClient http;

//Desativando o SSL
  client.setInsecure();
  http.begin(client,"https://iot-rodrigo.onrender.com");
  int httpCode = http.GET();
  if(httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }else{
    Serial.print("Erro ao tentar pegar os dados da API.");
  }
}

void loop() {
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
