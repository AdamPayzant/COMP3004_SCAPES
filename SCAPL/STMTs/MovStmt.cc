
#include "MovStmt.h"
#include "../Program.h"

MovStmt::MovStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "MovStmt";
}

MovStmt::~MovStmt(){

}

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

void MovStmt::compile(std::string &line) {
    return;
}

void MovStmt::run(){
  Variable *des;
  /*
  o1->setID(des)
 dest->setValue(o2.getVal());
 */

}
