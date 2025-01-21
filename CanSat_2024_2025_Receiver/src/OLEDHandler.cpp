#include "OLEDHandler.hpp"
#include <Arduino.h>

/**
 * @brief Constructor for the OLEDHandler class.
 * @details Sets up the initial configuration for the OLED display.
 */
OLEDHandler::OLEDHandler(uint8_t sda, uint8_t scl, int8_t rstPin, uint8_t i2cAddr, uint8_t width, uint8_t height)
    : oledDisplay(width, height, &Wire, rstPin), sdaPin(sda), sclPin(scl), rstPin(rstPin), i2cAddr(i2cAddr) {}

/**
 * @brief Initializes the OLED display.
 * @return true if the initialization is successful, false otherwise.
 */
bool OLEDHandler::begin() {
    Wire.begin(sdaPin, sclPin); // Start I2C communication
    if (!oledDisplay.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }
    oledDisplay.clearDisplay();
    oledDisplay.display();
    return true;
}

/**
 * @brief Clears the OLED display content.
 */
void OLEDHandler::clear() {
    oledDisplay.clearDisplay();
}

/**
 * @brief Prints text to the OLED display at a specified row.
 * @param row The row (Y-coordinate) to display the text.
 * @param text The text to display.
 * @param size Text size (default is 1).
 */
void OLEDHandler::printText(uint8_t row, const String& text, uint8_t size) {
    oledDisplay.setTextSize(size);
    oledDisplay.setTextColor(SSD1306_WHITE);
    oledDisplay.setCursor(0, row);
    oledDisplay.print(text);
}

/**
 * @brief Updates the OLED display to show the current buffer content.
 */
void OLEDHandler::display() {
    oledDisplay.display();
}
