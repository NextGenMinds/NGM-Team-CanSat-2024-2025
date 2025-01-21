#include "BMP280Handler.hpp"
#include <Wire.h>       // I2C communication library
#include <Arduino.h>    // Core Arduino functionality

/**
 * @brief Constructor for BMP280Handler.
 * 
 * Initializes the handler with the specified SDA and SCL pins, 
 * and sets the I2C address for the BMP280 sensor.
 * 
 * @param sdaPin The pin used for SDA communication.
 * @param sclPin The pin used for SCL communication.
 * @param i2cAddr The I2C address of the BMP280 sensor.
 */
BMP280Handler::BMP280Handler(uint8_t sdaPin, uint8_t sclPin, uint8_t i2cAddr)
    : sdaPin(sdaPin), sclPin(sclPin), i2cAddr(i2cAddr) {}

/**
 * @brief Initializes the BMP280 sensor.
 * 
 * Sets up the I2C communication using the specified SDA and SCL pins.
 * If the BMP280 sensor fails to initialize, the program halts.
 */
void BMP280Handler::begin() {
    Wire.begin(sdaPin, sclPin); // Initialize I2C communication with specified pins
    if (!bmp.begin(i2cAddr)) {  // Attempt to initialize the BMP280 sensor
        Serial.println("BMP280 Initialization Failed"); // Log failure message
        while (1); // Halt execution if initialization fails
    }
    Serial.println("BMP280 Initialized"); // Log success message
}

/**
 * @brief Reads the temperature and pressure data from the BMP280 sensor.
 * 
 * Retrieves the latest readings for temperature (in Celsius) and pressure (in hPa)
 * from the BMP280 sensor and stores them in a BMP280Data structure.
 * 
 * @return A BMP280Data structure containing temperature and pressure readings.
 */
BMP280Data BMP280Handler::getData() {
    BMP280Data data; // Create a structure to hold the sensor data
    data.temperature = bmp.readTemperature(); // Read temperature in Celsius
    data.pressure = bmp.readPressure() / 100.0F; // Convert pressure from Pa to hPa
    return data; // Return the populated data structure
}
