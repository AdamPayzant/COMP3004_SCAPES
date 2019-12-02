
#include "EndStmt.h"
#include "../Program.h"

EndStmt::EndStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "EndStmt";
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
