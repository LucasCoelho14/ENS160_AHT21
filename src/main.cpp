#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "ScioSense_ENS160.h"  // ENS160 library
#include <AHTxx.h> // include AHTxx library

ScioSense_ENS160 ens160(ENS160_I2CADDR_1); // I2C address of the ENS160 sensor
AHTxx aht21(AHTXX_ADDRESS_X38  , AHT2x_SENSOR); // I2C address and type of the AHT21 sensor

// Variable and device labels for Ubidots
#define VARIABLE_LABEL1 "AQI"
#define VARIABLE_LABEL2 "TVOC"
#define VARIABLE_LABEL3 "eCO2"
#define VARIABLE_LABEL4 "HP0"
#define VARIABLE_LABEL5 "HP1"
#define VARIABLE_LABEL6 "HP2"
#define VARIABLE_LABEL7 "HP3"
#define DEVICE_LABEL "ENS160_Station"
#define VARIABLE_LABEL8 "Temperature"
#define VARIABLE_LABEL9 "Humidity"

char payload[1000];
char topic1[150];
char topic2[150];
char topic3[150];
char topic4[150];
char topic5[150];
char topic6[150];
char topic7[150];
char topic8[150];
char topic9[150];

// Space to store values to send
char str_AQI[10];
char str_TVOC[10];
char str_eCO2[10];
char str_HP0[10];
char str_HP1[10];
char str_HP2[10];
char str_HP3[10];
char str_temperature[10];
char str_humidity[10];

void setup() {
  // Initialize serial communication and ENS160 sensor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("ENS160 - Digital air quality sensor");
  if (!ens160.begin()) {
    Serial.println("Could not find a valid ENS160 sensor, check wiring!");
    while (1);
  }
  Serial.println("ENS160 sensor found");
  ens160.setMode(ENS160_OPMODE_STD);  // Set standard mode of operation
  Serial.println("ENS160 sensor set to standard mode");

  if (!aht21.begin()) {
  Serial.println("Could not find a valid ATH21 sensor, check wiring!");
  while (1);
  }
  Serial.println("ATH21 sensor found");
  // aht21.setResolution(AHTXX_14BIT_RESOLUTION); // Set 14-bit resolution
  Serial.println("ATH21 sensor set to 14-bit resolution");

}

void loop() {
  // Perform a measurement and read the sensor values
  ens160.measure(0);
  float aqi = ens160.getAQI();
  float tvoc = ens160.getTVOC();
  float eco2 = ens160.geteCO2();
  float hp0 = ens160.getHP0();
  float hp1 = ens160.getHP1();
  float hp2 = ens160.getHP2();
  float hp3 = ens160.getHP3();

  // Read the temperature and humidity from the AHT21 sensor
  float temperature = aht21.readTemperature();
  float humidity = aht21.readHumidity();

  // Print out the sensor values for debugging
  Serial.println("Publishing value for AQI: " + String(aqi));
  Serial.println("Publishing value for TVOC: " + String(tvoc));
  Serial.println("Publishing value for eCO2: " + String(eco2));
  Serial.println("Publishing value for HP0: " + String(hp0));
  Serial.println("Publishing value for HP1: " + String(hp1));
  Serial.println("Publishing value for HP2: " + String(hp2));
  Serial.println("Publishing value for HP3: " + String(hp3));
  Serial.println("Publishing value for temperature: " + String(temperature));
  Serial.println("Publishing value for humidity: " + String(humidity));

  // Format the values as strings
  dtostrf(aqi, 5, 2, str_AQI);
  dtostrf(tvoc, 5, 2, str_TVOC);
  dtostrf(eco2, 5, 2, str_eCO2);
  dtostrf(hp0, 5, 2, str_HP0);
  dtostrf(hp1, 5, 2, str_HP1);
  dtostrf(hp2, 5, 2, str_HP2);
  dtostrf(hp3, 5, 2, str_HP3);
  dtostrf(temperature, 5, 2, str_temperature);
  dtostrf(humidity, 5, 2, str_humidity);
  delay(1000);
}