
#include "JMoreStmt.h"

JMoreStmt::JMoreStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
}

JMoreStmt::~JMoreStmt() {
    delete(label);
}

void JMoreStmt::compile(std::string &line) {
    // Syntax: "jmr <destination label>"
    // Nothing to do here for now
}

void JMoreStmt::run() {
    if(master->getCFlag() == 1) {
        Label *l;
        o1->getID(l);
        master->changeStmt(l);
    }
}

std::string JMoreStmt::getName() {
  std::string n = "JMoreStmt";
  return(n);
}