#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <string>

// Constants for SHA-256
const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xefa8d3a1, 0x6a2b2b8f, 0x6b9e4a8f, 0x3c6ef372, 0x9a4a9b08, 0x5b7a8d7b, 0x2f88b315, 0x1b73155b,
    0x3a62c6f7, 0x8e9ef5b9, 0xe7e8f5be, 0x5588edb7, 0x325d7de2, 0x78d4420b, 0xf1737c39, 0x4d98e3f2,
    0x28f2e43f, 0x3c85e5db, 0x46f1c2ff, 0x6275f5a4, 0x847fca7f, 0x9dbe3c5f, 0xa8bcf9d9, 0x53fcb0d3,
    0x78d9e1b1, 0x2b7c3136, 0x1a8c648b, 0x03bb07b3, 0x065403b7, 0x1d3d8b19, 0xf6d7e1ed, 0x9c9f8ee0
};

// Function to perform the right rotation
uint32_t right_rotate(uint32_t value, uint32_t bits) {
    return (value >> bits) | (value << (32 - bits));
}

// Function to preprocess the message to fit the SHA-256 block structure
std::vector<uint8_t> preprocess_message(const std::string& input) {
    // Convert the input to binary
    std::vector<uint8_t> message;
    for (char c : input) {
        message.push_back(static_cast<uint8_t>(c));
    }

    size_t original_length = message.size() * 8;
    message.push_back(0x80);

    while (message.size() % 64 != 56) {
        message.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) {
        message.push_back(static_cast<uint8_t>((original_length >> (i * 8)) & 0xFF));
    }

    return message;
}

// Function to process each 512-bit chunk (64 bytes) and update hash values
void process_chunk(const std::vector<uint8_t>& chunk, uint32_t* hash_values) {
    // Prepare message schedule
    std::vector<uint32_t> W(64);
    for (size_t i = 0; i < 16; ++i) {
        W[i] = (static_cast<uint32_t>(chunk[i * 4]) << 24) |
               (static_cast<uint32_t>(chunk[i * 4 + 1]) << 16) |
               (static_cast<uint32_t>(chunk[i * 4 + 2]) << 8) |
               (static_cast<uint32_t>(chunk[i * 4 + 3]));
    }

    for (size_t i = 16; i < 64; ++i) {
        uint32_t s0 = right_rotate(W[i - 15], 7) ^ right_rotate(W[i - 15], 18) ^ (W[i - 15] >> 3);
        uint32_t s1 = right_rotate(W[i - 2], 17) ^ right_rotate(W[i - 2], 19) ^ (W[i - 2] >> 10);
        W[i] = W[i - 16] + s0 + W[i - 7] + s1;
    }

    // Initialize working variables
    uint32_t a = hash_values[0];
    uint32_t b = hash_values[1];
    uint32_t c = hash_values[2];
    uint32_t d = hash_values[3];
    uint32_t e = hash_values[4];
    uint32_t f = hash_values[5];
    uint32_t g = hash_values[6];
    uint32_t h = hash_values[7];

    // Main loop
    for (size_t i = 0; i < 64; ++i) {
        uint32_t S1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
        uint32_t ch = (e & f) ^ (~e & g);
        uint32_t temp1 = h + S1 + ch + k[i] + W[i];
        uint32_t S0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
        uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
        uint32_t temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Update the hash values
    hash_values[0] += a;
    hash_values[1] += b;
    hash_values[2] += c;
    hash_values[3] += d;
    hash_values[4] += e;
    hash_values[5] += f;
    hash_values[6] += g;
    hash_values[7] += h;
}

// Function to convert a hash value to a hexadecimal string
std::string hash_to_string(uint32_t* hash_values) {
    std::stringstream ss;
    for (int i = 0; i < 8; ++i) {
        ss << std::hex << std::setw(8) << std::setfill('0') << hash_values[i];
    }
    return ss.str();
}

// SHA-256 main function
std::string sha256(const std::string& input) {
    // Initial hash values
    uint32_t hash_values[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // Preprocess the message
    std::vector<uint8_t> message = preprocess_message(input);

    // Process each 512-bit chunk
    for (size_t i = 0; i < message.size(); i += 64) {
        std::vector<uint8_t> chunk(message.begin() + i, message.begin() + i + 64);
        process_chunk(chunk, hash_values);
    }

    // Convert hash values to a hex string
    return hash_to_string(hash_values);
}

// Function to read the Book of Mark from the file
std::string read_book_of_mark(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Main function
int main() {
    // Read the Book of Mark from the file
    std::string book_of_mark = read_book_of_mark("book_of_mark.txt");

    // Compute the SHA-256 hash of the Book of Mark
    std::string hash = sha256(book_of_mark);

    // Output the result
    std::cout << "SHA-256 Hash of the Book of Mark: " << hash << std::endl;

    return 0;
}
