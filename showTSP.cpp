#include "showTSP.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cstdlib>

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

int **showTSP::GetCity()
{
    return CITY;
}

int showTSP::GetNUMBEROFCITES()
{
    return N;
}

void showTSP::initCity()
{
    CITY = (int **)malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++)
    {
        CITY[i] = (int *)malloc(sizeof(int) * 2);
    }
}

void showTSP::readFile(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: argment must be 2. like \"./a.out *.tsp\"" << std::endl;
        exit(1);
    }
    std::string filename = argv[1];

    std::ifstream reading_file;
    reading_file.open(filename, std::ios::in);
    if(!reading_file) {
        std::cerr << "Error: cannot open file(" << filename << ")" << std::endl;
        exit(1);
    }

    std::string reading_line_buffer;

    while (!reading_file.eof())
    {
        // read by line
        std::getline(reading_file, reading_line_buffer);

        // End of file *.tsp
        if (reading_line_buffer == "EOF")
            break;

        // read by delimiter on reading "one" line
        const char delimiter = ' ';
        std::string index, arg_first, arg_second;
        std::istringstream line_separater(reading_line_buffer);
        do{
        std::getline(line_separater, index, delimiter);
        }while(index == "");
        std::getline(line_separater, arg_first, delimiter);
        std::getline(line_separater, arg_second, delimiter);

        if (index == "DIMENSION")
        {
            N = atoi(arg_second.c_str());
            initCity();
        }
        else if (std::all_of(index.cbegin(), index.cend(), isdigit))
        {
            CITY[atoi(index.c_str()) - 1][0] = atoi(arg_first.c_str());
            CITY[atoi(index.c_str()) - 1][1] = atoi(arg_second.c_str());
            //std::cout << atoi(arg_first.c_str()) << " " << atoi(arg_second.c_str()) << std::endl;
        }
    }
}

double** DispCITY;
int* TOUR;
int SIZE;


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    // 描画開始
    glBegin(GL_POINTS);
    glColor3d(0.0, 0.0, 0.0);
    for(int i=0; i<SIZE; i++) {
        glVertex2d(DispCITY[i][0], DispCITY[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 0.0, 0.0);
    for(int i=0; i<SIZE; i++) {
        glVertex2d(DispCITY[i][0], DispCITY[i][1]);
    }
    glEnd();
    // 描画終了
    glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
    // esc,q,Qが入力されたら終了
    switch(key) {
        case 'q':
        case 'Q':
        case '\033':
            exit(0);
        default:
            break;
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int Highest(int** CITY, int N) {
    int High = 0;
    for(int i=0; i<N; i++) {
        if(CITY[i][0] > High) {
            High = CITY[i][0];
        }
        if(CITY[i][1] > High) {
            High = CITY[i][1];
        }
    }
    return High;
}

void MakeDisplayPosition(int** CITY, int N) {
    DispCITY = (double **)malloc(sizeof(double *) * N);
    for (int i = 0; i < N; i++)
    {
        DispCITY[i] = (double *)malloc(sizeof(double) * 2);
    }

    int h = Highest(CITY, N);
    SIZE = N;
    for(int i=0; i<N; i++) {
        DispCITY[i][0] = 1.8 * ((double)CITY[i][0] / h) - 0.9;
        DispCITY[i][1] = 1.8 * ((double)CITY[i][1] / h) - 0.9;
    }
}

void showTSP::showCity(int argc, char** argv, int* tour, int color) {
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    TOUR = tour;
    MakeDisplayPosition(CITY, N);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}