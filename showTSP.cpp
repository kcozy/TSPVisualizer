#include "showTSP.h"

#include <cstdlib>

#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

int* r;
double** dc;
int n;

showTSP::showTSP(int n, int** city) {
    NUMBEROFCITIES = n;
    CITIES = new int*[NUMBEROFCITIES];
    DispCITIES = new double*[NUMBEROFCITIES];
    for(int i=0; i<NUMBEROFCITIES; i++) {
        CITIES[i] = new int[2];
        DispCITIES[i] = new double[2];
    }
    CITIES = city;

    ROUTE = new int[NUMBEROFCITIES];
}

showTSP::~showTSP() {
    for(int i=0; i<NUMBEROFCITIES; i++) {
        delete [] CITIES[i];
        delete [] DispCITIES[i];
    }
    delete [] CITIES;
    delete [] DispCITIES;
    delete [] ROUTE;
}

static void keyboard(unsigned char key, int x, int y)
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

void showTSP::initGL(int argc, char** argv) {
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);

    glutKeyboardFunc(keyboard);
    init();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    // 描画開始
    glBegin(GL_POINTS);
    glColor3d(0.0, 0.0, 0.0);
    for(int i=0; i<n; i++) {
        glVertex2d(dc[i][0], dc[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 0.0, 0.0);
    for(int i=0; i<n; i++) {
        glVertex2d(dc[r[i]][0], dc[r[i]][1]);
    }
    glEnd();
    // 描画終了
    glFlush();
}

int showTSP::Highest() {
    int High = 0;
    for(int i=0; i<NUMBEROFCITIES; i++) {
        if(CITIES[i][0] > High) {
            High = CITIES[i][0];
        }
        if(CITIES[i][1] > High) {
            High = CITIES[i][1];
        }
    }
    return High;
}

void showTSP::MakeDisplayPosition() {
    int h = Highest();
    for(int i=0; i<NUMBEROFCITIES; i++) {
        DispCITIES[i][0] = 1.8 * ((double)CITIES[i][0] / h) - 0.9;
        DispCITIES[i][1] = 1.8 * ((double)CITIES[i][1] / h) - 0.9;
    }
}

void showTSP::showCity(int* route, int color) {
    ROUTE = route;
    r = route;
    n = NUMBEROFCITIES;
    MakeDisplayPosition();
    dc = DispCITIES;

    // OpenGL
    glutDisplayFunc(display);
    glutMainLoop();
}