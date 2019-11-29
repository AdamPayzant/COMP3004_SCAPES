
#include "PrintStmt.h"
#include "../Program.h"

PrintStmt::PrintStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "PrintStmt";
}

PrintStmt::~PrintStmt() {
    delete(o1);
}

void PrintStmt::compile(std::string &line) {
    int i;
    std::vector<Identifier*> *ids = master->getIds();

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
}

void PrintStmt::run() {
    /*
Std::String s;

s=std::to_string(o1.getValue());
master->addPrint(s);
*/
}


std::string PrintStmt::getName() {
  std::string n = "PrintStmt";
  return(n);
}