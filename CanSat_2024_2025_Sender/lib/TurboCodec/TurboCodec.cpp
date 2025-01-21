#include "TurboCodec.h"
#include <algorithm>
#include <random>

// ConvolutionalCode Implementation
ConvolutionalCode::ConvolutionalCode(uint32_t gen) : state(0), generator(gen) {}

void ConvolutionalCode::reset() {
    state = 0;
}

uint8_t ConvolutionalCode::computeParity(uint8_t input) {
    uint32_t temp = (state << 1) | input;
    uint8_t parity = 0;

    for (uint8_t i = 0; i <= MEMORY; i++) {
        if ((temp & (generator << i)) != 0) {
            parity ^= 1;
        }
    }
    state = temp & ((1 << MEMORY) - 1); // Update state
    return parity;
}

// TurboCodec Implementation
TurboCodec::TurboCodec() {}

std::vector<size_t> TurboCodec::generateInterleaver(size_t length) {
    std::vector<size_t> interleaver(length);
    for (size_t i = 0; i < length; ++i) {
        interleaver[i] = i;
    }

    // Use Mersenne Twister with fixed seed 42 for reproducibility
    std::mt19937 generator(42);
    std::shuffle(interleaver.begin(), interleaver.end(), generator);

    return interleaver;
}

std::vector<uint8_t> TurboCodec::stringToBinary(const std::string &input) {
    std::vector<uint8_t> binary;
    for (char c : input) {
        for (int i = 7; i >= 0; --i) {
            binary.push_back((c >> i) & 1);
        }
    }
    return binary;
}

std::string TurboCodec::binaryToString(const std::vector<uint8_t> &binary) {
    std::string output;
    for (size_t i = 0; i < binary.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; ++j) {
            c = (c << 1) | binary[i + j];
        }
        output += c;
    }
    return output;
}

std::string TurboCodec::encode(const std::string &input) {
    // Convert input string to binary
    auto binaryInput = stringToBinary(input);

    // Generate interleaver
    auto interleaver = generateInterleaver(binaryInput.size());

    // Initialize encoders
    ConvolutionalCode encoder1(0b1011); // Generator polynomial 1
    ConvolutionalCode encoder2(0b1111); // Generator polynomial 2

    encoder1.reset();
    encoder2.reset();

    // Encode with the first encoder
    std::vector<uint8_t> parity1(binaryInput.size());
    for (size_t i = 0; i < binaryInput.size(); ++i) {
        parity1[i] = encoder1.computeParity(binaryInput[i]);
    }

    // Interleave the input for the second encoder
    std::vector<uint8_t> permutedInput(binaryInput.size());
    for (size_t i = 0; i < binaryInput.size(); ++i) {
        permutedInput[i] = binaryInput[interleaver[i]];
    }

    // Encode with the second encoder
    std::vector<uint8_t> parity2(binaryInput.size());
    for (size_t i = 0; i < permutedInput.size(); ++i) {
        parity2[i] = encoder2.computeParity(permutedInput[i]);
    }

    // Combine systematic, parity1, and parity2 bits into the final encoded output
    std::string encodedOutput;
    for (size_t i = 0; i < binaryInput.size(); ++i) {
        encodedOutput += (binaryInput[i] ? '1' : '0');
        encodedOutput += (parity1[i] ? '1' : '0');
        encodedOutput += (parity2[i] ? '1' : '0');
    }

    return encodedOutput;
}
