#include "DeclIntStmt.h"

DeclIntStmt::DeclIntStmt(Program *p) {

}

DeclIntStmt::~DeclIntStmt() {
    // TODO Delete Operand
}

void DeclIntStmt::compile(std::string &line) {
    std::string name = line.substr(4, line.size()-4);
}

void DeclIntStmt::run() {

}