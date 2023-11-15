#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

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

WebSocketsServer webSocket = WebSocketsServer(81);

// Autenticação wi-fi - Coloque aqui a sua configuração
const char* ssid     = "2G CASA 2";
const char* password = "a3b3c3d3e3f3";

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

  pinMode(MOTOR1_PINO_POS,OUTPUT);  
  pinMode(MOTOR1_PINO_NEG,OUTPUT);
  pinMode(MOTOR2_PINO_POS,OUTPUT);
  pinMode(MOTOR2_PINO_NEG,OUTPUT);

  para();
}

void loop() {
  webSocket.loop();

  /*frente();
  delay(5000);
  para();
  delay(2000);
  tras();
  delay(5000);
  para();
  delay(2000);
  direita();
  delay(5000);
  para();
  delay(2000);
  esquerda();
  delay(5000);
  para();
  delay(2000);*/
}
