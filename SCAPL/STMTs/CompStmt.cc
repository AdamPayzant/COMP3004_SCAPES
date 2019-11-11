#include "CompStmt.h"

CompStmt::CompStmt(Program *p) {
    master = p;
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}

void CompStmt::compile(std::string &line) {
    // Syntax is "cmp <first value> <second value>"
    std::string operand = line.substr(4, line.size()-4);
    std::string oone;
    std::string otwo;
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
    for(int i = 0; i < operand.size(); i++) {
        if(operand.at(i) == ' ') {
            oone = operand.substr(0, i);
            otwo = operand.substr(i+1, line.size()-i);
            break;
        }
    }
    
    std::vector<Identifier*> *ids;
    master->getIds(ids);
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(oone) == 0) {
            o1 = new Operand(*iter);
        }
        else if(temp.compare(otwo) == 0) {
            o2 = new Operand(*iter);
        }
    }
    // TODO: Create error case if one or both operands are unassigned
}

void CompStmt::run() {
    
}