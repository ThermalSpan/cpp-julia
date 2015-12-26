//
//  tiffWrapper.cpp
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/22/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "tiffWrapper.h"

using namespace Image;

void Image::exportTiff (const std::string &filename, const ImageData &data) {
    TIFF *out = TIFFOpen (filename.c_str (), "w");

    // Image specifics
    int width = data.width;
    int height = data.height;
    int channels = 4;
    tsize_t lineBytes = channels * width;
    char* image = (char *) data.dataArray;

    // Setup tags for image file
    TIFFSetField (out, TIFFTAG_IMAGEWIDTH, width);
    TIFFSetField (out, TIFFTAG_IMAGELENGTH, height);
    TIFFSetField (out, TIFFTAG_SAMPLESPERPIXEL, channels);
    TIFFSetField (out, TIFFTAG_BITSPERSAMPLE, 8);
    TIFFSetField (out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField (out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField (out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);

    // Buffer for line to write
    unsigned char* buf = nullptr;
    if (TIFFScanlineSize (out) == lineBytes) {
        buf = (unsigned char *) _TIFFmalloc (lineBytes);
    } else {
        buf = (unsigned char *) _TIFFmalloc (TIFFScanlineSize (out));
    }

    TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize (out, width * channels));

    for (uint32 row = 0; row < height; row++) {
        memcpy (buf, &image[row * lineBytes], lineBytes);
        if (TIFFWriteScanline (out, buf, row, 0) < 0) {
            break;
        }
    }
    
    TIFFClose (out);
    if (buf != nullptr) {
        _TIFFfree (buf);
    }

}
