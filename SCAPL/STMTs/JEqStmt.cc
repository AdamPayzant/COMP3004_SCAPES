#include "JEqStmt.h"
#include "../Program.h"


JEqStmt::JEqStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "JEqStmt";
}

void JEqStmt::compile(std::string &line) {
    // Syntax: jeq <target label>
    std::string target = line.substr(3, line.size() - 4);
    o1 = new Operand(master->getID(target));
}

void JEqStmt::run() {
    if(master->getCFlag() == 0) {
        master->changeStmt((Label *) o1->getIDPtr());
    }
}
