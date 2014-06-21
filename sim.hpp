#ifndef SIM_HPP
#define	SIM_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include <ctime>

using namespace std;

class node{
public:
    int id;
    long x;
    long y;
    node * prev;
    long long d;
    node(int id);
    void init();
    
};

class edge{
public:
    node *u;
    node *v;
    int w;
    edge(node *u, node *v, int w);
    edge();
};

class graph {
public:
    vector<float> times;
    vector<node> startNodes;
    vector<node> endNodes;
    vector<node> nodes;
    vector<edge> edges;
    vector<long long> sums;
    string problem;
    int edgeNum;
    int nodesNum;
    int minw;
    int maxw;
    int cycle;
    
    void addEdge(int u, int v, int w);
    void nodesVector();
    void addCoords(int id, int x, int y);
    
    void relax(node *u, node *v, int w);
    void graphNodesInit(node *s);
    bool bellman_ford(node *s);
    
    void singleSource();
    void pointToPoint();
    void negativeCycleDetection();
    
    void countDistances(node *u);
    void countDistances(node *u, node *v);
    void start();
};

class loader {
public:

    char *sourceFile;
    char *graphFile;
    char *coordFile;
    graph *g;
    
    loader(char *sourceName, char * graphName, char *coordName, graph *g);
    loader(char * graphName, graph *g);
    void loadSource();
    void loadGraph();
    void loadCoord();
    string graphFileName();
};

class outPrinter{
private:
    string fileName;
    graph *g;
    loader *l;
    
public:
    outPrinter(string fileName, graph *g, loader *l);
    void printRes();
    void printCheck();
};

#endif	/* SIM_HPP */

