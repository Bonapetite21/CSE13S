#include "mathlib.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>


int main (int argc, char** argv) {

    int arcSinFlag = 0;
    int arcCosFlag = 0;
    int arcTanFlag = 0;
    int LogFlag = 0;
    int opt = 0;
    
    while ((opt = getopt(argc, argv, "asctl")) != -1) {
        switch (opt) {
            case 'a':
                arcSinFlag = 1;
                arcCosFlag = 1;
                arcTanFlag = 1;
                LogFlag = 1;
                break;
            
            case 's':
                arcSinFlag = 1;
                break;
            
            case 'c':
                arcCosFlag = 1;
                break;
            
            case 't':
                arcTanFlag = 1;
                break;
            
            case 'l':
                LogFlag = 1;
                break;
            
            default :
                break;
        }
    }

    if (arcSinFlag == 1) { // assume this is some variable flagged in the getopt
        printf("  %s            %s              %s        %s\n", "x", "arcSin", "Library", "Difference");
        printf("  %s            %s              %s        %s\n", "-", "------", "-------", "----------");
        for (double x = -1.0; x < 1; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.20lf\n", x, arcSin(x), asin(x), arcSin(x) - asin(x));
        }
    }

    if (arcCosFlag == 1) { // assume this is some variable flagged in the getopt
        printf("  %s            %s              %s        %s\n", "x", "arcCos", "Library", "Difference");
        printf("  %s            %s              %s        %s\n", "-", "------", "-------", "----------");
        for (double x = -1.0; x < 1; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.20lf\n", x, arcCos(x), acos(x), arcCos(x) - acos(x));
        }
    }

    if (arcTanFlag == 1) { // assume this is some variable flagged in the getopt
        printf("  %s            %s              %s        %s\n", "x", "arcTan", "Library", "Difference");
        printf("  %s            %s              %s        %s\n", "-", "------", "-------", "----------");
        for (double x = -1.0; x < 1; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.20lf\n", x, arcTan(x), atan(x), arcTan(x) - atan(x));
        }
    }

    if (LogFlag == 1) { // assume this is some variable flagged in the getopt
        printf("  %s            %s              %s        %s\n", "x", "Log   ", "Library", "Difference");
        printf("  %s            %s              %s        %s\n", "-", "------", "-------", "----------");
        for (double x = 1; x < 10; x += 0.1) {
            printf(" %7.4lf % 16.8lf % 16.8lf % 16.20lf\n", x, Log(x), log(x), Log(x) - log(x));
        }
    }
    return 0;
}     
