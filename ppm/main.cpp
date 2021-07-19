#include <iostream>
#include <fstream>
#include "process_ppm.h"
#include "mat.h"
#include "ppm.h"
#include "compress.h"

int main() {

    std::cout << JSON("test.ppm") << std::endl;
    /*
    mat<vec3b> img;
    LoadPPM("facolta.ppm", img);
    mat<uint8_t> r, g, b;
    SplitRGB(img, r, g, b);

    std::vector<uint8_t> encoded;

    PackBitsEncode(r, encoded);
    std::ofstream output;
    output.open("output", std::ios::binary);
    std::cout << "OK, size = " << encoded.size() << std::endl;
    for(auto x : encoded){
        output << x << "\t";
    }*/


}
