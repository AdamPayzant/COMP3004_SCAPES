
#include "JumpStmt.h"
#include "../Program.h"


JumpStmt::JumpStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "JumpStmt";
}


JumpStmt::~JumpStmt() {
    delete(label);
}

void JumpStmt::compile(std::string &line) {
    // Syntax: "jmp <Destination Label>"
    // Nothing to do here for now
}


void JumpStmt::run() {
    Label *l;
    o1->getID(l);
    master->changeStmt(l);
}

std::string JumpStmt::getName() {
  std::string n = "JumpStmt";
  return(n);
}

Operand* JumpStmt::getOperand1()
{
    return this->o1;
}


Operand* JumpStmt::getOperand2()
{
    return this->o2;
}

Label* JumpStmt::getLabel()
{
    return this->label;
}


void JumpStmt::setLabel(Label *l) {
  label = l;
};
