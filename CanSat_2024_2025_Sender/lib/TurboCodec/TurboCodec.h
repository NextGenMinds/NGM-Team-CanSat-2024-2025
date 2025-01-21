#ifndef TURBO_CODEC_H
#define TURBO_CODEC_H

#include <vector>
#include <string>
#include <stdint.h>

// ConvolutionalCode class
class ConvolutionalCode {
private:
    uint32_t state;                  // Current state of the encoder
    uint32_t generator;              // Generator parameter
    static constexpr uint32_t MEMORY = 3; // Memory of the encoder

public:
    ConvolutionalCode(uint32_t gen); // Constructor with generator polynomial
    void reset();                    // Reset encoder state
    uint8_t computeParity(uint8_t input); // Compute parity bit for the input
};

// TurboCodec class
class TurboCodec {
public:
    TurboCodec();                    // Constructor for the TurboCodec
    std::string encode(const std::string &input); // Turbo encoding for a string

private:
    std::vector<size_t> generateInterleaver(size_t length); // Generate interleaver
    std::vector<uint8_t> stringToBinary(const std::string &input); // Convert string to binary
    std::string binaryToString(const std::vector<uint8_t> &binary); // Convert binary to string
};

#endif // TURBO_CODEC_H
