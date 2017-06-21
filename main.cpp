#include <iostream>
#include "showTSP.h"

using namespace std;

int main(int argc, char** argv) {
    showTSP *s = new showTSP();
    s -> readFile(argc, argv);
    cout << s->GetNUMBEROFCITES() << endl;
}