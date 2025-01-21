#include "LoRaHandler.hpp"

/**
 * @brief Constructor for LoRaHandler.
 * 
 * Initializes the handler with the specified pins and settings for LoRa communication.
 * 
 * @param cs The Chip Select pin for the LoRa module.
 * @param rst The Reset pin for the LoRa module.
 * @param dio0 The Digital I/O pin 0 for the LoRa module.
 * @param freq The operating frequency for the LoRa module (in Hz).
 * @param sf The spreading factor for LoRa modulation.
 * @param sw The synchronization word for LoRa communication.
 */
LoRaHandler::LoRaHandler(int cs, int rst, int dio0, float freq, int sf, int sw, long bw, int cr)
    : csPin(cs), rstPin(rst), dio0Pin(dio0), frequency(freq), spreadingFactor(sf), syncWord(sw), bandwidth(bw), codingRate(cr) {}

/**
 * @brief Initializes the LoRa module.
 * 
 * Configures the SPI communication and sets up the frequency, spreading factor, 
 * and sync word for the LoRa module.
 * 
 * @return True if the initialization succeeds, False otherwise.
 */
bool LoRaHandler::initialize() {
    SPI.begin(); // Start SPI communication
    LoRa.setPins(csPin, rstPin, dio0Pin); // Assign SPI pins for LoRa communication

    select(); // Select the LoRa module for configuration
    bool status = LoRa.begin(frequency); // Initialize LoRa with the configured frequency
    deselect(); // Deselect the LoRa module after configuration

    if (status) {
        LoRa.setSignalBandwidth(bandwidth); // Set bandwidth to 250 kHz
        LoRa.setSpreadingFactor(spreadingFactor); // Set spreading factor to SF7
        LoRa.setCodingRate4(codingRate); // Set coding rate to 4/5
        LoRa.setSyncWord(syncWord); // Set sync word for network separation
        LoRa.disableCrc(); // Απενεργοποίηση CRC (Cyclic Redundancy Check)
        LoRa.setTxPower(20, PA_OUTPUT_PA_BOOST_PIN); // Ρύθμιση ισχύος σε 20 dBm (PA_BOOST)
    }
    
    return status; // Return the initialization status
}

/**
 * @brief Selects the LoRa module for SPI communication.
 * 
 * Sets the Chip Select (CS) pin LOW to enable communication with the LoRa module.
 */
void LoRaHandler::select() {
    digitalWrite(csPin, LOW); // Pull the CS pin LOW
}

/**
 * @brief Deselects the LoRa module for SPI communication.
 * 
 * Sets the Chip Select (CS) pin HIGH to disable communication with the LoRa module.
 */
void LoRaHandler::deselect() {
    digitalWrite(csPin, HIGH); // Pull the CS pin HIGH
}

/**
 * @brief Sends a data packet using the `LoRa.print` method.
 * 
 * This method prefixes the data with a "P:!" marker for debugging 
 * and sends the data as plain text over LoRa.
 * 
 * @param data Pointer to the data array to be sent.
 * @param size Size of the data array.
 * @return True if the packet is sent successfully.
 */
bool LoRaHandler::sendPacketWithPrint(const char* data, size_t size) {
    select(); // Select the LoRa module
    LoRa.beginPacket(); // Begin the LoRa packet

    LoRa.print("P:!"); // Prefix for debugging
    for (size_t i = 0; i < size; i++) {
        LoRa.print(data[i]); // Send data as plain text
    }
    LoRa.println(); // End the data with a newline
    LoRa.endPacket(); // Finalize the packet
    deselect(); // Deselect the LoRa module
    return true; // Return success
}

/**
 * @brief Sends a data packet using the `LoRa.write` method.
 * 
 * This method prefixes the data with a "W:!" marker for debugging, 
 * followed by the bit length, and sends the data as raw bytes over LoRa.
 * 
 * @param data A vector containing the byte-encoded message to be sent.
 * @param bitLength The length of the data in bits.
 * @return True if the packet is sent successfully.
 */
bool LoRaHandler::sendPacketWithWrite(const std::vector<uint8_t>& data, uint16_t bitLength) {
    select(); // Select the LoRa module
    LoRa.beginPacket(); // Begin the LoRa packet

    LoRa.print("W:!"); // Prefix for debugging
    LoRa.write((uint8_t*)&bitLength, sizeof(bitLength)); // Send the bit length as raw data
    LoRa.write(data.data(), data.size()); // Send the raw byte data
    LoRa.println(); // End the data with a newline
    LoRa.endPacket(); // Finalize the packet
    deselect(); // Deselect the LoRa module
    return true; // Return success
}
