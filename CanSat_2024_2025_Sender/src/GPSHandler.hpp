#ifndef GPSHANDLER_HPP
#define GPSHANDLER_HPP

#include <Arduino.h>          // Core Arduino functionality
#include <SoftwareSerial.h>   // Library for serial communication on arbitrary pins
#include <TinyGPSPlus.h>      // Library for parsing GPS NMEA data

/**
 * @brief A handler class for interacting with a GPS module.
 * 
 * This class provides functionality to initialize the GPS module, 
 * configure its settings, and retrieve GPS data such as location, time, speed, and altitude.
 */
class GPSHandler {
private:
    SoftwareSerial gpsSerial;  // Software serial for communicating with the GPS module
    TinyGPSPlus gps;           // TinyGPSPlus instance for parsing GPS data

    /**
     * @brief Sends a UBX message to the GPS module.
     * 
     * UBX messages are used to configure the GPS module with specific settings.
     * 
     * @param msg Pointer to the UBX message array.
     * @param len Length of the UBX message array.
     */
    void sendUBX(byte* msg, uint8_t len);

    /**
     * @brief Waits for GPS data for a specified duration while processing incoming data.
     * 
     * @param ms The duration to wait for incoming GPS data in milliseconds.
     * @param serial Reference to the software serial interface.
     * @param gps Reference to the TinyGPSPlus instance for data parsing.
     */
    static void smartDelay(unsigned long ms, SoftwareSerial& serial, TinyGPSPlus& gps);

    // Predefined UBX message to set the GPS update rate to 2 Hz
    const byte setRateTo2Hz[14] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xF4, 0x01, 0x01, 0x00, 0x01, 0x00, 0x24, 0x1D};

public:
    /**
     * @brief Constructor for GPSHandler.
     * 
     * Initializes the handler with specified RX, TX pins and baud rate for communication.
     * 
     * @param rxPin The pin connected to the GPS module's TX pin.
     * @param txPin The pin connected to the GPS module's RX pin.
     * @param baudRate The baud rate for GPS communication.
     */
    GPSHandler(uint8_t rxPin, uint8_t txPin, uint32_t baudRate);

    /**
     * @brief Initializes the GPS module and configures its settings.
     * 
     * This function sets the GPS update rate and ensures the serial interface is operational.
     * 
     * @param baudRate The baud rate for GPS communication.
     */
    void initialize(uint32_t baudRate);

    /**
     * @brief Reads data from the GPS module.
     * 
     * Retrieves GPS location, time, speed, altitude, and satellite count.
     * 
     * @param latitude Reference to store the latitude.
     * @param longitude Reference to store the longitude.
     * @param day Reference to store the day of the date.
     * @param month Reference to store the month of the date.
     * @param year Reference to store the year of the date.
     * @param hour Reference to store the hour.
     * @param minute Reference to store the minute.
     * @param second Reference to store the second.
     * @param speedKPH Reference to store the speed in km/h.
     * @param course Reference to store the course in degrees.
     * @param altitude Reference to store the altitude in meters.
     * @param satellites Reference to store the number of satellites in view.
     */
    void readGPS(double& latitude, double& longitude, int& day, int& month, int& year,
                 int& hour, int& minute, int& second, double& speedKPH, double& course,
                 double& altitude, uint32_t& satellites);
};

#endif // GPSHANDLER_HPP
