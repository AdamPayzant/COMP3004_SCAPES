#include "ReadStmt.h"

ReadStmt::ReadStmt(Program *p) {
    master = p;
}

ReadStmt::~ReadStmt() {
    delete(o1);
}

void ReadStmt::compile(std::string &line) {
    std::string operand = line.substr(4, line.size()-4);
    std::vector<Identifier*> *ids;
    master->getIds(ids);

    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(operand) == 0) {
            o1 = new Operand(*iter);
            return;
        }
    }
    // Make an error case here perhaps
}

void ReadStmt::run() {

}