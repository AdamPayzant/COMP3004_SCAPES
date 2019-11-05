#include "JumpStmt.h"

JumpStmt::JumpStmt(Program *p) {
    master = p;
}

JumpStmt::~JumpStmt() {
    delete(label);
}

void JumpStmt::compile(std::string &line) {

}

void JumpStmt::run() {
    
}