#ifndef UTILS_HPP
#define UTILS_HPP

#include <Arduino.h>
#include <RS-FEC.h>
#include <OLEDHandler.hpp>
#include <vector>
#include <string>

/**
 * @class Utils
 * @brief Contains utility functions for message decoding, OLED updates, and data conversions.
 */
class Utils {
public:
    /**
     * @brief Decodes a Reed-Solomon encoded message.
     * @param payload The encoded payload to decode.
     * @param rs Reed-Solomon encoder/decoder instance.
     * @param repaired Buffer for storing the repaired message.
     * @param oled Reference to the OLED handler for display updates.
     * @param messageNumber Identifier for the message being decoded.
     */
    static void decodeMessage(const std::string& payload, RS::ReedSolomon<96, 32>& rs, char* repaired, OLEDHandler& oled, int messageNumber);

    /**
     * @brief Updates the OLED display with decoded message details.
     * @param oled Reference to the OLED handler.
     * @param text The text to display on the OLED.
     * @param rssi The RSSI value associated with the received message.
     */
    static void updateOLED(OLEDHandler& oled, const std::string& text, int rssi);

    /**
     * @brief Converts a byte array into a bit array.
     * @param bytes The byte array to convert.
     * @param bitLength The number of bits to extract from the byte array.
     * @param bits The resulting bit array.
     */
    static void bytesToBits(const std::vector<uint8_t>& bytes, uint16_t bitLength, std::vector<uint8_t>& bits);
};

#endif // UTILS_HPP
