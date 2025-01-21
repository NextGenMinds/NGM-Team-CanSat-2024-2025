#include "SDHandler.hpp"

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
SDHandler::SDHandler(int cs, int mosi, int miso, int clk)
    : csPin(cs), mosiPin(mosi), misoPin(miso), clkPin(clk) {
    pinMode(csPin, OUTPUT); // Set CS pin as output
    deselect(); // Set CS pin HIGH initially
}

/**
 * @brief Initializes the SD card module.
 * 
 * Configures SPI communication and checks for a valid SD card connection.
 * @return True if initialization succeeds, False otherwise.
 */
bool SDHandler::initialize() {
    select(); // Enable communication with SD card
    bool status = SD.begin(csPin, mosiPin, misoPin, clkPin); // Initialize SD card
    deselect(); // Disable communication
    return status; // Return status of initialization
}

/**
 * @brief Writes data to a file on the SD card.
 * 
 * Appends the specified data to the file.
 * 
 * @param filename The name of the file to write to.
 * @param data The data to write to the file.
 * @return True if the data is written successfully, False otherwise.
 */
bool SDHandler::writeFile(const char* filename, const String& data) {
    select(); // Enable communication
    File file = SD.open(filename, FILE_WRITE); // Open file in write mode
    if (file) {
        file.println(data); // Write data to the file
        file.flush(); // Ensure data is written
        file.close(); // Close the file
        deselect(); // Disable communication
        return true; // Success
    } else {
        deselect(); // Disable communication
        return false; // Failure
    }
}

/**
 * @brief Creates a new file on the SD card.
 * 
 * Opens or creates a file with the specified name.
 * 
 * @param filename The name of the file to create.
 * @return True if the file is created successfully, False otherwise.
 */
bool SDHandler::createFile(const char* filename) {
    select(); // Enable communication
    File file = SD.open(filename, FILE_WRITE); // Open or create file
    if (file) {
        file.flush(); // Ensure file is ready
        file.close(); // Close the file
        deselect(); // Disable communication
        return true; // Success
    } else {
        deselect(); // Disable communication
        return false; // Failure
    }
}

/**
 * @brief Selects the SD card for SPI communication.
 */
void SDHandler::select() {
    digitalWrite(csPin, LOW); // Pull the CS pin LOW
}

/**
 * @brief Deselects the SD card for SPI communication.
 */
void SDHandler::deselect() {
    digitalWrite(csPin, HIGH); // Pull the CS pin HIGH
}
