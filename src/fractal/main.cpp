#include <stdlib.h>
#include <iostream>
#include "../Math/Complex.h"
#include "../Tiff/tiffWrapper.h"

using namespace std;
using namespace Math;
using namespace Image;

C_f transform (float x, float y) {
    float xt = x / 10000.0;
    float yt = y / 10000.0;
    
    xt -= 2.2;
    yt -= 1.0;

    return initComplex (xt, yt);
}

int main () {
    int w = 30000;
    int h = 20000;

	ImageData image;
	image.width = w;
	image.height = h;
	image.dataArray = (Pixel *) malloc (w * h * sizeof(Pixel));
	
    for (float x = 0.0; x < w; x += 1.0) {
        for (float y = 0.0; y < h; y += 1.0) {
            C_f c = transform (x, y);
            C_f z = c;
            int count = 0;

            while (count < 255 && squaredMag (z) < 4.0) {
               count++;
               z = (z * z) + c;
            }
			
			Pixel* p = &image.dataArray[(int) y * w + (int) x];
			p->R = (char) count;
			p->G = (char) count;
			p->B = (char) count;
			p->A = 255;

        }
    }
	
	exportTiff ("test.tiff", image);

	free (image.dataArray);
    return 0;
}
