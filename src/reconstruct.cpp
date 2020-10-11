#include <base64.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <sstream>
#include <string>

constexpr uint32_t num_shards = 6;

std::string sha256(const std::string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (unsigned char h : hash) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)h;
    }
    return ss.str();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: reconstruct shard-folder" << std::endl;
    }

    std::cout << "Reconstructing..." << std::endl;

    std::size_t pos = std::string(argv[1]).rfind("/");
    std::string file_name = (pos == std::string::npos ? std::string(argv[1]) : std::string(argv[1]).substr(pos));

    // Setup output file
    std::ofstream o(file_name, std::ofstream::binary);

    char* memblock;

    for (uint32_t i = 0; i < num_shards; i++) {
        std::string shard_file_name = std::string(argv[1]) + "-shards/s" + std::to_string(i);

        std::ifstream s(shard_file_name, std::ofstream::ate | std::ofstream::binary);
        uint64_t shard_size = s.tellg();
        s.seekg(0);

        memblock = new char[shard_size];

        // Decode and write to reconstruction file
        s.read(memblock, shard_size);
        std::string dec_memblock = base64_decode(std::string(memblock));
        o.write(dec_memblock.c_str(), dec_memblock.size());

        delete[] memblock;
        s.close();
    }

    o.close();

    /// SHA256 Hash verification against original

    std::ifstream rf(argv[1], std::ifstream::ate | std::ifstream::binary);
    std::ifstream of("Original-" + std::string(argv[1]), std::ifstream::ate | std::ifstream::binary);
    uint64_t r_file_size = rf.tellg();
    uint64_t o_file_size = of.tellg();
    rf.seekg(0);
    of.seekg(0);

    char* r_content = new char[r_file_size];
    char* o_content = new char[o_file_size];
    rf.read(r_content, r_file_size);
    of.read(o_content, o_file_size);

    std::string r_256_hash = sha256(r_content);
    std::string o_256_hash = sha256(o_content);

    if (o_256_hash == r_256_hash) {
        std::cout << "SUCCESS!" << std::endl;
    }
    else {
        std::cout << "FAIL!" << std::endl;
    }

    delete[] r_content;
    delete[] o_content;

    return 0;
}