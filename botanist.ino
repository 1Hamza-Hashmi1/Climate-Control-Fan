#include <LiquidCrystal.h>

// Motor control pins
#define ENABLE 5
#define DIRA 3
#define DIRB 4

// LCD pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Temperature sensor pin
int tempPin = 0;

void setup() {
  // Initialize motor control pins
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);

  // Set the motor direction to one way
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
}

void loop() {
  int tempReading = analogRead(tempPin);
  
  // Convert the analog reading to temperature in Celsius and Fahrenheit
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  float tempC = tempK - 273.15;            // Convert Kelvin to Celsius
  float tempF = (tempC * 9.0) / 5.0 + 32.0; // Convert Celsius to Fahrenheit

  // Display Temperature in Celsius
  lcd.setCursor(0, 0);
  lcd.print("Temp:        C  ");
  lcd.setCursor(6, 0);
  lcd.print(tempC, 1);

  // Display Temperature in Fahrenheit
  lcd.setCursor(0, 1);
  lcd.print("Temp:        F  ");
  lcd.setCursor(6, 1);
  lcd.print(tempF, 1);

  // Control the fan based on temperature
  if (tempC > 25.9) {
    analogWrite(ENABLE, 250); // Adjust this value for desired breeze strength (0-255)
    Serial.println("Fan ON - Gentle breeze mode");
  } else {
    analogWrite(ENABLE, 0);
    Serial.println("Fan OFF");
  }

  delay(1000); // Delay for LCD update and debouncing
}
