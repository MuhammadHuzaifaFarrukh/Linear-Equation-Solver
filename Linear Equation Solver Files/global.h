#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

using namespace std;

//Validate the Input (int or float etc)
int validateint_fullwithrangealso(int n);
float validatefloat_full(float num);

//Swapping
void swapping(float *a, float *b);

//Allocation of heap memory matrices
void allocate(float **arr, int rows, int columns);

//The Main Function
float** inverse_row_echelon(float **arr , float **b ,float **arr_copy , float **b_copy, int m , int n);


