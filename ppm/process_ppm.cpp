//
// Created by podda on 06/07/2021.
//


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

