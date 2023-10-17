#include <iostream>
#include <bitset>
#include <vector>

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

std::bitset<7> calculateLRC(const std::bitset<7>& data) {
    std::bitset<7> lrc = 0;
    for (size_t i = 0; i < 7; ++i) {
        lrc ^= data[i];
    }
    return lrc;
}

uint8_t calculateXORChecksum(const std::vector<uint8_t>& data) {
    uint8_t checksum = 0;

    for (const uint8_t& byte : data) {
        checksum ^= byte;
    }

    return checksum;
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

    std::bitset<7> data3 = 0b1101101;  // Example data word

    std::bitset<7> lrc = calculateLRC(data3);

    std::cout << "Data: " << data3 << std::endl;
    std::cout << "LRC: " << lrc << std::endl;

// Sample data to calculate checksum
    std::vector<uint8_t> data4 = {0x55, 0xAA, 0x12, 0x34, 0x78};

    // Calculate the checksum
    uint8_t checksum = calculateXORChecksum(data4);

    // Display the data and checksum
    std::cout << "Data: ";
    for (const uint8_t& byte : data4) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << "\nChecksum: 0x" << std::hex << static_cast<int>(checksum) << std::endl;


    // Introduce an error by changing a byte
    data4[2] = 0x11; // Change 0x12 to 0x11

// Recalculate the checksum
    checksum = calculateXORChecksum(data4);

    std::cout << "Data with error: ";
    for (const uint8_t& byte : data4) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }
    std::cout << "\nChecksum with error: 0x" << std::hex << static_cast<int>(checksum) << std::endl;

    return 0;
}
