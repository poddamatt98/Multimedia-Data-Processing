#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

void literal(std::istream& is, std::ostream& os, int len, std::vector<uint8_t>& vec){
    uint8_t buffer;
    for(unsigned int i = 0; i < len; ++i){
        is.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        os.write(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        vec.push_back(buffer);
    }
}

void copy(std::ostream& os, unsigned int offset, unsigned int length, std::vector<uint8_t>& decompressedData){

    size_t size = decompressedData.size();
    uint8_t buffer;

    for(unsigned int i = 0; i < length; ++i){
        buffer = decompressedData[size -offset +i];
        os.write(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        decompressedData.push_back(buffer);
    }
}

bool decompress(std::istream& is, std::ostream& os){

    //preamble
    // read varint
    uint64_t len = 0;

    std::vector<uint8_t> decompressedData;


    while(1){


        uint8_t byte = 0;

        is.read(reinterpret_cast<char *>(&byte), sizeof(byte));

        if((byte & 0b10000000) >> 7 == 1) { // read again
            byte = byte & 0b01111111;
            len += byte;
            len = len << 7;
            continue;
        }
        else{
            byte = byte & 0b01111111;
            len += byte;
            break;
        }
    }

    //stream starts
    // literal expected

    uint8_t buffer;

    while(1){
        is.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
        if(is.eof())
            break;
        std::vector<uint8_t> readData;
        uint8_t tag = buffer & 0b00000011;

        if(tag == 0b00){
            //literal
            unsigned int length = buffer >> 2;

            if(length <= 59){
                //read length + 1 bytes
                ++length;

                literal(is, os, length, decompressedData);

                continue;
            }
            else if(length == 60){
                //read next byte as length
                is.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
                length = buffer;
                ++length;

                literal(is, os, length, decompressedData);

                continue;

            }
            else if(length == 61){
                //read next 2 bytes as length
                uint16_t tmp;

                is.read(reinterpret_cast<char *>(&tmp), sizeof(uint16_t));
                length=tmp;
                ++length;

                literal(is, os, length, decompressedData);

                continue;
            }
            else if(length == 62){
                //read next 3 bytes as length
                uint32_t tmp;

                is.read(reinterpret_cast<char *>(&tmp), sizeof(uint16_t));
                tmp = tmp << 8;
                is.read(reinterpret_cast<char *>(&buffer), sizeof(uint8_t));
                tmp += buffer;
                length=tmp;
                ++length;

                literal(is, os, length, decompressedData);

                continue;
            }
            else if(length == 63){
                //read next 4 bytes as length
                uint32_t tmp;

                is.read(reinterpret_cast<char *>(&tmp), sizeof(uint32_t));
                length=tmp;
                ++length;

                literal(is, os, length, decompressedData);
                continue;
            }

        }
        else if(tag == 0b01){

            //copy with 1-byte offset
            unsigned int length = (buffer >> 2) & 0b00000111;
            length += 4;
            uint16_t offset = 0;
            //3 most significant bits of offset are 7, 6, 5 in tag byte
            offset = buffer >> 5;

            //read next byte
            is.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));

            offset = offset << 8;
            offset += buffer;

            copy(os, offset, length, decompressedData);

            continue;

        }
        else if(tag == 0b10){
            //copy with 2-byte offset

            unsigned int length = buffer >> 2;
            ++length;
            uint16_t offset;
            is.read(reinterpret_cast<char *>(&offset), sizeof(uint16_t));

            copy(os, offset, length, decompressedData);

            continue;

        }
        else if(tag == 0b11){

            //copy with 4-byte offset
            unsigned int length = buffer >> 2;
            ++length;
            uint32_t offset;
            is.read(reinterpret_cast<char *>(&offset), sizeof(uint32_t));

            copy(os, offset, length, decompressedData);

            continue;

        }

    }

    return true;

}

int main(int argc, char **argv) {
    if(argc != 3){
        std::cout << "Error: check format" << std::endl;
        return EXIT_FAILURE;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    std::ifstream is;
    std::ofstream os;

    is.open(inputFileName, std::ios::binary);

    if(!is){
        std::cout << "Error opening input file" << std::endl;
        return EXIT_FAILURE;
    }


    os.open(outputFileName, std::ios::binary);

    if(!os){
        std::cout << "Error opening output file" << std::endl;
        return EXIT_FAILURE;
    }

    decompress(is, os);

    return 0;
}
