//
//  tiffWrapper.h
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/22/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <stdlib.h>
#include <string>
#include <tiffio.h>

namespace Image {
    struct Pixel {
        char R;
        char G;
        char B;
        char A;
    };

    struct ImageData {
        Pixel* dataArray;
        int height;
        int width;
    };

    void exportTiff (const std::string &filename, const ImageData &data); 
};

