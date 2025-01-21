#ifndef OLEDHANDLER_HPP
#define OLEDHANDLER_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

/**
 * @class OLEDHandler
 * @brief Handles initialization and interaction with the OLED display.
 */
class OLEDHandler {
public:
    /**
     * @brief Constructor for the OLEDHandler class.
     * @param sda SDA pin for I2C communication.
     * @param scl SCL pin for I2C communication.
     * @param rstPin Reset pin for the OLED display.
     * @param i2cAddr I2C address of the OLED display.
     * @param width Width of the OLED display in pixels.
     * @param height Height of the OLED display in pixels.
     */
    OLEDHandler(uint8_t sda, uint8_t scl, int8_t rstPin, uint8_t i2cAddr, uint8_t width, uint8_t height);

    /**
     * @brief Initializes the OLED display.
     * @return true if the initialization is successful, false otherwise.
     */
    bool begin();

    /**
     * @brief Clears the OLED display content.
     */
    void clear();

    /**
     * @brief Prints text to the OLED display at a specified row.
     * @param row The row (Y-coordinate) to display the text.
     * @param text The text to display.
     * @param size Text size (default is 1).
     */
    void printText(uint8_t row, const String& text, uint8_t size = 1);

    /**
     * @brief Updates the OLED display to show the current buffer content.
     */
    void display();

    // Constants for predefined rows
    static const uint8_t row1 = 0;
    static const uint8_t row2 = 10;
    static const uint8_t row3 = 20;
    static const uint8_t row4 = 30;
    static const uint8_t row5 = 40;
    static const uint8_t row6 = 50;
    static const uint8_t row7 = 60;

private:
    Adafruit_SSD1306 oledDisplay; ///< Instance of the OLED display
    uint8_t sdaPin;               ///< SDA pin for I2C communication
    uint8_t sclPin;               ///< SCL pin for I2C communication
    int8_t rstPin;                ///< Reset pin for the OLED display
    uint8_t i2cAddr;              ///< I2C address of the OLED display
};

#endif // OLEDHANDLER_HPP
