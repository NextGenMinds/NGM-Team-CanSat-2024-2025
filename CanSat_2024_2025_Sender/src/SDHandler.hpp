#ifndef SDHANDLER_HPP
#define SDHANDLER_HPP

#include <Arduino.h> // Core Arduino functionality
#include <mySD.h>    // Library for SD card functionality

/**
 * @brief A handler class for interacting with the SD card module.
 * 
 * This class manages initialization, file creation, and data writing 
 * to an SD card using SPI communication.
 */
class SDHandler {
private:
    int csPin;   // Chip Select (CS) pin
    int mosiPin; // Master-Out Slave-In (MOSI) pin
    int misoPin; // Master-In Slave-Out (MISO) pin
    int clkPin;  // Clock (CLK) pin

public:
    /**
     * @brief Constructor for SDHandler.
     * 
     * Initializes the handler with the specified SPI pins.
     * 
     * @param cs The Chip Select pin for the SD card.
     * @param mosi The MOSI pin for SPI communication.
     * @param miso The MISO pin for SPI communication.
     * @param clk The Clock pin for SPI communication.
     */
    SDHandler(int cs, int mosi, int miso, int clk);

    /**
     * @brief Initializes the SD card module.
     * 
     * Sets up SPI communication and prepares the SD card for use.
     * @return True if initialization succeeds, False otherwise.
     */
    bool initialize();

    /**
     * @brief Writes data to a file on the SD card.
     * 
     * Appends the specified data to the file.
     * 
     * @param filename The name of the file to write to.
     * @param data The data to write to the file.
     * @return True if the data is written successfully, False otherwise.
     */
    bool writeFile(const char* filename, const String& data);

    /**
     * @brief Creates a new file on the SD card.
     * 
     * Opens or creates a file with the specified name.
     * 
     * @param filename The name of the file to create.
     * @return True if the file is created successfully, False otherwise.
     */
    bool createFile(const char* filename);

    /**
     * @brief Selects the SD card for SPI communication.
     * 
     * Sets the Chip Select (CS) pin LOW to enable communication with the SD card.
     */
    void select();

    /**
     * @brief Deselects the SD card for SPI communication.
     * 
     * Sets the Chip Select (CS) pin HIGH to disable communication with the SD card.
     */
    void deselect();
};

#endif // SDHANDLER_HPP
