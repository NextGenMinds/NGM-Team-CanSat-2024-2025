#include "config.hpp"

// *** Global Instances of Handlers ***

// Instance of BMP280Handler to manage the BMP280 sensor
BMP280Handler bmpHandler(BMP_SDA, BMP_SCL, BMP_ADDR);

// Instance of GPSHandler to manage the GPS module
GPSHandler gpsHandler(GPS_RX, GPS_TX, GPS_BAUD);

// Instantiate LoRa handler with updated frequency, SF7, 250 kHz bandwidth, and coding rate 4/5
LoRaHandler loraHandler(LORA_CS, LORA_RST, LORA_DIO0, LORA_BAND, LORA_SF, LORA_SW, LORA_BW, LORA_CR);

// Instance of OLEDHandler to manage the OLED display
OLEDHandler oledHandler(OLED_SDA, OLED_SCL, OLED_RST, OLED_ADDR, SCREEN_WIDTH, SCREEN_HEIGHT);

// Instance of SDHandler to manage the SD card
SDHandler sdHandler(SD_CS, SD_MOSI, SD_MISO, SD_CLK);

// *** Buffers for Encoding and Message Storage ***

// Message buffer used to store raw data before encoding
char message[messageSize];

// Encoded message buffer to store the output of Reed-Solomon encoding
char encoded[messageSize + ECC_LENGTH];

// Reed-Solomon encoder instance with specified message size and error correction length
RS::ReedSolomon<messageSize, ECC_LENGTH> rs;

// *** Global Variables ***

// Counter to keep track of the number of messages sent
int messageNumber = 0;
