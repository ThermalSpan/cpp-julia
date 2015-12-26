#include <stdlib.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include "Complex.h"
#include "tiffWrapper.h"
#include "AtomicGrid.h"

using namespace std;
using namespace Math;
using namespace Image;

// Parameters
int px = 300;
int py = 200;

float x0 = -2.0;
float y0 = -1.0;

float width = 3.0;
float height = 2.0;

int iteration = 255;
int threadCount = 10;

// Data Structures
AtomicGrid* grid;
ImageData image;

mutex queueLock;
mutex printLock;
list <int> *jobQueue;

// Functions
C_f transform (C_f c) {
	float ta = c.a / (float) px;
	float tb = c.b / (float) py;

	ta *= width;
	ta *= height;

	ta += x0;
	ta += y0;

	return initComplex (ta, tb); 
}

void colorize (long count, Pixel* p) {
	char c = (char) min ((int) count, 255);

	p->R = c;
	p->G = c;
	p->B = c;
	p->A = 255;
}

int getJob () {
	int result = -1;
	queueLock.lock ();
	if (!jobQueue->empty()) {
		result = jobQueue->front ();
		jobQueue->pop_front ();
	}
	queueLock.unlock ();
	return result;
}

void threadPrint (string s) {
	printLock.lock ();
	cout << s << endl;
	printLock.unlock ();
}

void threadJob (int id) {
	int row = getJob ();
	list <C_f> iterates;
//	threadPrint ("Thread: " + to_string (id) + " first job: " + to_string (row));	
	while (row != -1) {
		float y = (float) row;
		float x;
		for (int xi = 0; xi < px; xi++) {
			x = (float) xi;
			C_f t = initComplex (x, y);
			C_f c = transform (t);
			C_f z = c;
			iterates.push_back (z);

			int count = 0;
			while (count < iteration && squaredMag (z) < 4.0) {
				z = z * z + c;
				iterates.push_back (z);
				count++;
			}
/*
			if (count < iteration) {
				for (auto it = iterates.begin (); it != iterates.end (); it++) {
					grid->hit((*it).a, (*it).b);
				}
			}*/
			char col = (char) min (count, 255);
			image.dataArray[(row * px) + xi].R = col;
			image.dataArray[(row * px) + xi].G = col;
			image.dataArray[(row * px) + xi].B = col;
			image.dataArray[(row * px) + xi].A = 255;



			//threadPrint ("Thread: " + to_string (id) + " (" + to_string(x)+ ", " + to_string (y) + "): " + to_string (count));

			iterates.clear ();
		}

		row = getJob ();
		//threadPrint ("Thread: " + to_string (id) + " job: " + to_string (row));
	}
}

void gridToImage () {
	for (int y = 0; y < py; y++) {
		for (int x = 0; x < px; x++) {
			colorize (grid->get (x, y), &(image.dataArray[ y * px + x]));
		}
	}
}



int main () {
	cout << "Hello... initializing" << endl;

	grid = new AtomicGrid (px, py, x0, y0, width, height);
	image.height = px;
	image.width = py;
	image.dataArray = (Pixel*) malloc (px * py * sizeof (Pixel));
	jobQueue = new list <int> ();
	thread** threads = (thread**) malloc (threadCount * sizeof(thread*));
/*
	cout << "Loading Queue..." << endl;
	for (int y = 0; y < py; y++) {
		jobQueue->push_back (y);
	}

	cout << "Starting Threads..." << endl;
	for (int t = 0; t < threadCount; t++) {
		threads[t] = new thread (threadJob, t);
	}

	threadPrint ("Joining Threads...");
	for (int t = 0; t < threadCount; t++) {
		threads[t]->join ();
	}
	
	cout << "Colorizing and Exporting" << endl;
//	gridToImage ();*/

	for (int x = 0; x < px; x++) {
		for (int y = 0; y < py; y++) {

			cout << x << " " << y << endl;
			C_f c = transform (initComplex ((float) x, (float) y));
			C_f z = c;
			int count = 0;
			while (count < iteration && squaredMag (z) < 4.0) {
				z = z * z + c;
				count++;
			}
			char col = (char) min (count, 255);
			image.dataArray[(y * px) + x].R = col;
			image.dataArray[(y * px) + x].G = col;
			image.dataArray[y * px + x].B = col;
			image.dataArray[y * px + x].A = 255;

		}
	}
	exportTiff ("test1.tif", image);

	free (image.dataArray);
	delete (grid);
	delete (jobQueue);
	delete (threads);
	return 0;
}
