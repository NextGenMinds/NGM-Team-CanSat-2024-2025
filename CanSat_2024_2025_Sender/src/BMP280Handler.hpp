#ifndef BMP280HANDLER_HPP
#define BMP280HANDLER_HPP

#include <Adafruit_Sensor.h>   // Core library for sensor functionality
#include <Adafruit_BMP280.h>  // Library for BMP280 sensor operations

/**
 * @brief A structure to hold temperature and pressure data read from the BMP280 sensor.
 */
struct BMP280Data {
    float temperature; // Temperature in Celsius
    float pressure;    // Pressure in hPa
};

/**
 * @brief A handler class for interacting with the BMP280 sensor.
 * 
 * This class initializes the BMP280 sensor, retrieves data such as temperature and pressure, 
 * and ensures proper communication using the I2C protocol.
 */
class BMP280Handler {
public:
    /**
     * @brief Constructor for the BMP280Handler.
     * @param sdaPin The pin used for SDA (data line) communication.
     * @param sclPin The pin used for SCL (clock line) communication.
     * @param i2cAddr The I2C address of the BMP280 sensor.
     */
    BMP280Handler(uint8_t sdaPin, uint8_t sclPin, uint8_t i2cAddr);

    /**
     * @brief Initializes the BMP280 sensor and I2C communication.
     */
    void begin();

    /**
     * @brief Reads the temperature and pressure data from the BMP280 sensor.
     * @return A BMP280Data structure containing the latest temperature and pressure readings.
     */
    BMP280Data getData();

private:
    Adafruit_BMP280 bmp; // Instance of the BMP280 library for sensor interactions
    uint8_t sdaPin;      // Pin for the Serial Data Line (SDA)
    uint8_t sclPin;      // Pin for the Serial Clock Line (SCL)
    uint8_t i2cAddr;     // I2C address of the BMP280 sensor
};

#endif // BMP280HANDLER_HPP
