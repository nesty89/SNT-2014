#include "sim.hpp"

int main(int argc, char** argv) {

    graph g;
    loader *l;
    if(argc == 4){ // p2p ss
        l = new loader(argv[1], argv[2], argv[3], &g);
        l->loadGraph();
        l->loadSource(); 
        l->loadCoord();
    } else if(argc == 2){ // ncd
        l = new loader(argv[1], &g);
        l->loadGraph();
        g.problem = "ncd";
    } else {
        cerr << "chybny pocet parametru " << endl;
        return 1;
    }
    g.start();
    outPrinter *op = new outPrinter(l->graphFileName(),&g, l);
    op->printRes();
    op->printCheck();
    return 0;
}

