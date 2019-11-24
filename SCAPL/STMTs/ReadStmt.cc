
#include "ReadStmt.h"

ReadStmt::ReadStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
}

ReadStmt::~ReadStmt() {

}

void ReadStmt::compile(std::string &line) {
    // Syntax: rdi <o1>
    std::string operand = line.substr(4, line.size()-4);
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();

    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(operand) == 0) {
            o1 = new Operand(*iter);
            return;
        }
    }
}

void ReadStmt::run() {
 // get varible 
 //  std:;in stuff
 // set it to the value

}



std::string ReadStmt::getName() {
  std::string n = "ReadStmt";
  return(n);
}