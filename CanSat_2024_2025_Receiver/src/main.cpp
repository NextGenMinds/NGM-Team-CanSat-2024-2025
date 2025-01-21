/**
 * NGM Team CanSat Greece 2024 - 2025
 * TTGO ESP32 LoRa v1 (Correct Pinout https://primalcortex.files.wordpress.com/2017/11/ttgolorapinout_v2.jpg)
   https://primalcortex.wordpress.com/2017/11/24/the-esp32-oled-lora-ttgo-lora32-board-and-connecting-it-to-ttn/
 * GPS NEO 6M 3.3v
 * SD Card module 5v 
 * BMP280 sensor 3.3v
 * For SD Card module follow 
 * https://www.youtube.com/watch?v=hLCFNR3jp8Y
 * For Two I2C devices follow
 * https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
 * Libraries
 * Adafruit SSD1306@^2.5.9
	 Adafruit GFX Library@^1.11.9
	 LoRa@^0.8.0

//////////////////////////// MIT License /////////////////////////////////////////
  Copyright (c) <2024> <NextGenMinds.org>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
///////////////////////////////////////////////////////////////////////////////////
*/

#include <Arduino.h>
#include "config.hpp"
#include "utils.hpp"

/**
 * @brief Setup function executed once at the start of the program.
 *        Initializes serial communication, OLED display, and LoRa module.
 */
void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(115200);
    while (!Serial); // Wait until Serial is ready

    // Initialize the OLED display
    initializeOLED();

    // Initialize the LoRa module
    initializeLoRa();
}

/**
 * @brief Main program loop executed repeatedly after setup.
 *        Handles incoming LoRa data, processes messages, and performs decoding.
 */
void loop() {
    // Read incoming data from the LoRa module
    String LoRaData = lora.receivePacket();

    // Check if any data was received
    if (LoRaData.length() > 0) {
        // Check if the received message starts with "P:!"
        if (LoRaData.startsWith("P:!")) {
            // Extract the payload by removing the "P:!" prefix
            String payload = LoRaData.substring(3);

            // Decode the message using Reed-Solomon and update OLED display
            Utils::decodeMessage(payload.c_str(), rs, repaired, oled, pMessageNumber);

            // Increment the message counter for "P" type messages
            pMessageNumber++;
        }
        // Check if the received message starts with "W:!"
        else if (LoRaData.startsWith("W:!")) {
            // Extract the payload by removing the "W:!" prefix
            String payload = LoRaData.substring(3);

            // Validate the payload length to ensure it includes bit length information
            if (payload.length() < sizeof(uint16_t)) {
                Serial.println("Error: Payload too short for bit length.");
                return; // Exit processing if payload is invalid
            }

            // Extract the bit length from the payload
            uint16_t bitLength;
            memcpy(&bitLength, payload.c_str(), sizeof(uint16_t));

            // Calculate the number of bytes required to store the message
            size_t byteCount = (bitLength + 7) / 8;

            // Extract the byte message from the payload
            std::vector<uint8_t> byteMessage(byteCount);
            memcpy(byteMessage.data(), payload.c_str() + sizeof(uint16_t), byteCount);

            // Convert the byte message into a bit-level representation
            std::vector<uint8_t> bitMessage;
            Utils::bytesToBits(byteMessage, bitLength, bitMessage);

            // Print the received bit message to the Serial monitor for debugging
            Serial.print("Received Bit Message #");
            Serial.print(wMessageNumber);
            Serial.print("# : ");
            for (uint8_t bit : bitMessage) {
                Serial.print(bit);
            }
            Serial.println();

            // Increment the message counter for "W" type messages
            wMessageNumber++;
        }
    }
}
