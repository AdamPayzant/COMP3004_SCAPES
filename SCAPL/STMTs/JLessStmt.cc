
#include "JLessStmt.h"
#include "../Program.h"

void JLessStmt::compile(std::string &line) {

}

void JLessStmt::run() {
  if(master->getCFlag() == -1) {
        Label *l;
        o1->getID(l);
        master->changeStmt(l);
    }
}


std::string JLessStmt::getName() {
  std::string n = "JLessStmt";
  return(n);
}

Operand* JLessStmt::getOperand1()
{
    return this->o1;
}


Operand* JLessStmt::getOperand2()
{
    return this->o2;
}

Label* JLessStmt::getLabel()
{
    return this->label;
}


void JLessStmt::setLabel(Label *l) {
  label = l;
};
