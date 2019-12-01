#include "DeclIntStmt.h"
#include "../Program.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "DeclIntStmt";
}

DeclIntStmt::~DeclIntStmt() {

}


void DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);

    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ids->push_back(new IntegerVariable(name));
}


void DeclIntStmt::run() {

}
