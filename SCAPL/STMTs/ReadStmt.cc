
#include "ReadStmt.h"
#include "../Program.h"

ReadStmt::ReadStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "ReadStmt";
}

ReadStmt::~ReadStmt() {
    delete(o1);
}

void ReadStmt::compile(std::string &line) {
    int i;
    std::vector<Identifier*> *ids = master->getIds();

    if(line[4] == '$') {
        // Do the array add-y thing
    }
    else {
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(4, i - 4)) == 0) {
                o1 = new Operand(*iter);
            }
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
