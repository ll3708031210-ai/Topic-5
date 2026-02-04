#include "ThingSpeak.h"
#include "WiFiEsp.h"

// WiFi credentials
char ssid[] = "EE3070_P1615_1";
char pass[] = "EE3070P1615";

// Public weather station channel (example)
unsigned long weatherStationChannelNumber = 12397;
unsigned int temperatureFieldNumber = 1;

WiFiEspClient client;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  
  WiFi.init(&Serial1);
  
  // Connect to WiFi
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnected!");
  
  ThingSpeak.begin(client);
}

void loop() {
  // Read temperature from public channel
  float temperature = ThingSpeak.readFloatField(weatherStationChannelNumber, temperatureFieldNumber);
  
  int statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200) {
    Serial.print("Temperature: ");
    Serial.println(temperature);
  } else {
    Serial.print("Error reading data. Status: ");
    Serial.println(statusCode);
  }
  
  delay(20000); // Wait 20 seconds
}