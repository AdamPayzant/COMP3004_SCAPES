
#include "JEqStmt.h"
#include "../Program.h"

void JEqStmt::compile(std::string &line) {

}

void JEqStmt::run() {
  if(master->getCFlag() == 0) {
        Label *l;
        o1->getID(l);
        master->changeStmt(l);
    }
}


std::string JEqStmt::getName() {
  std::string n = "JEqStmt";
  return(n);
}

Operand* JEqStmt::getOperand1()
{
    return this->o1;
}


Operand* JEqStmt::getOperand2()
{
    return this->o2;
}

Label* JEqStmt::getLabel()
{
    return this->label;
}


void JEqStmt::setLabel(Label *l) {
  label = l;
};
