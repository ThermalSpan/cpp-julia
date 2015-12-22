//
//  main.cpp
//  buddha
//
//  Created by Russell Wilhelm Bentley on 12/22/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <stdlib.h>
#include <tiffio.h>
#include <iostream>

using namespace std;

int main () {
    TIFF* tif = TIFFOpen ("test.tif", "r");
    cout << "Tried to open tiff" << endl;
    if (tif != nullptr) {
        TIFFClose (tif);
    }
    return 0;
}
