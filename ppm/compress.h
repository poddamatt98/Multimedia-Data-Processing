//
// Created by podda on 06/07/2021.
//

#ifndef PACKBITSEXAM_COMPRESS_H
#define PACKBITSEXAM_COMPRESS_H
#include <cstdint>
#include "mat.h"
#include <vector>

void PackBitsEncode(const mat<uint8_t>& img, std::vector<uint8_t>& encoded);
std::string Base64Encode(const std::vector<uint8_t>& v);
std::string JSON(const std::string& filename);

#endif //PACKBITSEXAM_COMPRESS_H
