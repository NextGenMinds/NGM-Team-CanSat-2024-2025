#ifndef LORAHANDLER_HPP
#define LORAHANDLER_HPP

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

/**
 * @class LoRaHandler
 * @brief Handles the initialization and communication with the LoRa module.
 */
class LoRaHandler {
private:
    int csPin;            ///< Chip Select (CS) pin
    int rstPin;           ///< Reset pin
    int dio0Pin;          ///< DIO0 interrupt pin
    float frequency;      ///< LoRa communication frequency
    int spreadingFactor;  ///< LoRa spreading factor
    int syncWord;         ///< LoRa synchronization word
    long bandwidth;       ///< Signal bandwidth in Hz
    int codingRate;       ///< Coding rate for LoRa (e.g., 4/5)

public:
    /**
     * @brief Constructor for the LoRaHandler class.
     * @param cs Chip Select (CS) pin for SPI communication.
     * @param rst Reset pin for the LoRa module.
     * @param dio0 DIO0 interrupt pin.
     * @param freq Communication frequency in Hz.
     * @param sf Spreading factor for LoRa communication.
     * @param sw Synchronization word for the LoRa module.
     * @param bw Signal bandwidth in Hz.
     * @param cr Coding rate for LoRa communication.
     */
    LoRaHandler(int cs, int rst, int dio0, float freq, int sf, int sw, long bw, int cr);

    /**
     * @brief Initializes the LoRa module.
     * @return true if initialization is successful, false otherwise.
     */
    bool initialize();

    /**
     * @brief Selects the LoRa module for SPI communication.
     *        Pulls the Chip Select (CS) pin LOW.
     */
    void select();

    /**
     * @brief Deselects the LoRa module for SPI communication.
     *        Pulls the Chip Select (CS) pin HIGH.
     */
    void deselect();

    /**
     * @brief Reads a packet of data received via LoRa.
     * @return A String containing the received data. Returns an empty String if no data is received.
     */
    String receivePacket();
};

#endif // LORAHANDLER_HPP
