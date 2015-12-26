//
//  AtomicGrid.cpp
//  julia
//
//  Created by Russell Wilhelm Bentley on 12/25/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <math.h>
#include <assert.h>
#include "AtomicGrid.h"

using namespace std;

AtomicGrid::AtomicGrid (int cellX, int cellY, float x0, float y0, float width, float height) {
    m_cellX = cellX;
    m_cellY = cellY;
    m_xmin = x0;
    m_ymin = y0;
    m_xmax = width + x0;
    m_ymax = height + y0;

    m_cellWidth = width / (float) cellX;
    m_cellHeight = height / (float) cellY;

    m_dataArray = (atomic <long> *) malloc (cellX * cellY * sizeof (atomic <long>));
}

AtomicGrid::~AtomicGrid () {
    free (m_dataArray);
}

void AtomicGrid::hit (float x, float y) {
    if ( x > m_xmin && x < m_xmax && y > m_ymin && y < m_ymax) {
        float tx = x - m_xmin;
        float ty = y - m_ymin;

        int xIndex = (int) floor (tx / m_cellWidth);
        int yIndex = (int) floor (ty / m_cellHeight);

        assert (xIndex < m_cellX && yIndex < m_cellY);

        m_dataArray[yIndex * m_cellX + xIndex].fetch_add (1.0, memory_order_relaxed);
    } else {
        // nothing
    }
}

long AtomicGrid::get (int x, int y) {
    assert (x >= 0 && x < m_cellX && y >= 0 && y < m_cellY);
    return m_dataArray[y * m_cellX + x].load ();
}
