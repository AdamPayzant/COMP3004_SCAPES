#include "DeclIntStmt.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    master = p;
}

DeclIntStmt::~DeclIntStmt() {
    
}

void DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);
    std::vector<Identifier*> *ids;
    master->getIds(ids);
    ids->push_back(new Variable(name));
}

void DeclIntStmt::run() {

}