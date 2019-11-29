
#include "CompStmt.h"
#include "../Program.h"

CompStmt::CompStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "CompStmt";
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}


void CompStmt::compile(std::string &line) {
    // TODO: Either operand can be a literal or array value
    // Syntax is "cmp <first value> <second value>"
        int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[5] == ' ') {
            break;
        }
    }
    if(isdigit(line[4])) {
        int v = std::stoi(line.substr(4, i - 4));
        Literal *temp = new Literal(v);
        o1 = new Operand(temp);
    }
    else if(line[4] == '$') {
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


        int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[5] == ' ') {
            break;
        }
    }
    if(isdigit(line[i+1])) {
        int v = std::stoi(line.substr(i, line.size() - i - 1));
        Literal *temp = new Literal(v);
        o2 = new Operand(temp);
    }
    else if(line[i+1] == '$') {
        // Do the array add-y thing
    }
    else {
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(i, line.size() - i - 1)) == 0) {
                o2 = new Operand(*iter);
            }
        }
    }
}


void CompStmt::run() {

}


std::string CompStmt::getName() {
  std::string n = "CompStmt";
  return(n);
}