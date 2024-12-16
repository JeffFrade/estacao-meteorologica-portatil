// Usar ESP32 (ESP32-WROOM-Da Module)

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <TinyGPS++.h>
#include <WiFi.h>
#include <SoftwareSerial.h>

// Hostmane = Nome da sua placa ESP32 dentro da sua rede
const char* HOSTNAME = "estacao_meteorologica_esp";

// Preencher SSID com o nome da sua rede Wi-Fi e PASSWORD com a senha (Se houver).
const char* SSID = "nome_rede"; // rede wifi
const char* PASSWORD = "senha_rede"; // senha da rede wifi

// LED
#define redLed 13
#define greenLed 33
#define blueLed 12

// DHT
#define dhtPin 18
// Caso queira utilizar um DHT11, basta comentar a linha abaixo (25) e descomentar a linha 26
#define dhtType DHT22
// #define dhtType DHT11

// BMP
// Caso apresente problemas ao inicializar, trocar 0x76 por 0x77
#define addr 0x76

void initSerial();
void initWiFi();

Adafruit_BMP280 bmp;
DHT dht(dhtPin, dhtType);
SoftwareSerial gpsSerial(16, 17); // RX, TX
TinyGPSPlus gps;

void setup() {
  initSerial();
  Serial.println(F("Inicializando estação meteorológica"));

  dht.begin();

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, HIGH);

  if (!bmp.begin(addr)) {
    Serial.println(F("Erro ao iniciar o BMP280"));

    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    
    digitalWrite(redLed, HIGH);
    delay(2000);
    digitalWrite(redLed, LOW);
    delay(2000);
  }
  
  initWiFi();
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
}

void initSerial() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void initWiFi() {
  delay(10);
  Serial.println("Conectando-se em: " + String(SSID));
  
  WiFi.setHostname(HOSTNAME);
  WiFi.begin(SSID, PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.print("Conectado na Rede " + String(SSID) + " | IP => ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("Iniciando coletas");

  // Caso o roteador caia, a cada execução ele veriica se está conectado, se não estiver quando o roteador voltar, ele volta a conectar sozinho, sem necessidade de reiniciar.
  conectaWiFi();
  gpsAvailable();

  Serial.println("---------------------------------");

  digitalWrite(blueLed, HIGH);
  
  Serial.print(F("Temperatura: "));
  Serial.print(dht.readTemperature());
  Serial.println(F(" ºC"));

  Serial.print(F("Umidade: "));
  Serial.print(dht.readHumidity());
  Serial.println(F(" %"));
  
  Serial.print(F("Pressão: "));
  Serial.print(bmp.readPressure());
  Serial.println(F(" Pa"));

  Serial.print(F("Altitude: "));
  Serial.print(bmp.readAltitude());
  Serial.println(F(" m"));

  Serial.print(F("Latitude: "));
  Serial.println(gps.location.lat());

  Serial.print(F("Longitude: "));
  Serial.println(gps.location.lng());

  Serial.print(F("Velocidade: "));
  Serial.print(gps.speed.kmph());
  Serial.println(F(" km/h"));

  digitalWrite(blueLed, LOW);

  Serial.println("---------------------------------");

  digitalWrite(greenLed, HIGH);
  delay(1000);
  digitalWrite(greenLed, LOW);
}

void conectaWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
     return;
  }

  WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI  
  while (WiFi.status() != WL_CONNECTED) {
      delay(100);
  }
}
