#ifndef _showTSP_H
#define _showTSP_H

class showTSP {
public:
    void readFile(int argc, char** argv);
    int** GetCity();
    int GetNUMBEROFCITES();
    void showCity(int** city, int color);
private:
    void initCity();
    int** CITY;
    int N;
};

#endif