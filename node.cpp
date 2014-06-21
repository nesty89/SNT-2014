#include "sim.hpp"

node::node(int id){
    this->id = id;
    this->init();
}

void node::init(){
    this->d = LLONG_MAX;
    this->prev = NULL;
}
