#include <iostream>
#include <bitset>

// Function to calculate even parity bit for a given data word
bool calculateEvenParity(const std::bitset<7>& data) {
    bool parityBit = false;
    for (size_t i = 0; i < 7; ++i) {
        if (data.test(i)) {
            parityBit = !parityBit;
        }
    }
    return parityBit;
}

// Function to calculate odd parity bit for a given data word
bool calculateOddParity(const std::bitset<7>& data) {
    bool parityBit = true;
    for (size_t i = 0; i < 7; ++i) {
        if (data.test(i)) {
            parityBit = !parityBit;
        }
    }
    return parityBit;
}

std::bitset<16> performCRC(const std::bitset<7>& data, const std::bitset<8>& polynomial) {
    std::bitset<16> encodedData = data.to_ulong();  // Convert the 7-bit data to a 16-bit value
    for (size_t i = 0; i < 7; ++i) {
        if (encodedData[15]) {
            encodedData ^= (polynomial.to_ulong() << (15 - 7));
        }
        encodedData <<= 1;
    }
    return encodedData;
}

int main() {
    std::bitset<7> data = 0b1101101;  // Example data word

    bool evenParity = calculateEvenParity(data);
    bool oddParity = calculateOddParity(data);

    std::cout << "Data: " << data << std::endl;
    std::cout << "Even Parity Bit: " << evenParity << std::endl;
    std::cout << "Odd Parity Bit: " << oddParity << std::endl;

    std::bitset<7> data2 = 0b1101101;           // Example data word
    std::bitset<8> polynomial = 0b100000111;   // Example CRC polynomial (CRC-8)

    std::bitset<16> encodedData = performCRC(data, polynomial);

    std::cout << "Data: " << data2 << std::endl;
    std::cout << "CRC Polynomial: " << polynomial << std::endl;
    std::cout << "Encoded Data (with CRC): " << encodedData << std::endl;

    return 0;
}
