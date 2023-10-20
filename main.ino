#include <DHT.h> //Biblioteca para funcionamento do sensor de temperatura e umidade DHT11
#include <ThingerESP8266.h>
#include <SPI.h>


#define DHTPIN 4 //Pino digital D2 (GPIO4) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11

#define USERNAME "eduardossaleme"
#define DEVICE_ID "testando"
#define DEVICE_CREDENTIAL "&ksGZ9eb+0q!vFQ5"

#define SSID "Fabio Saleme Oi Fibra 2.4Ghz"
#define SSID_PASSWORD "02050093"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)

void setup() {
  thing.add_wifi(SSID, SSID_PASSWORD);
  pinMode(LED_BUILTIN, OUTPUT);
  thing["led"] << digitalPin(LED_BUILTIN);
  thing["millis"] >> outputValue(millis());
  Serial.begin(115200); //Inicializa a comunicação serial
  delay(50); // ?Intervalo para aguardar a estabilização do sistema
  dht.begin(); //Inicializa o sensor DHT11
  thing["dht11"] >> [](pson& out){
    // Add the values and the corresponding code
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
  };

}
void loop(){
  thing.handle();
}