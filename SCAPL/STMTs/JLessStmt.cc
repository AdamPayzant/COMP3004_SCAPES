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
    std::string target = line.substr(3, line.size() - 4);
    o1 = new Operand(master->getID(target));
}

void JLessStmt::run() {
    if(master->getCFlag() == -1) {
        master->changeStmt((Label *) o1->getIDPtr());
    }
}
