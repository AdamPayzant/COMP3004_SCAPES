#include "JumpStmt.h"

JumpStmt::JumpStmt(Program *p) {
    master = p;
}

JumpStmt::~JumpStmt() {
    delete(label);
}

void JumpStmt::compile(std::string &line) {
    // Syntax: "jmp <Destination Label>"
    // Nothing to do here for now
}

void JumpStmt::run() {
    
}