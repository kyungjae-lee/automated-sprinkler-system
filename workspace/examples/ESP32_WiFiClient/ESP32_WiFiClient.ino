// File		: ESP32_WiFiClient
// Brief	: Program to send data with a socket client on the Arduino core
// Author	: Kyungjae Lee
// Date		: Aug 08, 2023

#include <WiFi.h>

const char *ssid = "LIEBE-2.4G";
const char *password = "20180303";

WiFiServer server(12345);  // Port for communication

int rainSensorValue = 0;  // Variable to store rain sensor value

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");

    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("Received request: " + request);

        if (request == "get_data") {
          // Send rain sensor value to the server
          client.println(rainSensorValue);
          Serial.println("Sensor value sent to server");
        }
        
        delay(500); // Small delay
      }
    }
    
    //client.stop();
    //Serial.println("Client disconnected");
  }

  // Simulate reading rain sensor value (replace with actual reading)
  rainSensorValue ^= 1; // Assuming rain sensor is connected to GPIO 2
  delay(500); // Read and update sensor value every 1 second
}
