
#include "DeclIntStmt.h"
#include "./../Program.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    master = p;
}

DeclIntStmt::~DeclIntStmt() {

}
/**
* Compiles and makes the objects for the compile instruction
**/
bool DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);
    for(int i =0; i < name.size(); i++) {
        if(name.at(i) == ' ') {
            return{false};
        }
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ids->push_back(new Variable(name));

    return(true);
}

void DeclIntStmt::run() {

}

std::string DeclIntStmt::getName() {
  std::string n = "DeclIntStmt";
  return(n);
}

Operand* DeclIntStmt::getOperand1()
{
    return this->o1;
}


Operand* DeclIntStmt::getOperand2()
{
    return this->o2;
}

Label* DeclIntStmt::getLabel()
{
    return this->label;
}


void DeclIntStmt::setLabel(Label *l) {
  label = l;
};
