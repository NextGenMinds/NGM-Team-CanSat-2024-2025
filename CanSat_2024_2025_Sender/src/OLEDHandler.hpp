#ifndef OLEDHANDLER_HPP
#define OLEDHANDLER_HPP

#include <Adafruit_GFX.h>      // Core graphics library for displays
#include <Adafruit_SSD1306.h> // Library for SSD1306 OLED displays
#include <Wire.h>             // I2C communication library

/**
 * @brief A handler class for interacting with the OLED display.
 * 
 * This class manages initialization, text rendering, and clearing 
 * of the OLED display using I2C communication.
 */
class OLEDHandler {
public:
    /**
     * @brief Constructor for OLEDHandler.
     * 
     * Initializes the handler with pins and settings for the OLED display.
     * 
     * @param sda The SDA (data) pin for I2C communication.
     * @param scl The SCL (clock) pin for I2C communication.
     * @param rstPin The reset pin for the OLED display.
     * @param i2cAddr The I2C address of the OLED display.
     * @param width The width of the display in pixels.
     * @param height The height of the display in pixels.
     */
    OLEDHandler(uint8_t sda, uint8_t scl, int8_t rstPin, uint8_t i2cAddr, uint8_t width, uint8_t height);

    /**
     * @brief Initializes the OLED display.
     * 
     * Sets up I2C communication and prepares the display for rendering.
     * @return True if the initialization succeeds, False otherwise.
     */
    bool begin();

    /**
     * @brief Clears the OLED display.
     * 
     * Removes all content from the screen.
     */
    void clear();

    /**
     * @brief Displays text on a specific row of the OLED.
     * 
     * @param row The vertical position (in pixels) for the text.
     * @param text The text string to display.
     * @param size The font size for the text.
     */
    void printText(uint8_t row, const String& text, uint8_t size = 1);

    /**
     * @brief Renders the current content to the OLED display.
     */
    void display();

    // Row constants for predefined text positions
    static const uint8_t row1 = 0;
    static const uint8_t row2 = 10;
    static const uint8_t row3 = 20;
    static const uint8_t row4 = 30;
    static const uint8_t row5 = 40;
    static const uint8_t row6 = 50;
    static const uint8_t row7 = 60;

private:
    Adafruit_SSD1306 oledDisplay; // Instance of the SSD1306 display driver
    uint8_t sdaPin;               // SDA (data) pin
    uint8_t sclPin;               // SCL (clock) pin
    int8_t rstPin;                // Reset pin
    uint8_t i2cAddr;              // I2C address of the display
};

#endif // OLEDHANDLER_HPP
