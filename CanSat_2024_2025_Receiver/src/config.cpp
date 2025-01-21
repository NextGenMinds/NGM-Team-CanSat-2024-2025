#include "config.hpp"

// Instantiate OLED and LoRa handlers with appropriate settings
OLEDHandler oled(OLED_SDA, OLED_SCL, OLED_RST, OLED_ADDR, SCREEN_WIDTH, SCREEN_HEIGHT);
LoRaHandler lora(LORA_CS, LORA_RST, LORA_DIO0, LORA_BAND, LORA_SF, LORA_SW, LORA_BW, LORA_CR);

// Reed-Solomon configuration
const uint8_t ECC_LENGTH = 32; ///< Length of the error correction code
const int messageSize = 96;    ///< Size of the message for Reed-Solomon
char repaired[messageSize];    ///< Buffer to store the repaired message
RS::ReedSolomon<96, 32> rs;    ///< Instance of the Reed-Solomon encoder/decoder

// Message counters
int pMessageNumber = 0; ///< Counter for "P" messages
int wMessageNumber = 0; ///< Counter for "W" messages

/**
 * @brief Initializes the OLED display.
 *        Verifies the OLED functionality and displays initial messages.
 */
void initializeOLED() {
    if (!oled.begin()) {
        Serial.println(F("OLED initialization failed"));
        while (1); // Halt program if initialization fails
    }
    oled.printText(OLEDHandler::row1, "LORA RECEIVER");
    oled.display();
}

/**
 * @brief Initializes the LoRa module.
 *        Configures the LoRa module and verifies its connection.
 */
void initializeLoRa() {
    if (!lora.initialize()) {
        Serial.println("LoRa initialization failed!");
        while (1); // Halt program if initialization fails
    }
    oled.printText(OLEDHandler::row2, "LoRa Initialized");
    oled.display();
}
