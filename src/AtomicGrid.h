//
//  AtomicGrid.h
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/25/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <atomic>

using namespace std;

class AtomicGrid {
protected:
    atomic <long> *m_dataArray;
    int m_cellX;
    int m_cellY;
    float m_cellWidth;
    float m_cellHeight;
    float m_xmin;
    float m_xmax;
    float m_ymin;
    float m_ymax;

public:
    AtomicGrid (int cellX, int cellY, float x0, float y0, float width, float height);
    ~AtomicGrid ();

    void hit (float x, float y);
    long get (int x, int y);
};
