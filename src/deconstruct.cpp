#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: deconstruct file-name" << std::endl;
    }

    std::cout << "Deconstructing..." << std::endl;

    std::ifstream f(argv[1], std::ifstream::ate | std::ifstream::binary);
    uint64_t file_size = f.tellg();
    f.seekg(0);

    std::cout << "File size: " << file_size << "bytes" << std::endl;

    return 0;
}