//
// Created by podda on 06/07/2021.
//
#include <string>
#include "mat.h"
#include "ppm.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <sstream>

#include "mat.h"
#include "ppm.h"
#include <iostream>
#include <fstream>

class PPM_HEADER{
    std::string magicNumber;
    unsigned int width, height, maxVal;

public:
    PPM_HEADER(std::ifstream& istream){
        std::string comment;

        istream >> magicNumber;

        istream.get();

        if(istream.peek() == '#')
            std::getline(istream, comment);


        istream >> width >> height >> maxVal;

        istream.get();

    }

    const std::string& getMagicNumber() const {
        return magicNumber;
    }

    unsigned int getWidth() const {
        return width;
    };

    unsigned int getHeight() const {
        return height;
    }

    unsigned int getMaxVal() const {
        return maxVal;
    }

    friend std::ostream& operator<<(std::ostream& os, const PPM_HEADER& ppm){
        os << "Magic number: " << ppm.getMagicNumber() << std::endl;
        os << "Width = " << ppm.getWidth() << ", height = " << ppm.getHeight() << std::endl;
        os << "MaxVal = " << ppm.getMaxVal() << std::endl;
        return os;
    }

};


bool LoadPPM(const std::string& filename, mat<vec3b>& img){
    std::ifstream is;
    is.open(filename, std::ios::binary);

    if(!is){
        std::cout << "Error opening .ppm file" << std::endl;
        return false;
    }

    PPM_HEADER ppm_header(is);

    std::cout << ppm_header;

    unsigned int sampleDim;

    if(ppm_header.getMaxVal() < 256)
        sampleDim = 1;
    else
        sampleDim = 2;

    img.resize(ppm_header.getHeight(), ppm_header.getWidth());

    for(unsigned int r = 0; r < img.rows(); ++r){
        for(unsigned int c = 0; c < img.cols(); ++c){
            switch(sampleDim){
                case 1:
                    unsigned char red, g, b;
                    is.read(reinterpret_cast<char *>(&red), sizeof(red));
                    is.read(reinterpret_cast<char *>(&g), sizeof(g));
                    is.read(reinterpret_cast<char *>(&b), sizeof(b));
                    vec3b pixel(red, g, b);
                    img(r, c) = pixel;
                    break;
            }
        }
    }

    return true;
}

void SplitRGB(const mat<vec3b>& img, mat<uint8_t>& img_r, mat<uint8_t>& img_g, mat<uint8_t>& img_b){
    int rows = img.rows();
    int cols = img.cols();

    img_r.resize(rows, cols);
    img_g.resize(rows, cols);
    img_b.resize(rows, cols);

    for(int r = 0; r < rows; ++r){
        for(int c = 0; c < cols; ++c){
            img_r(r, c) = img(r, c)[0];
            img_g(r, c) = img(r, c)[1];
            img_b(r, c) = img(r, c)[2];
        }
    }
}

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
    //std::cout << "Size: " << v.size() << std::endl;
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


std::string JSON(const std::string& filename){
    mat<vec3b> img;
    if(!LoadPPM(filename, img)){
        return "";
    }

    int width = img.cols();
    int height = img.rows();

    std::vector<uint8_t> encodedR, encodedG, encodedB;

    mat<uint8_t> r, g, b;

    SplitRGB(img, r, g, b);


    std::stringstream ss;

    PackBitsEncode(r, encodedR);
    PackBitsEncode(g, encodedG);
    PackBitsEncode(b, encodedB);


    ss << "{\n";
    ss << "\t\"width\": " << width << ",\n";
    ss << "\t\"height\": " << height << ",\n";
    ss << "\t\"red\": \"" << Base64Encode(encodedR) << "\",\n";
    ss << "\t\"green\": \"" << Base64Encode(encodedG) << "\",\n";
    ss << "\t\"blue\": \"" << Base64Encode(encodedB) << "\"\n}";

    std::string myJson = ss.str();

    return myJson;



}