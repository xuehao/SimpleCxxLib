/*
 * File: TestGridClass.cpp
 * -----------------------
 * This file contains a unit test of the Grid class.
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#include <iostream>
#include <sstream>
#include <string>

#include "grid.h"
#include "strlib.h"
#include "unittest.h"
using namespace std;

static void testGridCopy(Grid<double>& grid, Grid<double> gridByValue);
static string gridSignature(Grid<double>& grid);
static Grid<double> createIdentityMatrix(int n);

class SumFunctor {
public:
    SumFunctor(double& sum) {
        dp = &sum;
    }

    void operator()(const double& x) {
        *dp += x;
    }

private:
    double* dp;
};

void testGridClass() {
    declare(Grid<double> matrix(2, 2));
    test(matrix.numRows(), 2);
    test(matrix.numCols(), 2);
    trace(matrix[0][0] = 7);
    trace(matrix[0][1] = 3.5);
    trace(matrix[1][0] = -2);
    trace(matrix[1][1] = 42);
    test(matrix.get(0, 0), 7);
    trace(matrix.set(0, 0, 17));
    test(matrix.get(0, 0), 17);
    declare(Grid<double>::iterator it = matrix.begin());
    test(it == matrix.begin(), true);
    test(it == matrix.end(), false);
    test(*it++, 17);
    test(*it++, 3.5);
    test(*it++, -2);
    test(*it++, 42);
    test(it == matrix.end(), true);
    declare(double sum = 0.0);
    trace(matrix.mapAll(SumFunctor(sum)));
    test(sum, 60.5);
    trace(sum = 0);
    trace(for (double x : matrix) sum += x);
    test(sum, 60.5);
    testGridCopy(matrix, matrix);
    trace(matrix = createIdentityMatrix(2));
    test(matrix[0][0], 1.0);
    test(matrix[0][1], 0.0);
    test(matrix[1][0], 0.0);
    test(matrix[1][1], 1.0);
    test(matrix.toString(), "{{1, 0}, {0, 1}}");
    declare(istringstream ss("{{1, 2, 3}, {4, 5, 6}}"));
    trace(ss >> matrix);
    test(matrix.toString(), "{{1, 2, 3}, {4, 5, 6}}");
    reportResult("Grid class");
}

/* Sample code from the Grid interface */

static Grid<double> createIdentityMatrix(int n) {
    Grid<double> matrix(n, n);
    for (int i = 0; i < n; i++) {
        matrix[i][i] = 1.0;
    }
    return matrix;
}

/* Test copy constructor and assignment operator */

static void testGridCopy(Grid<double>& grid, Grid<double> gridByValue) {
    Grid<double> gridCopy = grid;
    test(gridByValue.numRows() == grid.numRows(), true);
    test(gridByValue.numCols() == grid.numCols(), true);
    test(gridCopy.numRows() == grid.numRows(), true);
    test(gridCopy.numCols() == grid.numCols(), true);
    test(gridSignature(grid) == gridSignature(gridByValue), true);
    test(gridSignature(grid) == gridSignature(gridCopy), true);
}

static string gridSignature(Grid<double>& grid) {
    string signature;
    for (int row = 0; row < grid.numRows(); row++) {
        if (row > 0)
            signature += "/";
        for (int col = 0; col < grid.numCols(); col++) {
            if (col > 0)
                signature += ",";
            signature += realToString(grid[row][col]);
        }
    }
    return signature;
}
