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
	 esp32-micro-sdcard@^0.1.1
	 TinyGPSPlus@^1.0.3
	 EspSoftwareSerial@^8.1.0
	 Adafruit BMP280 Library@^2.6.8

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

#include "config.hpp"

/**
 * @brief Setup function executed once at the start of the program.
 */
void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(115200);
    while (!Serial); // Wait until Serial is ready
    Serial.println("Hardware Serial Began");

    // Initialize GPS module with specified baud rate
    gpsHandler.initialize(GPS_BAUD);

    // Initialize OLED display
    if (!oledHandler.begin()) {
        Serial.println("OLED initialization failed");
        while (1); // Halt execution if OLED fails
    }
    oledHandler.printText(OLEDHandler::row1, "Initializing...", 1);
    oledHandler.display();

    // Initialize BMP280 sensor
    bmpHandler.begin();
    oledHandler.printText(OLEDHandler::row2, "BMP280 Ready!", 1);
    oledHandler.display();

    // Start SPI communication and initialize the SD card
    Serial.println("LoRa Sender Test");
    Serial.println("Initializing SD card...");
    if (!sdHandler.initialize()) {
        Serial.println("SD card initialization failed!");
    } else {
        Serial.println("SD card initialized.");
        oledHandler.printText(OLEDHandler::row3, "SD Card OK!", 1);
        oledHandler.display();
        delay(1000);

        // Create a new file on the SD card
        if (sdHandler.createFile("/CS2425.TXT")) {
            Serial.println("CS2425.TXT created successfully.");
            oledHandler.printText(OLEDHandler::row4, "File Created!", 1);
            oledHandler.display();
        } else {
            Serial.println("Error creating CS2425.TXT.");
        }
    }

    // Initialize LoRa communication
    if (!loraHandler.initialize()) {
        Serial.println("LoRa initialization failed!");
    } else {
        Serial.println("LoRa initialized successfully!");
    }

    Serial.println("Setup done!");
}

/**
 * @brief Main program loop executed repeatedly after setup.
 */
void loop() {
    // Read data from the BMP280 sensor (temperature and pressure)
    BMP280Data data = bmpHandler.getData();

    // Variables for GPS data
    double latitude, longitude, altitude;
    int day, month, year, hour, minute, second;
    double speedKPH, course, pressure, temperature;
    uint32_t satellites;

    // Read pressure and temperature from BMP280
    pressure = data.pressure;
    temperature = data.temperature;

    // Read data from the GPS module
    gpsHandler.readGPS(latitude, longitude, day, month, year, hour, minute, second,
                        speedKPH, course, altitude, satellites);

    // Create a formatted string of data
    String dataString = Utils::createDataString(messageNumber, latitude, longitude, day, month, year,
                                                hour, minute, second, speedKPH, course, altitude,
                                                satellites, pressure, temperature);

    // Print the data string for debugging
    Serial.println(dataString);

    // Encode the data string using Reed-Solomon error correction
    Utils::encodeMessage(dataString, message, messageSize, encoded, sizeof(encoded), rs);

    // Print the encoded message for debugging
    // Serial.print("Encoded message (Reed-Solomon): ");
    // Serial.write(encoded, sizeof(encoded));
    // Serial.println();

    // Transmit the encoded message via LoRa
    loraHandler.sendPacketWithPrint(encoded, sizeof(encoded));
    Serial.println("Reed-Solomon Message Sent.");

    // Encode the data using Turbo Codes
    TurboCodec codec;
    std::string encodedMessage = codec.encode(dataString.c_str());

    // Print the Turbo Codes encoded message
    Serial.print("Turbo Codes Encoded Message: ");
    Serial.println(encodedMessage.c_str());

    // Convert the Turbo Codes message into a byte format for LoRa transmission
    std::vector<uint8_t> byteMessage;
    std::vector<uint8_t> bitVectorEncodedMessage;
    uint16_t bitLength;

    Utils::vectorToBits(encodedMessage, bitVectorEncodedMessage);
    Utils::bitsToBytes(bitVectorEncodedMessage, byteMessage, bitLength);

    // Print the byte array for verification
    // Serial.print("Byte Message: ");
    // for (uint8_t byte : byteMessage) {
    //     Serial.print(byte, BIN);
    //     Serial.print(" ");
    // }
    // Serial.println();

    // Send the byte-encoded message via LoRa
    // Serial.print("Sending message with Bit Length: ");
    // Serial.println(bitLength);

    loraHandler.sendPacketWithWrite(byteMessage, bitLength);
    // Serial.println("Turbo Codes Message Sent.");

    // Save the raw data string to the SD card
    if (!sdHandler.writeFile("/CS2425.TXT", dataString)) {
        Serial.println("Error writing to CS2425.TXT.");
    }

    // Update OLED display with the latest readings
    Utils::updateOLED(oledHandler, latitude, longitude, altitude, temperature, pressure);

    // Increment the message counter for the next loop
    messageNumber++;
}
