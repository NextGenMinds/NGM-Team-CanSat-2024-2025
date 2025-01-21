#ifndef UTILS_HPP
#define UTILS_HPP

#include <Arduino.h>             // Core Arduino functionality
#include <RS-FEC.h>              // Library for Reed-Solomon error correction
#include <OLEDHandler.hpp>       // Handler for OLED display
#include <vector>                // Standard vector library
#include <string>                // Standard string library

/**
 * @brief A utility class providing various helper functions for data processing.
 * 
 * This class includes functions for creating data strings, encoding messages 
 * with error correction, updating OLED displays, and converting between bits and bytes.
 */
class Utils {
public:
    /**
     * @brief Creates a formatted data string from various inputs.
     * 
     * Combines GPS, sensor, and other telemetry data into a single, comma-separated string.
     * 
     * @param messageNumber The message counter.
     * @param latitude Latitude in degrees.
     * @param longitude Longitude in degrees.
     * @param day Day of the date.
     * @param month Month of the date.
     * @param year Year of the date.
     * @param hour Current hour.
     * @param minute Current minute.
     * @param second Current second.
     * @param speedKPH Speed in km/h.
     * @param course Course in degrees.
     * @param altitude Altitude in meters.
     * @param satellites Number of satellites in view.
     * @param pressure Atmospheric pressure in hPa.
     * @param temperature Temperature in Celsius.
     * @return A formatted string containing the input data.
     */
    static String createDataString(int messageNumber, double latitude, double longitude, int day,
                                   int month, int year, int hour, int minute, int second,
                                   double speedKPH, double course, double altitude,
                                   uint32_t satellites, double pressure, double temperature);

    /**
     * @brief Encodes a message using Reed-Solomon error correction.
     * 
     * Pads the input message and encodes it for reliable transmission.
     * 
     * @param dataString The input data string to encode.
     * @param message Buffer to store the padded message.
     * @param messageSize Size of the message buffer.
     * @param encoded Buffer to store the encoded data.
     * @param encodedSize Size of the encoded buffer.
     * @param rs Reference to the Reed-Solomon encoder.
     */
    static void encodeMessage(const String& dataString, char* message, size_t messageSize,
                              char* encoded, size_t encodedSize, RS::ReedSolomon<96, 32>& rs);

    /**
     * @brief Updates the OLED display with telemetry data.
     * 
     * Displays latitude, longitude, altitude, temperature, and pressure on the OLED screen.
     * 
     * @param oledHandler Reference to the OLEDHandler instance.
     * @param latitude Latitude in degrees.
     * @param longitude Longitude in degrees.
     * @param altitude Altitude in meters.
     * @param temperature Temperature in Celsius.
     * @param pressure Atmospheric pressure in hPa.
     */
    static void updateOLED(OLEDHandler& oledHandler, double latitude, double longitude,
                           double altitude, double temperature, double pressure);

    /**
     * @brief Converts a binary string into a vector of bits.
     * 
     * @param input The input binary string.
     * @param bitInput Vector to store the resulting bits.
     */
    static void vectorToBits(const std::string& input, std::vector<uint8_t>& bitInput);

    /**
     * @brief Converts a vector of bits into a vector of bytes.
     * 
     * @param bits The input vector of bits.
     * @param bytes Vector to store the resulting bytes.
     * @param bitLength The length of the bit stream.
     */
    static void bitsToBytes(const std::vector<uint8_t>& bits, std::vector<uint8_t>& bytes, uint16_t& bitLength);
};

#endif // UTILS_HPP
