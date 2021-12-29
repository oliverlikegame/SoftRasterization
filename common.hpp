//
//create by AO LI 11/16/2021
//
#pragma once

#include <iostream>

#define LOG(msg)                                                                         \
    std::cout << "[" << __FILE__ << ", " << __FUNCTION__ << ", " << __LINE__             \
              << "]: " << msg << std::endl;

#define CHECK(cond)                                                                      \
    do {                                                                                 \
        if (!(cond)) {                                                                   \
            LOG("Runtime Error.");                                                       \
            exit(-1);                                                                    \
        }                                                                                \
    } while (false)

#define CHECKTexture( w , h )                                                            \
    do {                                                                                 \
        if ( w < 0 || h < 0) {                                                           \
            LOG("Runtime Error.Texture's height or weight illegal!");                    \
            exit(-1);                                                                    \
        }                                                                                \
        if ( !(w & (w-1))==0 || !(h & (h-1))==0 ) {                                      \
            LOG("Runtime Error.Texture's height or weight not 2^n!");                    \
            exit(-1);                                                                    \
        }                                                                                \
    } while (false)
