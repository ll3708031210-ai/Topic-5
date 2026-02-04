#include "ThingSpeak.h"
#include "WiFiEsp.h"

// WiFi credentials
char ssid[] = "EE3070_P1615_1";
char pass[] = "EE3070P1615";

// Your ThingSpeak channel
unsigned long myChannelNumber = 3250036;
const char* myReadAPIKey = "2NOO2GGNGT552D5G";

WiFiEspClient client;


void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  
  
  
  WiFi.init(&Serial1);
  
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnected!");
  
  ThingSpeak.begin(client);
  Serial.println("Press button to read data...");
}

void loop() {
    // Read Field 1
    float value = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);

    int statusCode = ThingSpeak.getLastReadStatus();
    if (statusCode == 200) {
        // Get created time
        String createdAt = ThingSpeak.readCreatedAt(myChannelNumber, myReadAPIKey);

        Serial.print("Field 1 Value: ");
        Serial.println(value);
        Serial.print("Created At: ");
        Serial.println(createdAt);
        Serial.println();
    } else {
        Serial.print("Read failed. Status: ");
        Serial.println(statusCode);
    }

    delay(20000);  // Read every 20 seconds (ThingSpeak free tier limit)
}