#include "JMoreStmt.h"

JMoreStmt::JMoreStmt(Program *p) {
    master = p;
}

JMoreStmt::~JMoreStmt() {
    delete(label);
}

void JMoreStmt::compile(std::string &line) {

}

void JMoreStmt::run() {

}