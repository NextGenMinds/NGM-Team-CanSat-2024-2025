#include <Arduino.h>
#include <TurboCodec.h>

void setup() {
    Serial.begin(115200);
    delay(1000);

    TurboCodec codec;
    std::string inputMessage = "Hello ESP32!";
    Serial.println("Original Message: " + String(inputMessage.c_str()));

    std::string encodedMessage = codec.encode(inputMessage);
    Serial.println("Turbo Encoded Message: " + String(encodedMessage.c_str()));
}

void loop() {
    // Loop left empty
}
