
#include "DeclIntStmt.h"
#include "../Program.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
}

DeclIntStmt::~DeclIntStmt() {

}
/**
* Compiles and makes the objects for the compile instruction
**/
void DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);
    while(name.at(0) == ' ') {
        line.erase(name.begin());
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ids->push_back(new Variable(name));
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
