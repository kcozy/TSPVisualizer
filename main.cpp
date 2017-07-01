#include <iostream>
#include <cstdlib>
#include <string>
#include "readTSPLIB.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

using namespace std;

int** CITIES;
int NUMBEROFCITIES;

int width, height;
double** DispCITIES;
int* CurrentRoute;
int* BestRoute;
double** Pheromones;
string BestLength;

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

void initMemory() {
    DispCITIES = new double*[NUMBEROFCITIES];
    Pheromones = new double*[NUMBEROFCITIES];
    for(int i=0; i<NUMBEROFCITIES; i++) {
        DispCITIES[i] = new double[2];
        Pheromones[i] = new double[NUMBEROFCITIES];
    }
    CurrentRoute = new int[NUMBEROFCITIES];
    BestRoute = new int[NUMBEROFCITIES];
}

int Highest() {
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

void MakeDisplayPosition() {
    int h = Highest();
    for(int i=0; i<NUMBEROFCITIES; i++) {
        DispCITIES[i][0] = 1.8 * ((double)CITIES[i][0] / h) - 0.9;
        DispCITIES[i][1] = 1.8 * ((double)CITIES[i][1] / h) - 0.9;
    }
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

void render_string(float x, float y, string const& str){
    float z = -1.0f;
    glRasterPos3f(x, y, z);
    for(int i=0; i<str.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);

    // Current Route
    glViewport(0 , height/2 , width/2 , height/2);
    glBegin(GL_POINTS);
    glColor3d(0.0, 0.0, 0.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[i][0], DispCITIES[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(1.0, 0.0, 0.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[CurrentRoute[i]][0], DispCITIES[CurrentRoute[i]][1]);
    }
    glEnd();

    // Best Route
    glViewport(width/2 , height/2 , width/2 , height/2);
    glBegin(GL_POINTS);
    glColor3d(0.0, 0.0, 0.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[i][0], DispCITIES[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(0.0, 0.0, 1.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[BestRoute[i]][0], DispCITIES[BestRoute[i]][1]);
    }
    glEnd();

    // Pheromones
    glViewport(0 , 0 , width/2 , height/2);
    glBegin(GL_POINTS);
    glColor3d(0.0, 0.0, 0.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[i][0], DispCITIES[i][1]);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3d(0.0, 1.0, 0.0);
    for(int i=0; i<NUMBEROFCITIES; i++) {
        glVertex2d(DispCITIES[i][0], DispCITIES[i][1]);
        for(int j=0; j<NUMBEROFCITIES; j++) {
            glVertex2d(DispCITIES[j][0], DispCITIES[j][1]);
        }
    }
    glEnd();

    // Texts
    glViewport(width/2 , 0 , width/2 , height/2);
    glColor3d(0.0, 0.0, 0.0);
    render_string(-0.9f, 0.0f, "Best Route : "+BestLength);

    // Line
    glViewport(0 , 0 , width , height);
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 0.0);
    glVertex2d(0, 1);
    glVertex2d(0, -1);
    glVertex2d(1, 0);
    glVertex2d(-1, 0);
    glEnd();

    // 描画終了
    glFlush();
}

void reshape(int w, int h) {
	width = w; height = h;
	display();
}

void update() {
    glutPostRedisplay();
}

void showRoute(int* route) {
    CurrentRoute = route;
}

void showBest(int* route) {
    BestRoute = route;
}

void showPheromones(double** pheromones) {
    Pheromones = pheromones;
}

void showText(double length) {
    char buff[numeric_limits<double>::max_exponent10
          + 6   // fixed precision (printf's default)
          + 3]; // '-' + '.' + NULL
    sprintf(buff, "%.2f", length);
    BestLength = buff;
}

void timer(int value) {
    // sample route

    shuffle<int>(CurrentRoute, NUMBEROFCITIES);
    BestRoute = CurrentRoute;
    showText(1.0);
    /* 画面を再描写 */
    glutPostRedisplay();
    /* 100ミリ秒後に再実行 */
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv) {
    // input from *.tsp
    readTSPLIB rtsp;
    rtsp.readFile(argc, argv);
    CITIES = rtsp.CITY;
    NUMBEROFCITIES = rtsp.NUMBEROFCITIES;

    initMemory();
    MakeDisplayPosition();

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(500, 500);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow("Show TSP");

    glutKeyboardFunc(keyboard);
    init();

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(update);

    // solve TSP here
    for(int i=0; i<NUMBEROFCITIES; i++) {
        CurrentRoute[i] = i+1;
    }
    CurrentRoute[NUMBEROFCITIES-1] = 0;

    glutTimerFunc(100, timer, 0);
    
    glutMainLoop();
}