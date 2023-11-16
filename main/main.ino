#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
#include <ThingerESP8266.h>
#include <SPI.h>

#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15

#define MOTOR1_PINO_POS    D3
#define MOTOR1_PINO_NEG    D1
#define MOTOR2_PINO_POS    D4
#define MOTOR2_PINO_NEG    D5

#define DHTPIN 4 //Pino digital D2 (GPIO4) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

#define USERNAME "eduardossaleme"
#define DEVICE_ID "testando"
#define DEVICE_CREDENTIAL "&ksGZ9eb+0q!vFQ5"

#define SSID "PIC2-2.4G"
#define SSID_PASSWORD "engcomp@ufes"


WebSocketsServer webSocket = WebSocketsServer(81);

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

// Autenticação wi-fi - Coloque aqui a sua configuração
const char* ssid     = "PIC2-2.4G";
const char* password = "engcomp@ufes";

// Tratamento de eventos dos dados que vêm do cliente 
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) {
    case WStype_DISCONNECTED:
      break;

    case WStype_CONNECTED:
      { IPAddress ip = webSocket.remoteIP(num);
        Serial.println(ip);
      }
      break;

    case WStype_TEXT:
      { String text = String((char *) &payload[0]);
        Serial.println(text);
        Serial.println(num);
        Serial.println(type);

        if (text == "FRONT") {
          frente();
        } else if (text == "LEFT") {
          esquerda();
        } else if (text == "RIGHT") {
          direita();
        } else if (text == "BACK") {
          tras();
        } else if (text == "OFF") {
          para();
        }
      }
      break;

  }

}

void setaMotor(int motor1Positivo, int motor1Negativo, int motor2Positivo, int motor2Negativo) {
  digitalWrite(MOTOR1_PINO_POS, motor1Positivo);
  digitalWrite(MOTOR1_PINO_NEG, motor1Negativo);
  digitalWrite(MOTOR2_PINO_POS, motor2Positivo);
  digitalWrite(MOTOR2_PINO_NEG, motor2Negativo);
}

void para() {
  setaMotor(0, 0, 0, 0);
}

void frente() {
  setaMotor(255, 0, 255, 0);
}

void tras() {
  setaMotor(0, 255, 0, 255);
}

void direita() {
  setaMotor(0, 200, 200, 0);
}

void esquerda() {
  setaMotor(200, 0, 0, 200);
}

void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(". ");
    delay(100);
  }
  Serial.println(WiFi.localIP());
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  thing.add_wifi(SSID, SSID_PASSWORD);
  pinMode(LED_BUILTIN, OUTPUT);
  thing["led"] << digitalPin(LED_BUILTIN);
  thing["millis"] >> outputValue(millis());
  delay(50); // ?Intervalo para aguardar a estabilização do sistema
  dht.begin(); //Inicializa o sensor DHT11
  thing["dht11"] >> [](pson& out){
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
  };

  pinMode(MOTOR1_PINO_POS,OUTPUT);  
  pinMode(MOTOR1_PINO_NEG,OUTPUT);
  pinMode(MOTOR2_PINO_POS,OUTPUT);
  pinMode(MOTOR2_PINO_NEG,OUTPUT);

  para();
}

void loop() {
  webSocket.loop();
  thing.handle();
}
