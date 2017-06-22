#ifndef _showTSP_H
#define _showTSP_H

class showTSP {
public:
    showTSP(int n, int** city);
    virtual ~showTSP();

    void initGL(int argc, char** argv);
    void showCity(int* route, int color);

private:
    int Highest();
    void MakeDisplayPosition();

    int** CITIES;
    double** DispCITIES;
    int* ROUTE;
    int NUMBEROFCITIES;
};

#endif