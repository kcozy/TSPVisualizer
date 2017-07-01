#include <iostream>
#include <cstdlib>
#include <string>
#include "showTSP.h"
#include "readTSPLIB.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

using namespace std;

int** city;
int N;

template<class T> void shuffle(T ary[],int size)
{
    for(int i=0;i<size;i++)
    {
        int j = rand()%size;
        T t = ary[i];
        ary[i] = ary[j];
        ary[j] = t;
    }
}

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

    // sample route
    int tour[N];
    for(int i=0; i<N; i++) {
        tour[i] = i+1;
    }
    tour[N-1] = 0;

    for(int i=0; i<10; i++) {
        s->showRoute(tour);
        shuffle<int>(tour, N);
    }
    s->showBest(tour);

    s->showText(1.0);
    
    //s->MainLoop();
}