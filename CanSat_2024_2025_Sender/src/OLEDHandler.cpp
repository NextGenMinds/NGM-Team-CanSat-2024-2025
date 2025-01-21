#include "OLEDHandler.hpp"
#include <Arduino.h> // Core Arduino functionality

/**
 * @brief Constructor for OLEDHandler.
 * 
 * Initializes the handler with the specified pins and settings.
 * 
 * @param sda The SDA pin for I2C communication.
 * @param scl The SCL pin for I2C communication.
 * @param rstPin The reset pin for the OLED display.
 * @param i2cAddr The I2C address of the OLED display.
 * @param width The width of the display in pixels.
 * @param height The height of the display in pixels.
 */
OLEDHandler::OLEDHandler(uint8_t sda, uint8_t scl, int8_t rstPin, uint8_t i2cAddr, uint8_t width, uint8_t height)
    : oledDisplay(width, height, &Wire, rstPin), sdaPin(sda), sclPin(scl), rstPin(rstPin), i2cAddr(i2cAddr) {}

/**
 * @brief Initializes the OLED display.
 * 
 * Configures the I2C communication and checks for successful initialization.
 * @return True if initialization succeeds, False otherwise.
 */
bool OLEDHandler::begin() {
    Wire.begin(sdaPin, sclPin); // Start I2C communication
    if (!oledDisplay.begin(SSD1306_SWITCHCAPVCC, i2cAddr)) { // Initialize the OLED
        Serial.println(F("SSD1306 allocation failed"));
        return false; // Return failure if initialization fails
    }
    oledDisplay.clearDisplay(); // Clear the display on start
    oledDisplay.display(); // Render the cleared display
    return true; // Return success
}

/**
 * @brief Clears the OLED display.
 * 
 * Erases all content on the screen.
 */
void OLEDHandler::clear() {
    oledDisplay.clearDisplay(); // Clear the buffer
}

/**
 * @brief Displays text on a specific row of the OLED display.
 * 
 * @param row The vertical position (in pixels) for the text.
 * @param text The text string to display.
 * @param size The font size for the text.
 */
void OLEDHandler::printText(uint8_t row, const String& text, uint8_t size) {
    oledDisplay.setTextSize(size); // Set text size
    oledDisplay.setTextColor(SSD1306_WHITE); // Set text color to white
    oledDisplay.setCursor(0, row); // Set the cursor position
    oledDisplay.print(text); // Print the text to the buffer
}

/**
 * @brief Renders the current content to the OLED display.
 */
void OLEDHandler::display() {
    oledDisplay.display(); // Render the buffer to the screen
}
