#ifndef _WINDOW_METHOD_H_
#define _WINDOW_METHOD_H_
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define A_COEFFICENT 2147483647
#define MOD 2147483641
#define WIDTH 3
#define SIZE_PRECOMPUTED 8

typedef struct {
    int x;
    int y;
} Point;

int* decimalToBinary(int decimal, int* scalar_bits);
int modular_exponentiation(int a, int b);
int inverse(int a);
Point point_add(Point p, Point q);
Point error_detection_window_method(Point point, int scalar);
void error_detection(int* pre_pattern_counter,int scalar_bits_length,int *scalar_bits,int width,int* width_precomputation);
int CC(int* pre_pattern_counter,int* post_pattern_counter,int length);


#endif
