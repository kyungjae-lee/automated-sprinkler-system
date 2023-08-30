// File		: ESP32_WiFiServer
// Brief	: Program to create a WiFi access point and provide a web server on it
// Author	: Kyungjae Lee
// Date		: Aug 08, 2023

#include <WiFi.h>

// Set these to your desired credentials.
// To use a password, make sure that it has MORE THAN 7 characters.
const char *ssid = "LIEBE-2.4G";
const char *password = "20180303";
const char* clientIP = "192.168.0.187"; // IP address of the client ESP32
const int clientPort = 12345; // Port for communication

WiFiClient client;

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
}

void loop() {
  if (client.connect(clientIP, clientPort)) {
    Serial.println("Connected to client");
    
    // Request rain sensor value from client
    client.println("get_data");
    
    // Read and print the client's response (rain sensor value)
    while (client.available()) {
      String response = client.readStringUntil('\r');
      Serial.println("Rain sensor value from client: " + response);
    }
    
    client.stop();
    Serial.println("Connection to client closed");
  } else {
    Serial.println("Connection to client failed");
  }
  
  delay(1500); // Request data every 5 seconds
}
