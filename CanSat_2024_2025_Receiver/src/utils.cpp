#include "utils.hpp"

/**
 * @brief Decodes a Reed-Solomon encoded message.
 * @param payload The encoded payload to decode.
 * @param rs Reed-Solomon encoder/decoder instance.
 * @param repaired Buffer for storing the repaired message.
 * @param oled Reference to the OLED handler for display updates.
 * @param messageNumber Identifier for the message being decoded.
 */
void Utils::decodeMessage(const std::string& payload, RS::ReedSolomon<96, 32>& rs, char* repaired, OLEDHandler& oled, int messageNumber) {
    const int messageSize = 96;
    const int ECC_LENGTH = 32;
    char encodedMessage[messageSize + ECC_LENGTH];

    if (payload.length() != (messageSize + ECC_LENGTH + 2)) {
        Serial.println("Error: Invalid payload size for decoding.");
        //return;
    }

    // Copy the payload into the encoded message buffer
    for (int i = 0; i < messageSize + ECC_LENGTH; i++) {
        encodedMessage[i] = payload[i];
    }

    // Decode the message using Reed-Solomon
    rs.Decode(encodedMessage, repaired);

    // Print the decoded message to the Serial monitor
    Serial.print("Reed-Solomon Decoded Message: ");
    Serial.print(messageNumber);
    Serial.print(", ");
    for (int i = 0; i < messageSize; i++) {
        Serial.print(repaired[i]);
    }
    Serial.println();

    // Update the OLED display with the decoded message
    int rssi = -75; // Example RSSI value
    updateOLED(oled, std::string(repaired, messageSize), rssi);
}

/**
 * @brief Updates the OLED display with decoded message details.
 * @param oled Reference to the OLED handler.
 * @param text The text to display on the OLED.
 * @param rssi The RSSI value associated with the received message.
 */
void Utils::updateOLED(OLEDHandler& oled, const std::string& text, int rssi) {
    oled.clear();
    oled.printText(OLEDHandler::row1, "LORA RECEIVER");
    oled.printText(OLEDHandler::row2, "RSSI: " + String(rssi));
    oled.printText(OLEDHandler::row3, "Received packet:");
    oled.printText(OLEDHandler::row4, text.c_str());
    oled.display();
}

/**
 * @brief Converts a byte array into a bit array.
 * @param bytes The byte array to convert.
 * @param bitLength The number of bits to extract from the byte array.
 * @param bits The resulting bit array.
 */
void Utils::bytesToBits(const std::vector<uint8_t>& bytes, uint16_t bitLength, std::vector<uint8_t>& bits) {
    bits.resize(bitLength);
    for (size_t i = 0; i < bitLength; i++) {
        bits[i] = (bytes[i / 8] >> (7 - (i % 8))) & 0x01; // Extract individual bits
    }
}
