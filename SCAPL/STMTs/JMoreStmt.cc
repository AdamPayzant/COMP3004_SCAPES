#include "JMoreStmt.h"

JMoreStmt::JMoreStmt(Program *p) {
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

}