
#include "LoRaHandler.hpp"

/**
 * @brief Constructor for the LoRaHandler class.
 * @details Initializes LoRa settings with provided configuration values.
 */
LoRaHandler::LoRaHandler(int cs, int rst, int dio0, float freq, int sf, int sw, long bw, int cr)
    : csPin(cs), rstPin(rst), dio0Pin(dio0), frequency(freq), spreadingFactor(sf), syncWord(sw), bandwidth(bw), codingRate(cr) {}

/**
 * @brief Initializes the LoRa module.
 * @return true if successful, false otherwise.
 */
bool LoRaHandler::initialize() {
    SPI.begin(); // Start SPI communication
    LoRa.setPins(csPin, rstPin, dio0Pin); // Configure pins for LoRa module

    if (!LoRa.begin(frequency)) {
        Serial.println("LoRa initialization failed!");
        return false;
    }

    // Additional settings for LoRa
    LoRa.setSignalBandwidth(bandwidth);
    LoRa.setSpreadingFactor(spreadingFactor);
    LoRa.setCodingRate4(codingRate);
    LoRa.setSyncWord(syncWord);
    LoRa.disableCrc(); // Απενεργοποίηση CRC (Cyclic Redundancy Check)
    LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN); // Ρύθμιση ισχύος σε 20 dBm (PA_BOOST)

    Serial.println("LoRa initialized successfully!");
    return true;
}

/**
 * @brief Selects the LoRa module for SPI communication.
 */
void LoRaHandler::select() {
    digitalWrite(csPin, LOW); // Pull CS pin LOW
}

/**
 * @brief Deselects the LoRa module for SPI communication.
 */
void LoRaHandler::deselect() {
    digitalWrite(csPin, HIGH); // Pull CS pin HIGH
}

/**
 * @brief Reads a packet received via LoRa.
 * @return A String containing the received data, or an empty String if no packet is received.
 */
String LoRaHandler::receivePacket() {
    int packetSize = LoRa.parsePacket(); // Check for packet
    if (packetSize) {
        return LoRa.readString(); // Return the received data as a String
    }
    return ""; // No data received
}
