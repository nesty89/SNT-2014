#include "sim.hpp"

edge::edge(node *u, node *v, int w){
    this->u = u;
    this->v = v;
    this->w = w;
}

edge::edge(){};
