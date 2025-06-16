#include "mathlib.h"
#include <stdio.h>
#include <math.h>

#define EPSILON 0.0000000001


double absolute(double x) {
    if (x < 0) {
        return -x;
    }
    else {
        return x;
    }
}

// Had help from Harsh's office hour
double arcSin(double x) {
    double x_0 = 0;
    while (absolute(sin(x_0) - x) > EPSILON) {
        x_0 =  x_0 - ((sin(x_0) - x) / cos(x_0));
    }
    return x_0;
}

double arcCos(double x) {
    return ((M_PI/2) - arcSin(x));
}

double root(double x) {
    double square_root = x / 2;
    double x_0 = 0;
    while (square_root != x_0) {
        x_0 = square_root;
        square_root = ( x / x_0 + x_0) / 2;
    }
    return square_root;
}

double arcTan(double x) {
    return arcSin(x / root(1 + (x * x)));
}


double exponent(double x) {
    double prev = 1.0;
    double sum  = 1.0;
    for (double i = 1.0; prev > EPSILON; i+=1){
        prev *= (x / i);
        sum += prev;
    }

    return sum;
}

double Log(double x) {
    double x_k = 1;
    while ((absolute(x - exponent(x_k))) > EPSILON) {
        x_k =  x_k + ((x - exponent(x_k)) / exponent(x_k));
    }
    return x_k;
}
