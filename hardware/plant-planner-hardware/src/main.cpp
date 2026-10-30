#include <Arduino.h>
#include <DHT.h>
#include <WiFi.h>
#include <Wire.h>
#include <BH1750.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// A három szenzor deklarálása
#define DHTPIN 4
#define DHTTYPE DHT22
#define SOIL_PIN 36

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

// Wi-Fi név és jelszó
const char* ssid = "Pookie wifi";
const char* password = "pookiemookie";

// Szerver cím és api kulcs
const char* serverName = "http://httpbin.org/post"; // Tesztelés miatt
const char* apiKey = "API_KULCS_TESZT";

// Időzítő változók (millisec)
unsigned long previousMillis = 0;
const long timerInterval = 10000; // Most 10 másodperc, az éles verzióban 900000 (15 perc) lesz

void setup() {
  Serial.begin(115200);
  Wire.begin();
  dht.begin();
  lightMeter.begin();
  
  Serial.println("\n--- ESP32 indul ---");
  
  WiFi.begin(ssid, password);
  Serial.print("Csatlakozás a Wi-Fi-hez");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWi-Fi csatlakoztatva! IP: " + WiFi.localIP().toString());
  Serial.println("----------------------------------\n");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= timerInterval) {
    previousMillis = currentMillis;

    // Szenzorok kiolvasása
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int soilMoistureRaw = analogRead(SOIL_PIN);
    float lux = lightMeter.readLightLevel();

    // Adatok kiírása a Serial Monitorra
    Serial.printf("Hő: %.2f °C | Pára: %.2f %% | Talaj: %d | Fény: %.2f lx\n", temperature, humidity, soilMoistureRaw, lux);

    // HTTP POST küldés
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      
      http.begin(serverName);
      http.addHeader("Content-Type", "application/json");
      http.addHeader("x-api-key", apiKey);

      // JSON csomag
      StaticJsonDocument<200> doc;
      doc["temperature"] = temperature;
      doc["humidity"] = humidity;
      doc["soilMoisture"] = soilMoistureRaw;
      doc["light"] = lux;

      String requestBody;
      serializeJson(doc, requestBody);

      Serial.println("Adatok küldése a szerverre...");
      int httpResponseCode = http.POST(requestBody);

      if (httpResponseCode > 0) {
        Serial.print("Sikeres küldés! HTTP kód: ");
        Serial.println(httpResponseCode);
      } else {
        Serial.print("Hiba a küldés során. Hibakód: ");
        Serial.println(httpResponseCode);
      }
      
      http.end();
      Serial.println("----------------------------------");
    } else {
      Serial.println("Hiba: Nincs Wi-Fi kapcsolat!");
    }
  }
}