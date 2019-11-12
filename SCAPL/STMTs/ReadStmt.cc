
#include "ReadStmt.h"
#include "../Program.h"

ReadStmt::ReadStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
}

ReadStmt::~ReadStmt() {
    delete(o1);
}

void ReadStmt::compile(std::string &line) {
    std::string operand = line.substr(4, line.size()-4);
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    
    // Memory issues is created here
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(operand) == 0) {
            o1 = new Operand(*iter);
            return;
        }
    }
}

void ReadStmt::run() {

}



std::string ReadStmt::getName() {
  std::string n = "ReadStmt";
  return(n);
}

Operand* ReadStmt::getOperand1()
{
    return this->o1;
}


Operand* ReadStmt::getOperand2()
{
    return this->o2;
}

Label* ReadStmt::getLabel()
{
    return this->label;
}


void ReadStmt::setLabel(Label *l) {
  label = l;
};
