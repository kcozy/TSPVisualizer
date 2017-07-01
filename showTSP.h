#ifndef _showTSP_H
#define _showTSP_H

class showTSP {
public:
    showTSP(int n, int** city);
    virtual ~showTSP();

    void initGL(int argc, char** argv);

    void showRoute(int* route);
    void showBest(int* route);
    void showPheromones(double** pheromones);
    void showText(double length);

private:
    int Highest();
    void MakeDisplayPosition();
    //void display();

    int** CITIES;
    double** DispCITIES;
    int NUMBEROFCITIES;
};

#endif