//
// Created by podda on 06/07/2021.
//

//#include "compress.h"
#include <cstdint>
#include "mat.h"
#include <vector>
#include <iostream>
#include "mat.h"
#include "ppm.h"
#include <fstream>
#include <sstream>

void writeRun(unsigned int length, uint8_t value, std::vector<uint8_t>& encoded){
    if(length > 128){
        writeRun(128, value, encoded);
        writeRun(length - 128, value, encoded);
    }
    else{
        uint8_t code = 257 - length;
        encoded.push_back(code);
        encoded.push_back(value);
    }
}

void writeCopy(std::vector<uint8_t>& buffer, std::vector<uint8_t>& encoded){
    if(buffer.size() > 128){
        std::vector<uint8_t> left(buffer.begin(), buffer.begin() +127);
        std::vector<uint8_t> right(buffer.begin() +128, buffer.end());
        writeCopy(left, encoded);
        writeCopy(right, encoded);
    }
    else{
        uint8_t code = buffer.size() - 1;
        encoded.push_back(code);
        for (auto x : buffer) {
            encoded.push_back(x);
        }
    }
}

void PackBitsEncode(const mat<uint8_t>& img, std::vector<uint8_t>& encoded){
    const uint8_t *data = img.data();
    unsigned int size = img.size();
    std::vector<uint8_t> buffer;
    for(unsigned int i = 0; i <  size; ++i){

        unsigned int count = 1;
        while(i < size -1 && data[i] == data[i+1]){
            ++count;
            ++i;
        }
        if(count == 1)
            buffer.push_back(data[i]);
        else{
            if(buffer.size() != 0){
                writeCopy(buffer, encoded);
                buffer.clear();
            }
            writeRun(count, data[i], encoded);
        }

    }
    if(buffer.size()!=0){
        writeCopy(buffer, encoded);
        buffer.clear();
    }

    encoded.push_back(128);
}

void computeBase64Code(unsigned char& c){
    if(c < 26){
        c+=65;
    }
    else if(c < 52){
        c += 71;
    }
    else if(c < 62){
        c -= 4;
    }
    else if(c == 62){
        c = '+';
    }
    else if(c == 63){
        c = '/';
    }
}

void addBase64(std::string& string, uint8_t tmp1, uint8_t tmp2, uint8_t tmp3){
    unsigned char first = 0, second = 0, third = 0, fourth = 0;
    //std::cout << "Temps" << std::endl;
    //std::cout << (int)tmp1 << "\t" << (int)tmp2 << "\t" << (int)tmp3 << std::endl;

    first = (tmp1 >> 2) & 0b00111111;
    second = ((tmp1 << 4) | (tmp2 >> 4)) & 0b00111111;
    third = ((tmp2 << 2) | (tmp3 >> 6)) & 0b00111111;
    fourth = tmp3 & 0b00111111;
    //std::cout << "Manipulated" << std::endl;
    //std::cout << (int)first << "\t" << (int)second << "\t" << (int)third << "\t" << (int)fourth << std::endl;
    computeBase64Code(first);
    computeBase64Code(second);
    computeBase64Code(third);
    computeBase64Code(fourth);
    string+=first;
    string+=second;
    string+=third;
    string+=fourth;
}

std::string Base64Encode(const std::vector<uint8_t>& v){
    std::string return_string;
    for(unsigned int i = 0; i*3 < v.size() - 2; ++i){
        addBase64(return_string, v[i*3], v[i*3 + 1], v[i*3 + 2]);

    }
    std::cout << "Size: " << v.size() << std::endl;
    switch (v.size() % 3) {
        case 1:
            addBase64(return_string, v[v.size()-1], 0b10000000, 0b10000000);
            break;
        case 2:
            std::cout << "case 2" << std::endl;
            addBase64(return_string, v[v.size()-2], v[v.size()-1], 0b10000000);
            break;
        default:
            break;
    }

    return return_string;


}

