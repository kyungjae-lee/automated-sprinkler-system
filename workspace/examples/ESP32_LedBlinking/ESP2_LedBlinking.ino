// LED on GPIO2
#define LED_PIN 2

void setup() {
  // Set LED as output
  pinMode(LED_PIN, OUTPUT);

  // Serial monitor setup
  Serial.begin(115200);
}

void loop() {
  Serial.print("Hello");
  digitalWrite(LED_PIN, HIGH);

  delay(500);

  Serial.println(" world!");
  digitalWrite(LED_PIN, LOW);

  delay(500);
}
