#include "Utils.hpp"

/**
 * @brief Creates a formatted data string from telemetry and sensor data.
 * 
 * Combines all input parameters into a single, comma-separated string for transmission or storage.
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
String Utils::createDataString(int messageNumber, double latitude, double longitude, int day,
                               int month, int year, int hour, int minute, int second,
                               double speedKPH, double course, double altitude,
                               uint32_t satellites, double pressure, double temperature) {
    return String(messageNumber) + "," +
           String(latitude, 6) + "," +
           String(longitude, 6) + "," +
           String(day) + "/" + String(month) + "/" + String(year) + "," +
           String(hour) + ":" + String(minute) + ":" + String(second) + "," +
           String(speedKPH) + "," +
           String(course) + "," +
           String(altitude) + "," +
           String(satellites) + "," +
           String(pressure) + "," +
           String(temperature);
}

/**
 * @brief Encodes a message using Reed-Solomon error correction.
 * 
 * Pads the message with zeros to the required size and encodes it for reliable communication.
 * 
 * @param dataString The input data string to encode.
 * @param message Buffer to store the padded message.
 * @param messageSize Size of the message buffer.
 * @param encoded Buffer to store the encoded data.
 * @param encodedSize Size of the encoded buffer.
 * @param rs Reference to the Reed-Solomon encoder.
 */
void Utils::encodeMessage(const String& dataString, char* message, size_t messageSize,
                          char* encoded, size_t encodedSize, RS::ReedSolomon<96, 32>& rs) {
    memset(message, 0, messageSize); // Clear the message buffer

    size_t dataStringLength = dataString.length(); // Get the length of the data string
    for (size_t i = 0; i < dataStringLength && i < messageSize; i++) {
        message[i] = dataString[i]; // Copy data into the buffer
    }

    for (size_t i = dataStringLength; i < messageSize; i++) {
        message[i] = '0'; // Pad with zeros if needed
    }
    message[dataStringLength] = ','; // Add a separator at the end

    rs.Encode(message, encoded); // Perform Reed-Solomon encoding
}

/**
 * @brief Updates the OLED display with telemetry data.
 * 
 * Displays the latest readings of latitude, longitude, altitude, temperature, and pressure.
 * 
 * @param oledHandler Reference to the OLEDHandler instance.
 * @param latitude Latitude in degrees.
 * @param longitude Longitude in degrees.
 * @param altitude Altitude in meters.
 * @param temperature Temperature in Celsius.
 * @param pressure Atmospheric pressure in hPa.
 */
void Utils::updateOLED(OLEDHandler& oledHandler, double latitude, double longitude,
                       double altitude, double temperature, double pressure) {
    oledHandler.clear(); // Clear the OLED display
    oledHandler.printText(OLEDHandler::row1, "LoRa Sender", 1); // Display title
    oledHandler.printText(OLEDHandler::row2, "Lat: " + String(latitude, 6), 1); // Latitude
    oledHandler.printText(OLEDHandler::row3, "Lng: " + String(longitude, 6), 1); // Longitude
    oledHandler.printText(OLEDHandler::row4, "Alt: " + String(altitude) + " m", 1); // Altitude
    oledHandler.printText(OLEDHandler::row5, "Temp: " + String(temperature) + " C", 1); // Temperature
    oledHandler.printText(OLEDHandler::row6, "Press: " + String(pressure) + " hPa", 1); // Pressure
    oledHandler.display(); // Render the updated display
}

/**
 * @brief Converts a binary string into a vector of bits.
 * 
 * @param input The input binary string.
 * @param bitInput Vector to store the resulting bits.
 */
void Utils::vectorToBits(const std::string& input, std::vector<uint8_t>& bitInput) {
    for (char c : input) {
        bitInput.push_back(c == '1' ? 1 : 0); // Convert '1' to 1 and '0' to 0
    }
}

/**
 * @brief Converts a vector of bits into a vector of bytes.
 * 
 * @param bits The input vector of bits.
 * @param bytes Vector to store the resulting bytes.
 * @param bitLength The length of the bit stream.
 */
void Utils::bitsToBytes(const std::vector<uint8_t>& bits, std::vector<uint8_t>& bytes, uint16_t& bitLength) {
    bitLength = bits.size(); // Record the total bit length
    size_t byteCount = (bitLength + 7) / 8; // Calculate the number of bytes needed
    bytes.resize(byteCount, 0); // Resize the output byte vector

    for (size_t i = 0; i < bitLength; i++) {
        if (bits[i]) {
            bytes[i / 8] |= (1 << (7 - (i % 8))); // Set the corresponding bit in the byte
        }
    }
}
