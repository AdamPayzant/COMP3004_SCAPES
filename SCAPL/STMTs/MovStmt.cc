
#include "MovStmt.h"
#include "../Program.h"


std::string MovStmt::getName() {
  std::string n = "MovStmt";
  return(n);
}

Operand* MovStmt::getOperand1()
{
    return this->o1;
}


Operand* MovStmt::getOperand2()
{
    return this->o2;
}

Label* MovStmt::getLabel()
{
    return this->label;
}


void MovStmt::setLabel(Label *l) {
  label = l;
};
