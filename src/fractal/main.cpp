#include <stdlib.h>
#include <iostream>
#include <thread>
#include "../Math/Complex.h"
#include "../Tiff/tiffWrapper.h"

using namespace std;
using namespace Math;
using namespace Image;

C_f transform (float x, float y) {
    float xt = x / 8000.0;
    float yt = y / 8000.0;
    
    xt -= 2.2;
    yt -= 1.0;

    return initComplex (xt, yt);
}

struct JobData {
    ImageData image;
    int id;
    int start;
    int end;
};

void runJob (JobData *job) {
    Pixel* data = job->image.dataArray;
    int w = job->image.width;
    int h = job->image.height;

    for (int i = job->start; i < job->end; i++) {
        float x = (float) (i % w);
        float y = (float) (i / h);

        C_f c = transform (x, y);
        C_f z = c;
        int count = 0;

            while (count < 255 && squaredMag (z) < 4.0) {
               count++;
               z = (z * z) + c;
            }
			
			Pixel* p = &data[i];
			p->R = (char) count;
			p->G = (char) count;
			p->B = (char) count;
			p->A = 255;
    }
}



int main () {
    int w = 24000;
    int h = 16000;

	ImageData image;
	image.width = w;
	image.height = h;
	image.dataArray = (Pixel *) malloc (w * h * sizeof(Pixel));
    int pixels = w * h;
    unsigned threadCount = std::thread::hardware_concurrency() * 2;
    int pixelsPer = pixels / threadCount;

    JobData* jobs = new JobData[threadCount];
    for (int i = 0; i < threadCount; i++) {
       jobs[i].image = image;
       jobs[i].id = i;
       jobs[i].start = i * pixelsPer;
       jobs[i].end = (i + 1) * pixelsPer;
    }

    thread** threads = (thread**) malloc (threadCount * sizeof(thread*));
    for (int i = 0; i < threadCount; i++) {
        threads[i] = new thread (runJob, &jobs[i]);
    }
    for (int i = 0; i < threadCount; i++) {
        threads[i]->join();
        delete (threads[i]);
    }

	
	exportTiff ("test.tiff", image);

	free (image.dataArray);
    free (threads);
    delete (jobs);
    return 0;
}
