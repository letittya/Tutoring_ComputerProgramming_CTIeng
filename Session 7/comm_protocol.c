/*
You are designing a communication protocol that fits into a single uint32_t. The 32 bits are structured as follows:
[Header: 8 bits] [Payload: 20 bits] [Checksum: 4 bits]
[31..........24] [23.............4] [3...........0]

1. Header: Fixed value 0xAA.
2. Payload: Stores 5 distinct values (4 bits each).
3. Checksum: The XOR sum of the 5 payload values.

Tasks:
  1. Implement: uint32_t createPacket(unsigned int values[], int n);
  - Take the first 5 elements from the 'values' array.
  - If n < 5, pad the remaining slots with 0.
  - Ensure only the lowest 4 bits of each input value are used (mask with 0xF).
  - Calculate the Checksum (XOR of the 5 packed values).
  - Construct and return the final 32-bit packet with Header 0xAA.

  2. Implement: int validatePacket(uint32_t packet);
  - Return 1 if the packet is valid, 0 otherwise.
  - A packet is valid IF AND ONLY IF:
  a) The Header (top 8 bits) is exactly 0xAA.
  b) The stored Checksum (bottom 4 bits) matches the XOR sum of the 5 values extracted from the Payload.

  Example:
  Input: {1, 2, 1, 2, 1}
  Header:   0xAA
  Payload:  0x12121 (Nibbles: 1, 2, 1, 2, 1)
  Checksum: 1 ^ 2 ^ 1 ^ 2 ^ 1 = 1
  Result:   0xAA121211
*/

#include <stdio.h>
#include <stdint.h>

uint32_t set_nibble(uint32_t n, unsigned int nibble, int pos) {
    return n | ((nibble) << (pos * 4));
}

uint32_t get_nibble(uint32_t n, unsigned int pos)
{
    return (n >> (pos * 4)) & 0xF;
}

uint32_t createPacket(unsigned int values[], int n) {
    uint32_t packet = 0;
    unsigned int checksum = 0;
    
    // set the Header (0xAA) in the front -> 0xAA is 10101010
    packet = set_nibble(packet, 0xA, 7);
    packet = set_nibble(packet, 0xA, 6);

    // payload occupies bits 4 to 23
    // values[0] is at the highest payload spot (bits 20-23) and values[4] at the lowest payload spot (bits 4-7)
    
    for (int i = 0; i < 5; i++) {
        unsigned int val = 0;
        // handle case where input array is shorter than 5
        if (i < n) {
            val = values[i] & 0xF; // ensure we only take 4 bits
        }
        
        // update checksum
        checksum = checksum ^ val;
        // place val
        packet = set_nibble(packet, val, 5 - i);
    }

    // set the Checksum (bits 0-3)
    packet = set_nibble(packet, checksum, 0);
    return packet;
}

int validatePacket(uint32_t packet) {
    // validate header
    unsigned int headerHigh = get_nibble(packet, 7);
    unsigned int headerLow  = get_nibble(packet, 6);
    if( headerHigh!=0xA || headerLow !=0xA)
        return 0;

    // validate Checksum
    // extract checksum -> last nibble
    unsigned int storedChecksum = get_nibble(packet, 0);
    unsigned int calculatedChecksum = 0;

    // loop through the 5 payload slots to recalculate XOR sum
    for (int i = 0; i < 5; i++) {
        unsigned int val = get_nibble(packet, 5 - i);
        
        calculatedChecksum =  calculatedChecksum^val;
    }

    if (storedChecksum == calculatedChecksum) return 1;
    else return 0;
}

int main() {
    unsigned int data[] = {1, 2, 1};
    uint32_t packet = createPacket(data, 3);
    
    printf("Generated Packet: 0x%X\n", packet); 
    
    if (validatePacket(packet)) {
        printf("Packet 1 is VALID.\n");
    } else {
        printf("Packet 1 is INVALID.\n");
    }

    // change change the last nibble (checksum) from 1 to F
    uint32_t corrupted = (packet & 0xFFFFFFF0) | 0xF; 
    
    printf("\nCorrupted Packet: 0x%X\n", corrupted);
    
    if (validatePacket(corrupted)) {
        printf("Packet 2 is VALID.\n");
    } else {
        printf("Packet 2 is INVALID (Checksum mismatch).\n");
    }

    return 0;
}
