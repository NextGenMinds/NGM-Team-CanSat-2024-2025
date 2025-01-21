#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <vector>
#include <string>
#include <RS-FEC.h>
#include "OLEDHandler.hpp"
#include "LoRaHandler.hpp"

// Pin definitions and settings for LoRa communication
#define LORA_SCK 5         //< SPI Clock Pin
#define LORA_MISO 19       //< SPI Master-In-Slave-Out Pin
#define LORA_MOSI 27       //< SPI Master-Out-Slave-In Pin
#define LORA_CS 18         //< SPI Slave-Select Pin
#define LORA_RST 14        //< LoRa Reset Pin
#define LORA_DIO0 26       //< LoRa Interrupt Pin
#define LORA_BAND 869.50E6 // Operating frequency (869.50 MHz) max power (27 dBm / 500 mW)
#define LORA_SF 8          // Spreading Factor for LoRa modulation (SF10)
#define LORA_SW 0xF8       // Sync word for network separation
#define LORA_BW 250E3      // Signal bandwidth (125 kHz)
#define LORA_CR 5          // Coding rate (4/6)

// Pin definitions and settings for OLED display
#define OLED_SDA 4       ///< OLED SDA Pin
#define OLED_SCL 15      ///< OLED SCL Pin
#define OLED_RST 16      ///< OLED Reset Pin
#define OLED_ADDR 0x3C   ///< OLED I2C Address
#define SCREEN_WIDTH 128 ///< OLED screen width in pixels
#define SCREEN_HEIGHT 64 ///< OLED screen height in pixels

// External object declarations
extern OLEDHandler oled; ///< Instance of the OLED handler
extern LoRaHandler lora; ///< Instance of the LoRa handler

// Reed-Solomon settings
extern const uint8_t ECC_LENGTH; ///< Error correction code length
extern const int messageSize;    ///< Size of the Reed-Solomon message
extern char repaired[];          ///< Buffer for repaired message data
extern RS::ReedSolomon<96, 32> rs; ///< Instance of Reed-Solomon encoder/decoder

// Counters for message numbering
extern int pMessageNumber; ///< Counter for "P" type messages
extern int wMessageNumber; ///< Counter for "W" type messages

/**
 * @brief Initializes the OLED display.
 *        Configures and verifies the connection to the OLED.
 */
void initializeOLED();

/**
 * @brief Initializes the LoRa module.
 *        Configures and verifies the connection to the LoRa module.
 */
void initializeLoRa();

#endif // CONFIG_HPP
