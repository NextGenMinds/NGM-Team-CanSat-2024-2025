#ifndef LORAHANDLER_HPP
#define LORAHANDLER_HPP

#include <Arduino.h> // Core Arduino functionality
#include <LoRa.h>    // Library for LoRa communication
#include <SPI.h>     // SPI communication for LoRa module
#include <vector>    // Standard vector for handling byte arrays

/**
 * @class LoRaHandler
 * @brief A handler class for managing LoRa communication.
 * 
 * This class initializes the LoRa module, configures parameters such as
 * frequency, spreading factor, bandwidth, and coding rate, and provides
 * methods to send data packets using plain text or byte encoding.
 */
class LoRaHandler {
private:
    int csPin;             // Chip Select (CS) pin for SPI communication
    int rstPin;            // Reset pin for LoRa module
    int dio0Pin;           // Digital I/O pin for LoRa module
    float frequency;       // Frequency for LoRa communication
    int spreadingFactor;   // Spreading factor for LoRa modulation
    int syncWord;          // Sync word for network separation
    long bandwidth;        // Signal bandwidth in Hz
    int codingRate;        // Coding rate for LoRa (e.g., 4/5)

public:
    /**
     * @brief Constructor for LoRaHandler.
     * 
     * Initializes the handler with pins and settings required for LoRa communication.
     * 
     * @param cs The Chip Select pin for the LoRa module.
     * @param rst The Reset pin for the LoRa module.
     * @param dio0 The Digital I/O pin 0 for the LoRa module.
     * @param freq The operating frequency for the LoRa module (in Hz).
     * @param sf The spreading factor for LoRa modulation.
     * @param sw The synchronization word for LoRa communication.
     * @param bw The Signal bandwidth in Hz
     * @param cr The Coding rate for LoRa (e.g., 4/5)
     */
    LoRaHandler(int cs, int rst, int dio0, float freq, int sf, int sw, long bw, int cr);

    /**
     * @brief Initializes the LoRa module with the configured settings.
     * 
     * Sets up the SPI communication, frequency, spreading factor, and sync word.
     * @return True if initialization succeeds, False otherwise.
     */
    bool initialize();

    /**
     * @brief Selects the LoRa module for SPI communication.
     * 
     * Sets the Chip Select (CS) pin LOW to enable communication with the LoRa module.
     */
    void select();

    /**
     * @brief Deselects the LoRa module for SPI communication.
     * 
     * Sets the Chip Select (CS) pin HIGH to disable communication with the LoRa module.
     */
    void deselect();

    /**
     * @brief Sends a data packet using the `LoRa.print` method.
     * 
     * This method includes a prefix for debugging and sends data as plain text.
     * 
     * @param data Pointer to the data array to be sent.
     * @param size Size of the data array.
     * @return True if the packet is sent successfully.
     */
    bool sendPacketWithPrint(const char* data, size_t size);

    /**
     * @brief Sends a data packet using the `LoRa.write` method.
     * 
     * This method includes a prefix, followed by the bit length, and sends the data as raw bytes.
     * 
     * @param data A vector containing the byte-encoded message to be sent.
     * @param bitLength The length of the data in bits.
     * @return True if the packet is sent successfully.
     */
    bool sendPacketWithWrite(const std::vector<uint8_t>& data, uint16_t bitLength);
};

#endif // LORAHANDLER_HPP
