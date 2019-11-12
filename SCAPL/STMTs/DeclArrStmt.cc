
#include "DeclArrStmt.h"
#include "../Program.h"

std::string DeclArrStmt::getName() {
  std::string n = "DeclArrStmt";
  return(n);
}

Operand* DeclArrStmt::getOperand1()
{
    return this->o1;
}


Operand* DeclArrStmt::getOperand2()
{
    return this->o2;
}

Label* DeclArrStmt::getLabel()
{
    return this->label;
}


void DeclArrStmt::setLabel(Label *l) {
  label = l;
};
