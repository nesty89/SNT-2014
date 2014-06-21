#include "sim.hpp"

void graph::addEdge(int u, int v, int w){
    edge e;
    e.u = &nodes[u-1];
    e.v = &nodes[v-1];
    e.w = w;
    if(this->maxw < w){
        this->maxw = w;
    }
    if(this->minw > w){
        this->minw = w;
    }
    this->edges.push_back(e);
}

/*
 * vytvori neinicializovane uzly pouze id
 */
void graph::nodesVector(){
    for (int i = 0; i < this->nodesNum; i++){
        node n(i+1); 
        this->nodes.push_back(n);
    }
}

void graph::addCoords(int id, int x, int y){
    this->nodes[id-1].x = x;
    this->nodes[id-1].y = y;
    
}

/*
 * nastaneni promennych v uzlech na vychozi hodnoty 
 */
void graph::graphNodesInit(node *s){
    for(int i = 0; i < this->nodesNum; i++){
        this->nodes[i].init();
    }
    this->nodes[s->id - 1].d = 0;    
}

/*
 * relaxace hran 
 */
void graph::relax(node *u, node *v, int w){
    if(v->d - w > u->d ){
        v->d = u->d + w;
        v->prev = u;
    }
}

/* algoritmus Bellman-Ford detekce nejkratsich cest
 * true - neobsahuje zaporny cyklus 
 * false - obsahuke zaporny cyklus
 */
bool graph::bellman_ford(node *s){
    this->graphNodesInit(s);
    
    for(int i = 0; i < this->nodesNum; i++){
        for(int j = 0; j < this->edgeNum; j++){
            this->relax(this->edges[j].u,this->edges[j].v,this->edges[j].w);
        }
    }
    return true;
}

void graph::singleSource(){
    clock_t start, end;
   
    for(int i = 0; i < this->startNodes.size(); i++){
        start = clock();
        
        if(this->bellman_ford(&this->startNodes[i])){
            this->cycle = 0;
            this->countDistances(&this->nodes[startNodes[i].id -1]);
        }
        else {
            this->cycle = 1;
        }
              
        end = (double)(clock() - start)*1000/CLOCKS_PER_SEC;
        this->times.push_back(end);
    }
}

void graph::pointToPoint(){
    clock_t start, end;
    for(int i = 0; i < this->startNodes.size(); i++){
        start = clock();
        if(this->bellman_ford(&this->startNodes[i])){
            this->cycle = 0;
        }
        else {
            this->cycle = 1;
        }
        this->countDistances(&this->nodes[this->startNodes[i].id -1],&this->nodes[this->endNodes[i].id -1]);
        end = (float)(clock() - start)*1000/CLOCKS_PER_SEC;
        this->times.push_back(end);
    }
}



void graph::negativeCycleDetection(){
    clock_t start, end;
    start = clock();
    if(this->bellman_ford(&this->nodes[0])){
        this->cycle = 0;
    }
    else {
        this->cycle = 1;
    }
    end = (float)(clock() - start)*1000/CLOCKS_PER_SEC;
    this->times.push_back(end);
    
}

void graph::start(){
    if(this->problem == "ss"){
        this->singleSource();
    } else if(this->problem == "p2p"){
        this->pointToPoint();
    } else if(this->problem == "ncd"){
        this->negativeCycleDetection();
    } else {
        cerr << "neznamy problem: " << this->problem << endl;
    }
}

void graph::countDistances(node *u){
    long long sum = 0;
    int x, y;
    for( int i = 0; i < this->nodesNum; i++){
        if(this->nodes[i].d == LLONG_MAX){
            continue;
        }
        node *t = &this->nodes[i];
        while(t->prev != NULL){
            x = t->x - t->prev->x;
            y = t->y - t->prev->y;
            sum += (long long)sqrt(x*x + y*y) % LLONG_MAX;
            t = t->prev;
        }
    }
    this->sums.push_back(sum);
}

void graph::countDistances(node *u,node *v){
    long long sum = 0;
    int x,y;
    node *t = v;
    while(t->prev != NULL){
        x = t->x - t->prev->x;
        y = t->y - t->prev->y;
        sum += (long long)sqrt(x*x + y*y) % LLONG_MAX;
        t = t->prev;
    }
    this->sums.push_back(sum);
}