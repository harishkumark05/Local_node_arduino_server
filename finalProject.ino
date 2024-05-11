#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

#define SMOKE_SENSOR A0  // Analog pin for smoke sensor
#define PIR_SENSOR 6      // Digital pin for PIR sensor
#define BUZZER_PIN 8      // Digital pin for buzzer

SoftwareSerial BTSerial(9, 10); // RX, TX
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  lcd.begin(16, 2);
  pinMode(PIR_SENSOR, INPUT); // Set the PIR sensor pin as an input
  pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output
  lcd.print("Harish");
  lcd.clear();
}

void loop() {
  delay(1000);

  float temperature = readTemperature();
  int smokeValue = analogRead(SMOKE_SENSOR);
  int motionDetected = digitalRead(PIR_SENSOR);

  // Print temperature, smoke value, and motion detection to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Smoke Value: ");
  Serial.println(smokeValue);
  Serial.print("Motion Detected: ");
  Serial.println(motionDetected);

  // Construct JSON data string
  String smokeStatus;
  if (smokeValue <= 70) {
    smokeStatus = "Nothing Detected";
  } else if (smokeValue <= 300) {
    smokeStatus = "Smoke Detected";
  } else {
    smokeStatus = "Gas Detected";
  }

  // String jsonData = "{\"temperature\": " + String(temperature) + ", \"smoke\": " + String(smokeValue) + ", \"smoke_status\": \"" + smokeStatus + "\", \"motion\": " + String(motionDetected) + "}\n";

String jsonData = "{\"temperature\": " + String(temperature) + ", \"smoke\": \"" + String(smokeValue) + "\", \"gas\": \"" + String(smokeValue) + "\", \"motion\": " + String(motionDetected) + "}\n";

  // Send JSON data over Bluetooth and display on LCD if available
  if (BTSerial.available()) {
    BTSerial.println(jsonData);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C ");

  // Display smoke or gas detection on LCD
  lcd.setCursor(0, 1);
  if (smokeValue > 70) {
    lcd.print(smokeStatus);
  } else {
    lcd.print("No Smoke/Gas");
  }

  // Check if gas is detected or motion is detected and activate buzzer
  if (smokeValue > 300 || motionDetected == HIGH) { // Adjust threshold value as needed
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
    delay(1000); // Buzz for 1 second
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }
  
  delay(5000);
}

float readTemperature() {
  // Read the raw analog value from the LM35 sensor
  // int rawValue = analogRead(LM35_PIN);
  int sensorValue = analogRead(A1); // Replace with your data source

  // Convert the raw value to voltage (in millivolts)
  // float voltage = rawValue * (5000.0 / 1024.0);

  // Convert voltage to temperature in Celsius
  // float temperatureC = voltage / 10.0;
  float temperatureC =  (sensorValue) * (3930.0 / 1024) / 10 ;

  return temperatureC;
}
