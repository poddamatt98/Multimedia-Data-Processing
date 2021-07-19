//
// Created by podda on 06/07/2021.
//

#ifndef PPM_LOAD_PROCESS_PPM_H
#define PPM_LOAD_PROCESS_PPM_H
#include "mat.h"
#include "ppm.h"

bool LoadPPM(const std::string& filename, mat<vec3b>& img);
void SplitRGB(const mat<vec3b>& img, mat<uint8_t>& img_r, mat<uint8_t>& img_g, mat<uint8_t>& img_b);

#endif //PPM_LOAD_PROCESS_PPM_H
