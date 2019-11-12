#include "DeclIntStmt.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    master = p;
}

DeclIntStmt::~DeclIntStmt() {

}
/**
* Compiles and makes the objects for the compile instruction
**/
void DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);
    while(name.at(0) == ' ') {
        line.erase(name.begin());
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ids->push_back(new Variable(name));
}

void DeclIntStmt::run() {

}
