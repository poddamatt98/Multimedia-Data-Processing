#include <iostream>
#include "lz78encode.h"
#include <chrono>

int main() {

    std::cout << lz78encode("bibbia.txt", "bibbiaencoded.txt", 10) << std::endl;
}
