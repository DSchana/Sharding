#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

constexpr uint32_t num_shards = 6;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: deconstruct file-name" << std::endl;
    }

    std::cout << "Deconstructing..." << std::endl;

    std::size_t pos = std::string(argv[1]).rfind("/");
    std::string file_name = (pos == std::string::npos ? std::string(argv[1]) : std::string(argv[1]).substr(pos));

    // Setup input file
    std::ifstream f(argv[1], std::ifstream::ate | std::ifstream::binary);
    uint64_t file_size = f.tellg();
    uint64_t shard_size = ceil(file_size / num_shards);
    f.seekg(0);

    // Setup output files
    system(("mkdir " + file_name).c_str());

    char* memblock;

    for (uint32_t i = 0; i < num_shards; i++) {
        std::string shard_file_name = file_name + "/s" + std::to_string(i);
        system(("touch " + shard_file_name).c_str());

        std::ofstream s(shard_file_name, std::ofstream::binary);

        memblock = new char[shard_size];

        f.read(memblock, shard_size);
        s.write(memblock, shard_size);

        delete[] memblock;
        s.close();
    }

    f.close();

    return 0;
}