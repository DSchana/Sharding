#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

constexpr uint32_t num_shards = 6;

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
        std::string shard_file_name = std::string(argv[1]) + "/s" + std::to_string(i);

        std::ifstream s(shard_file_name, std::ofstream::ate | std::ofstream::binary);
        uint64_t shard_size = s.tellg();
        s.seekg(0);

        memblock = new char[shard_size];

        s.read(memblock, shard_size);
        o.write(memblock, shard_size);

        delete[] memblock;
        s.close();
    }

    o.close();

    return 0;
}