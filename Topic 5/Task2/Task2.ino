#include "ThingSpeak.h"
#include "WiFiEsp.h"

// WiFi credentials
char ssid[] = "EE3070_P1615_1";
char pass[] = "EE3070P1615";

// Your ThingSpeak channel
unsigned long myChannelNumber = 3250036;
const char* myWriteAPIKey = "K20Y1E389DS2SUPE";

WiFiEspClient client;
int uploadCount = 0;

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
}

void loop() {
  if (uploadCount < 5) {
    // Generate random values
    int value1 = random(0, 100);
    int value2 = random(0, 100);
    
    // Set fields before writing
    ThingSpeak.setField(1, value1);
    ThingSpeak.setField(2, value2);
    
    // Write all fields at once
    int statusCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    
    if (statusCode == 200) {
      Serial.print("Upload #"); Serial.print(uploadCount + 1);
      Serial.print(" - Field1: "); Serial.print(value1);
      Serial.print(", Field2: "); Serial.println(value2);
    } else {
      Serial.print("Upload failed. Status: ");
      Serial.println(statusCode);
    }
    
    uploadCount++;
    delay(60000); // Wait 1 minute (ThingSpeak free limit: 15 sec minimum)
  }
}