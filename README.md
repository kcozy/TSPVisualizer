# TSPVisualizer
- Visualize Traveling Salesman Problem(TSP) & Import TSP from file
- Using C++ with OpenGL

## File Format
- *.tsp
- Use file in [TSPLIB](https://www.iwr.uni-heidelberg.de/groups/comopt/software/TSPLIB95/)
- Somefiles are not According to the format...(?)

## Compile Command
in OS X
```bash
g++ main.cpp showTSP.cpp readTSPLIB.cpp -framework GLUT -framework OpenGL
```
in Others, please check how to compile OpenGL sources.

## Run
If use "a280.tsp" file
```bash
./a.out a280.tsp
```
