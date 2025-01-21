#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>  // Arduino core library for basic functionality
#include "BMP280Handler.hpp"  // Handler for BMP280 sensor
#include "OLEDHandler.hpp"    // Handler for OLED display
#include "GPSHandler.hpp"     // Handler for GPS module
#include "LoRaHandler.hpp"    // Handler for LoRa communication
#include "SDHandler.hpp"      // Handler for SD card operations
#include "TurboCodec.h"       // Library for Turbo Codes encoding/decoding
#include "Utils.hpp"          // Utility functions
#include <mySD.h>             // Library for SD card functionality
#include <RS-FEC.h>           // Library for Reed-Solomon error correction

// *** BMP280 Sensor Configuration ***
// I2C pins for communication with BMP280
#define BMP_SDA 4  // Serial Data Line (SDA) pin
#define BMP_SCL 15 // Serial Clock Line (SCL) pin
#define BMP_ADDR 0x76 // I2C address for the BMP280 sensor

extern BMP280Handler bmpHandler; // Global instance of the BMP280 handler

// *** GPS Module Configuration ***
// Pins for GPS communication
#define GPS_TX 33      // Transmit pin for GPS
#define GPS_RX 34      // Receive pin for GPS
#define GPS_BAUD 9600  // Baud rate for GPS communication

extern GPSHandler gpsHandler; // Global instance of the GPS handler

// *** LoRa Module Configuration ***
// Pins and settings for LoRa communication
#define LORA_SCK 5         //< SPI Clock Pin
#define LORA_MISO 19       //< SPI Master-In-Slave-Out Pin
#define LORA_MOSI 27       //< SPI Master-Out-Slave-In Pin
#define LORA_CS 18         //< SPI Slave-Select Pin
#define LORA_RST 14        //< LoRa Reset Pin
#define LORA_DIO0 26       //< LoRa Interrupt Pin
#define LORA_BAND 869.50E6 // Operating frequency (869.50 MHz) max power (20 dBm)
#define LORA_SF 8          // Spreading Factor for LoRa modulation (SF10)
#define LORA_SW 0xF8       // Sync word for network separation
#define LORA_BW 250E3      // Signal bandwidth (125 kHz)
#define LORA_CR 5          // Coding rate (4/6)

extern LoRaHandler loraHandler; // Global instance of the LoRa handler

// *** OLED Display Configuration ***
// Pins and settings for OLED display
#define OLED_SDA 4        // SDA pin for OLED
#define OLED_SCL 15       // SCL pin for OLED
#define OLED_RST 16       // Reset pin for OLED
#define OLED_ADDR 0x3C    // I2C address for OLED
#define SCREEN_WIDTH 128  // OLED screen width in pixels
#define SCREEN_HEIGHT 64  // OLED screen height in pixels

extern OLEDHandler oledHandler; // Global instance of the OLED handler

// *** Reed-Solomon Error Correction Configuration ***
// Error correction constants
const uint8_t ECC_LENGTH = 32; // Length of the error correction code
const int messageSize = 96;    // Size of the message in bytes

// Buffers for message and encoded data
extern char message[messageSize];
extern char encoded[messageSize + ECC_LENGTH];
extern RS::ReedSolomon<messageSize, ECC_LENGTH> rs; // Reed-Solomon encoder instance

// *** SD Card Module Configuration ***
// Pins for SD card communication
#define SD_CLK 17   // Clock pin for SD card
#define SD_MISO 13  // Master-In Slave-Out (MISO) pin
#define SD_MOSI 12  // Master-Out Slave-In (MOSI) pin
#define SD_CS 23    // Chip Select (CS) pin for SD card

extern SDHandler sdHandler; // Global instance of the SD handler

// *** Other Variables ***
// Global message counter for tracking transmitted messages
extern int messageNumber;

#endif // CONFIG_HPP
