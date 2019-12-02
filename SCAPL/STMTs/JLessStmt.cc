
#include "JLessStmt.h"
#include "../Program.h"

JLessStmt::JLessStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "JLessStmt";
}

void JLessStmt::compile(std::string &line) {
    // Syntax: jls <target label>
    target = line.substr(3, line.size() - 4);
}

void JLessStmt::run() {
  if(master->getCFlag() == -1) {
        master->changeStmt(target);
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
