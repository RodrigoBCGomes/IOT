//Bibliotecas
#include ".\config.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Definições
#define led D8

//Variáveis LED
bool stateLedApi;
unsigned long lastTimeLed = 0;
unsigned long timerDelayLed = 10;

//Variáveis sensor ultrassônico
unsigned long lastTimeSensor = 0;
unsigned long timerDelaySensor = 50;
const int trigPin = D6;
const int echoPin = D5;

//Velocidade do COM em cm/uS
#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;
float distanceInch;

//Executado no começo do código
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

//Desligando o LED  
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

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

//Repete durante o código
void loop() {
//Conectando com o WIFI
  WiFiClientSecure client;
  HTTPClient http;
  client.setInsecure();

//Se o tempo atual (millis) menos a última marcação (lastTime) for menor que o tempo escohido, faz a tarefa e reinicia a marcação o tempo atual
  if((millis()-lastTimeLed > timerDelayLed)){
  
    http.begin(client,"https://iot-rodrigo.onrender.com/led/state-led");
    int httpCode = http.GET();
    String payload = http.getString();
    Serial.print(payload);

    StaticJsonDocument<54> doc;

//Erro no WIFI
    DeserializationError error = deserializeJson(doc,payload);
    if(error) {
      Serial.print("Deu erro em transformar em documento o nosso Json da API.");
      Serial.println(error.f_str());
  }

//Estado do LED  
    bool state = doc["state"];
    Serial.println(state);
    digitalWrite(led,state);    
    lastTimeLed = millis();
  }
//Lê o sinal
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;

  if((millis()-lastTimeSensor > timerDelaySensor)){
    http.begin(client,"https://iot-rodrigo.onrender.com/sensor/acesso");
    http.addHeader("Content-Type","application/json");
    StaticJsonDocument<100> SensorDocument;
    SensorDocument["nome"] = "Porta de entrada";
    SensorDocument["value"] = distanceCm;
    if(distanceCm < 150 and distanceCm > 50){
      char bufferDoJsonEmString[100];
      serializeJson(SensorDocument,bufferDoJsonEmString);
      int httpResponseCode = http.POST(bufferDoJsonEmString);
      String ResponceServer = http.getString();
      Serial.println(ResponceServer); 
    }
    lastTimeSensor = millis();
  }
}
