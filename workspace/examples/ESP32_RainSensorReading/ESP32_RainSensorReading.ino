// File		: ESP32_RainSensorReading.ino
// Brief	: Program to demonstrate rain sensor data reading on ESP32
// Author	: Kyungjae Lee
// Date		: Aug 07, 2023
//
// Note		: The design is intended to activate the rain sensor only during
//			  data reading, thereby minimizing the risk of copper wire corrosion
//		 	  in the rain sensor.

// Pin definitions
#define rainSensorPowerPin		15	// GPIO Pin 15
#define rainSensorDigitalPin	4	// GPIO Pin 4

void setup()
{
	// Initialize the rain sensor (Power off)
	pinMode(rainSensorPowerPin, OUTPUT);
	digitalWrite(rainSensorPowerPin, LOW);

	// Set the baud rate (bps) for serial data transmission (For communicating with
	// Serial Monitor, make sure to use one of the baud rates listed in the menu at
	// the bottom right corner of its screen.) 
	Serial.begin(115200);
}

void loop()
{
	// Read rain sensor data (digital)
	int val = readRainSensor();

	// Print the rain sensor data and its weather representation
	Serial.print("Rain sensor reading (digital): ");
	Serial.println(val);
	if (val)
	{
		Serial.println("Weather: Clear");
	}
	else
	{
		Serial.println("Weather: Raining");
	}

	// Print data every 1 second
	delay(1000);
	Serial.println();
}

// Reads rain sensor data (digital)
int readRainSensor()
{
	// Activate rain sensor
	digitalWrite(rainSensorPowerPin, HIGH);
	
	delay(10);

	// Read rain sensor data (digital)
	int val = digitalRead(rainSensorDigitalPin);
	
	// Deactivate rain sensor
	digitalWrite(rainSensorPowerPin, LOW);
	
	return val;
}
