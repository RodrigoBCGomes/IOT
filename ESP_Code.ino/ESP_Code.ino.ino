//Bibliotecas
#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Definilões
#define led D8

//Variáveis LED
bool stateLedApi;
unsigned long lastTime = 0;
unsigned long timerDelayLed = 10;

//Variáveis sensor ultrassônico
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 50;
const int trigPin = D6;
const int echoPin = D5;

//Velocidade do COM em cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch

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
  http.begin(client,"https://iot-rodrigo.onrender.com/");
  int httpCode = http.GET();
  if(httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }else{
    Serial.print("Erro ao tentar pegar os dados da API.");
  }
}

void loop() {
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();
  http.begin(client,"https://iot-rodrigo.onrender.com/led/state-led");
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.print(payload);

  StaticJsonDocument<54> doc;

  DeserializationError error = deserializeJson(doc,payload);
  if(error) {
    Serial.print("Deu erro em transformar em documento o nosso Json da API.");
    Serial.println(error.f_str());
  }
  bool state = doc["state"];
  Serial.println(state);
  digitalWrite(led,state);
  delay(10);
  
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(500);
}
