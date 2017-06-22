#include <iostream>
#include "showTSP.h"
#include "readTSPLIB.h"

using namespace std;

int** city;
int N;

int main(int argc, char** argv) {
    // input from *.tsp
    readTSPLIB rtsp;
    rtsp.readFile(argc, argv);
    city = rtsp.CITY;
    N = rtsp.NUMBEROFCITIES;
    // initialize
    showTSP *s = new showTSP(N, city);
    s->initGL(argc, argv);

    // solve TSP here
    // to show process, s->showCity(CurrentRoute, color); 

    // sample route
    int tour[N];
    for(int i=0; i<N; i++) {
        tour[i] = i+1;
    }
    tour[N-1] = 0;
    s->showCity(tour, 0);
}