
#include "EndStmt.h"

EndStmt::EndStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
}

EndStmt::~EndStmt() {
    // No Pointers to delete
}

void EndStmt::compile(std::string &name) {
    // Doesn't have anything in the line to consider
}

void EndStmt::run() {

}

std::string EndStmt::getName() {
  std::string n = "EndStmt";
  return(n);
}

Operand* EndStmt::getOperand1()
{
    return this->o1;
}


Operand* EndStmt::getOperand2()
{
    return this->o2;
}

Label* EndStmt::getLabel()
{
    return this->label;
}


void EndStmt::setLabel(Label *l) {
  label = l;
};
