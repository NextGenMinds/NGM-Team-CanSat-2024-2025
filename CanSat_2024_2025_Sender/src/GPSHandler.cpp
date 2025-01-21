#include "GPSHandler.hpp"

/**
 * @brief Constructor for GPSHandler.
 * 
 * Initializes the software serial interface with the specified RX and TX pins.
 * 
 * @param rxPin The pin connected to the GPS module's TX pin.
 * @param txPin The pin connected to the GPS module's RX pin.
 * @param baudRate The baud rate for GPS communication.
 */
GPSHandler::GPSHandler(uint8_t rxPin, uint8_t txPin, uint32_t baudRate)
    : gpsSerial(rxPin, txPin) {}

/**
 * @brief Sends a UBX configuration message to the GPS module.
 * 
 * UBX messages allow precise control over the GPS module's settings. 
 * This function also prints the response received from the GPS module for debugging.
 * 
 * @param msg Pointer to the UBX message array.
 * @param len Length of the UBX message array.
 */
void GPSHandler::sendUBX(byte* msg, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        gpsSerial.write(msg[i]); // Send each byte of the message
    }

    delay(500); // Allow time for the GPS module to process the message

    Serial.print("UBX Response: ");
    unsigned long start = millis();
    while (millis() - start < 1000) { // Wait up to 1 second for a response
        if (gpsSerial.available()) {
            byte response = gpsSerial.read(); // Read the response byte
            Serial.print("0x");
            if (response < 0x10) Serial.print("0"); // Add leading zero for single hex digits
            Serial.print(response, HEX);
            Serial.print(" ");
        }
    }
    Serial.println(); // End of response output
}

/**
 * @brief Processes incoming GPS data for a specified duration.
 * 
 * This function continuously reads and parses GPS data from the serial interface.
 * 
 * @param ms Duration to wait for GPS data in milliseconds.
 * @param serial Reference to the software serial interface.
 * @param gps Reference to the TinyGPSPlus instance for parsing data.
 */
void GPSHandler::smartDelay(unsigned long ms, SoftwareSerial& serial, TinyGPSPlus& gps) {
    unsigned long start = millis();
    do {
        while (serial.available()) {
            gps.encode(serial.read()); // Pass each received byte to the GPS parser
        }
    } while (millis() - start < ms);
}

/**
 * @brief Initializes the GPS module.
 * 
 * Sets up the serial communication and sends configuration commands to adjust settings such as the update rate.
 * 
 * @param baudRate The baud rate for GPS communication.
 */
void GPSHandler::initialize(uint32_t baudRate) {
    Serial.println("Initializing GPS...");

    gpsSerial.begin(baudRate); // Start the GPS serial communication
    delay(200); // Allow the GPS module time to initialize

    if (!gpsSerial.available()) {
        Serial.println("GPS Serial Not Available"); // Log if GPS serial is unresponsive
    } else {
        Serial.println("GPS Serial Available"); // Log successful GPS communication
    }

    // Set GPS update rate to 2 Hz
    Serial.println("Setting GPS update rate to 2Hz...");
    sendUBX((byte*)setRateTo2Hz, sizeof(setRateTo2Hz));

    Serial.println("GPS Initialized.");
}

/**
 * @brief Reads and parses GPS data.
 * 
 * Extracts location, time, speed, altitude, and satellite information from the GPS module.
 * 
 * @param latitude Reference to store the latitude.
 * @param longitude Reference to store the longitude.
 * @param day Reference to store the day of the date.
 * @param month Reference to store the month of the date.
 * @param year Reference to store the year of the date.
 * @param hour Reference to store the hour.
 * @param minute Reference to store the minute.
 * @param second Reference to store the second.
 * @param speedKPH Reference to store the speed in km/h.
 * @param course Reference to store the course in degrees.
 * @param altitude Reference to store the altitude in meters.
 * @param satellites Reference to store the number of satellites in view.
 */
void GPSHandler::readGPS(double& latitude, double& longitude, int& day, int& month, int& year,
                         int& hour, int& minute, int& second, double& speedKPH, double& course,
                         double& altitude, uint32_t& satellites) {
    // Process incoming GPS data for 500 milliseconds
    smartDelay(500, gpsSerial, gps);

    // Retrieve data parsed by TinyGPSPlus
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    day = gps.date.day();
    month = gps.date.month();
    year = gps.date.year();
    hour = gps.time.hour();
    minute = gps.time.minute();
    second = gps.time.second();
    speedKPH = gps.speed.kmph();
    course = gps.course.deg();
    altitude = gps.altitude.meters();
    satellites = gps.satellites.value();
}
