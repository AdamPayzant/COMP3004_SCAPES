
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
    int i = line.size() - 1;
    std::vector<Identifier*> *ids = master->getIds();

    if(isdigit(line[4])) {
        // Literal Case
        int v = std::stoi(line.substr(5, i - 4));
        Literal *temp = new Literal(v);
        o1 = new Operand(temp);
    }
    else if(line[4] == '$') {
        // Array Case
        std::string arrName;
        std::string accessName;
        int j;
        for(j = 6; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(5, j - 5);
            }
        }
        accessName = line.substr(j + 1, i - j - 1);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName);
                break;
            }
        }
    }
    else {
        // Variable case
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(5, i - 4)) == 0) {
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
    std::string val = std::to_string(o1->getVal());
    master->addPrint(val);
}


std::string PrintStmt::getName() {
  std::string n = "PrintStmt";
  return(n);
}