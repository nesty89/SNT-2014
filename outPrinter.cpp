#include "sim.hpp"

outPrinter::outPrinter(string fileName, graph* g, loader *l){
    this->fileName = fileName;
    this->g = g;
    this->l = l;
}

void outPrinter::printRes(){
    ofstream out;
    ofstream out2;
    string name2;
    string name = this->fileName;
    name += ".";
    name += this->g->problem;
    
    if(this->g->problem == "p2p"){
        name2 = name;
        name2 += ".q.res";
        out2.open(name2);
        name += ".p";
    }
    name += ".res";
    out.open(name.c_str());
    if (this->g->problem == "ss"){
        out << "c problem single source, solver xpavlu06\n";
        out << "p res sp ss xpavlu06\n";
        out << "c\n";
        out << "c graph and specification files\n";
        out << "f ";
        out << this->l->graphFile;
        out << " "; 
        out << this->l->sourceFile; 
        out << "\n";
        out << "c\n";
    } else if (this->g->problem == "p2p"){
        out << "c problem point to point, solver xpavlu06\n";
        out2 << "c problem point to point, solver xpavlu06\n";
        out << "p res sp p2p xpavlu06\n";
        out2 << "p res sp p2p xpavlu06\n";
        out << "c\n";
        out2 << "c\n";
        out << "c graph file\n";
        out2 << "c graph file\n";
        out << "f ";
        out2 << "f ";
        out << this->l->graphFile;
        out2 << this->l->graphFile;
        out << "\n";
        out2 << "\n";
        out << "c\n";
        out2 << "c\n";
    } else if (this->g->problem == "ncd"){
        out << "c problem negative cycle detection, solver xpavlu06\n";
        out << "p res sp ncd xpavlu06\n";
        out << "c\n";
        out << "c graph file\n";
        out << "f ";
        out << this->l->graphFile;
        out << "\n";
        out << "c\n";
    }
   
    out << "c number of nodes, edges, min weight and max weight\n";
    out << "g ";
    out << this->g->nodesNum;
    out << " ";
    out << this->g->edgeNum;
    out << " ";
    out << this->g->minw;
    out << " ";
    out << this->g->maxw;
    out << "\n";
    out << "c\n";
    out << "c average time per ss computation on ";
    out << this->l->graphFile;
    out << " in msec\n";
    out << "t ";
    float t = 0;
    for(int i = 0; i < this->g->times.size(); i++){
        t += this->g->times[i];
    }
    t /=  this->g->times.size();
    out << t;
    if(this->g->problem == "p2p"){
    out2 << "c\nc number of nodes, edges, min weight and max weight\n";
    out2 << "g ";
    out2 << this->g->nodesNum;
    out2 << " ";
    out2 << this->g->edgeNum;
    out2 << " ";
    out2 << this->g->minw;
    out2 << " ";
    out2 << this->g->maxw;
    out2 << "\n";
    out2 << "c\n";
    out2 << "c average time per ss computation on ";
    out2 << this->l->graphFile;
    out2 << " in msec\n";
    out2 << "t ";
    out2 << t;
    out2.close();
    }
    out.close();
}

void outPrinter::printCheck(){
    ofstream out;
    string name = this->fileName;
    name += ".";
    name += this->g->problem;
    name += ".chk";
    out.open(name.c_str());
    string line;
    if(this->g->problem == "ss"){
        out << "c problem single source, solver xpavlu06\n";
        out << "p chk sp ss xpavlu06\n";
        out << "c\n";
        out << "c graph and specification files\n";
        out << "f ";
        out << this->l->graphFile;
        out << " ";
        out << this->l->sourceFile;
        out << "\n";
        out << "c\n";
    } else if(this->g->problem == "p2p"){
        out << "c problem point to point, solver xpavlu06\n";
        out << "p chk sp p2p xpavlu06\n";
        out << "c\n";
        out << "c graph file\n";
        out << "f ";
        out << this->l->graphFile;
        out << "\n";
        out << "c\n";
        
    } else if(this->g->problem == "ncd"){
        out << "c problem negative cycle detection, solver xpavlu06\n";
        out << "p chk sp ncd xpavlu06\n";
        out << "c\n";
        out << "c graph file\n";
        out << "f ";
        out << this->l->graphFile;
        out << "\n";
        out << "c\n";
    }
    
    out << "c number of nodes, edges, min weight and max weight\n";
    out << "g ";
    out << this->g->nodesNum;
    out << " ";
    out << this->g->edgeNum;
    out << " ";
    out << this->g->minw;
    out << " ";
    out << this->g->maxw;
    out << "\n";
    out << line;
    out << "c\n";
    if(this->g->problem == "ss"){
        out << "c negative cycle detection - 1 if there is cycle, 0 otherwise \n";
        out << "D ";
        out << this->g->cycle;
        out << "\n";
        out << "c\n";
        if (this->g->cycle == 0){
            out <<  "c sums modulo 2^62 of distances from each source\n";
            for (int i = 0; i < this->g->sums.size(); i++){
                out << "d ";
                out << this->g->startNodes[i].id;
                out << " ";
                out << this->g->sums[i];
                out << "\n";
            }
        } else {
            out << "c no d lines since there is a negative-weight cycle";
        }
    } else if(this->g->problem == "p2p"){
        out << "c distances from source to destination node";
        for(int i = 0; i < this->g->startNodes.size(); i++){
            out << "\nd ";
            out << this->g->startNodes[i].id;
            out << " ";
            out << this->g->endNodes[i].id;
            out << " ";
            out << this->g->sums[i];
        }
        
        
    } else if(this->g->problem == "ncd"){
        out << "c negative cycle detection - 1 if there is cycle, 0 otherwise \n";
        out << "D ";
        out << this->g->cycle;
    }
    out.close();
}
