#include <fstream>
#include <iostream>
#include <getopt.h>
#include <string>

int main(int argc, char* argv[]) {
    struct option long_options[] = {
        {"source_file1", required_argument, 0, 'a'},
        {"source_file2", required_argument, 0, 'b'},
        {0, 0, 0, 0}
    };

    int option_index = 0;
    int c;

    std::string file1_path, file2_path;

    while ((c = getopt_long(argc, argv, "a:b:", long_options, &option_index)) != -1) {
        switch (c) {
            case 'a':
                file1_path = optarg;
                break;
            case 'b':
                file2_path = optarg;
                break;
            default:
                return 1;
        }
    }

    std::ifstream file1(file1_path, std::ios::binary);
    std::ifstream file2(file2_path, std::ios::binary);

    if(!file1.is_open()) {
        std::cerr << "Error: Cannot open file " << file1_path << "\n";
        return 1;
    }

    if(!file2.is_open()) {
        std::cerr << "Error: Cannot open file " << file2_path << "\n";
        return 1;
    }

    char byte1, byte2;
    int position = 0;

    while(file1.get(byte1) && file2.get(byte2)) {
        if(byte1 != byte2) {
            std::cout << position;
            return 1;
        }
        position++;
    }

    if(file1.get(byte1) || file2.get(byte2)) {
        std::cout << position;
        return 1;
    }

    return 0;
}