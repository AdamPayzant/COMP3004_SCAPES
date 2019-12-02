
#include "JMoreStmt.h"
#include "../Program.h"

JMoreStmt::JMoreStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "JMoreStmt";
}

JMoreStmt::~JMoreStmt() {
    delete(label);
}

void JMoreStmt::compile(std::string &line) {
    // Syntax: "jmr <destination label>"
    target = line.substr(3, line.size() - 4);
}

void JMoreStmt::run() {
    if(master->getCFlag() == 1) {
        master->changeStmt(target);
    }
}

std::string JMoreStmt::getName() {
  std::string n = "JMoreStmt";
  return(n);
}

Operand* JMoreStmt::getOperand1()
{
    return this->o1;
}

Operand* JMoreStmt::getOperand2()
{
    return this->o2;
}

Label* JMoreStmt::getLabel()
{
    return this->label;
}

void JMoreStmt::setLabel(Label *l) {
  label = l;
};
