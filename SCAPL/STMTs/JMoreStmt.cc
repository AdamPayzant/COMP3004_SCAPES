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
    std::string target = line.substr(3, line.size() - 4);
    o1 = new Operand(master->getID(target));
}

void JMoreStmt::run() {
    if(master->getCFlag() == 1) {
        master->changeStmt((Label *) o1->getIDPtr());
    }
}
