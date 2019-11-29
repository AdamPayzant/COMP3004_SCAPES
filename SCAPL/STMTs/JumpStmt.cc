
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
    target = line.substr(3, line.size() - 4);
}


void JumpStmt::run() {
    master->changeStmt(target);
}

std::string JumpStmt::getName() {
  std::string n = "JumpStmt";
  return(n);
}