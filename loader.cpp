#include "sim.hpp"

loader::loader(char * sourceName, char *graphName, char *coordName, graph *g){
    this->sourceFile = sourceName;
    this->graphFile = graphName;
    this->coordFile = coordName;
    this->g = g;
}
loader::loader(char *graphName, graph *g){
    this->g = g;
    this->graphFile = graphName;
}

void loader::loadSource(){
    ifstream input;
    stringstream ss;
    input.open(this->sourceFile);
    string line;
    bool p = false;
    string aux, sp;
    int n, f, t;
    
    while(getline(input,line)){
        if(line[0] == 'c' || line == ""){
            continue;
        } else if(line[0] == 'p' && !p){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> aux >> sp >> g->problem >> n; 
            p = true;
        } else if(line[0] == 'q' && g->problem == "p2p"){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> f >> t;
            g->startNodes.push_back(g->nodes[f-1]);
            g->endNodes.push_back(g->nodes[t-1]);

        } else if (line[0] == 's' && g->problem == "ss"){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> f;
            g->startNodes.push_back(g->nodes[f-1]);
        } else {
            cerr << "chybny format "<< this->sourceFile << endl;
        }
    } 
    input.close();
}

void loader::loadCoord(){
    ifstream input;
    stringstream ss;
    input.open(this->coordFile);
    string line;
    bool p = false;
    string problem, aux;
    int id, x, y, coords;
    while(getline(input, line)){
        if(line[0] == 'c' || line == ""){
            continue;
        } else if (line[0] == 'p' && !p){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> problem >> coords ;
            p = true;
        } else if (line[0] == 'v'){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> id >> x >> y ;
            g->addCoords(id, x, y);
        } else {
            cerr << "chybny format "<< this->coordFile << endl;
        }
    }
    input.close();
}

void loader::loadGraph(){
    ifstream input;
    stringstream ss;
    input.open(this->graphFile);
    string line;
    bool p = false;
    string problem;
    int u, v, w;
    bool first = true;
    while(getline(input, line)){
        if(line[0] == 'c' || line == ""){
            continue;
        } else if( line[0] == 'p' && !p ){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >>  problem >> g->nodesNum >> g->edgeNum;
            g->nodesVector();
            p = true;
        } else if(line[0] == 'a'){
            line.erase(line.begin());
            ss.clear();
            ss.str("");
            ss << line;
            ss >> u >> v >> w;
            
            if(first){
                first = false;
                this->g->maxw = w;
                this->g->minw = w;
            }
            
            g->addEdge(u,v,w);
            
        } else {
            cerr << "chybny format "<< this->graphFile << endl;
        }
    }
    input.close();
}


 string loader::graphFileName(){
    string gr = this->graphFile;
    gr = gr.substr(0,gr.length() - 3);
    return gr.c_str();
}