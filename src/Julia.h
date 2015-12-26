//
// Julia.h
// julia
//
//

#pragma once

#include <list>
#include <mutex>
#include "Complex.h"

using namespace std;
using namespace Complex;

namespace Julia {

    template <typename Num> class Function {
        public:
            Num operator() (Num z) = 0;
    }

    struct basicPlotJob () {
        int row;
    }

    typedef list <basicPlotJob*> basicJobQueue;

    void runBasicPlotJob (basicPlotJob* job, ImageData* image, const Function <C_f> *f) {
    
    }

    void basicPlotThread (ImageData* image, mutex* queueLock, basicJobQueue* queue) {
        basicPlotJob* job;

        gueueLock->lock ();
        if (!queue->empty()) {
            basicPlotJob* job = queue.front ();
            queue.pop_front ();
        } else {
            job = nullptr
        }
        queueLock->unlock ();

        while (job != nullptr) {
            runBasicPlotJob
        }
    }



    bool runBasicPlot (const Function <C_f> *f, const int &px, const int &py) {
        mutex m_queueLock;
        list <basicPlotJob*> jobQueue ();

        // Setup Jobs
        for (int i = 0; i < py; i++) {
           jobs[i].row = i; 
        }

        //Setup Threads
        
        int pointCount = px * py;
        unsigned threadCount = std::thread::hardware_concurrency() * 2;
        if (threadCount == 0) threadCount = 1;




    }
                       

        return true;
    }
};
