#include "PrintStmt.h"

PrintStmt::PrintStmt(Program *p) {
    master = p;
}

PrintStmt::~PrintStmt() {
    delete(o1);
}

void PrintStmt::compile(std::string &line) {
    std::string operand = line.substr(4, line.size()-4);
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
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

void PrintStmt::run() {

}