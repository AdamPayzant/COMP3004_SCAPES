#include "CompStmt.h"

CompStmt::CompStmt(Program *p) {
    master = p;
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}

void CompStmt::compile(std::string &line) {
    
}

void CompStmt::run() {
    
}