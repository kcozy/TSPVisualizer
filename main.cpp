#include <iostream>
#include "showTSP.h"

using namespace std;

int main(int argc, char** argv) {
    showTSP *s = new showTSP();
    int** city;
    s -> readFile(argc, argv);
    city = s->GetCity();
    int N = s->GetNUMBEROFCITES();
    int tour[N];
    for(int i=0; i<N; i++) {
        tour[i] = i+1;
    }
    tour[N-1] = 0;
    
    s->showCity(argc, argv, tour, 0);
}