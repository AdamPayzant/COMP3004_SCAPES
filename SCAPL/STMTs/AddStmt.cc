
#include "AddStmt.h"

AddStmt::AddStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
}


AddStmt::~AddStmt() {
    delete(o1);
    delete(o2);
}


void AddStmt::compile(std::string &line) {



}


void AddStmt::run() {
  // get operands
  // add  number 2 to 1
  // set the value
  Variable *des;
  o1.setId(destination)
 dest->setValue(o1.getVal()+o2.getVal());
}


std::string AddStmt::getName() {
  std::string n = "AddStmt";
  return(n);
}

Operand* AddStmt::getOperand1()
{
    return this->o1;
}


Operand* AddStmt::getOperand2()
{
    return this->o2;
}

Label* AddStmt::getLabel()
{
    return this->label;
}


void AddStmt::setLabel(Label *l) {
  label = l;
};
