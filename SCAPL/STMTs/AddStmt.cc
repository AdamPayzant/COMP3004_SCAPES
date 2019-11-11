#include "AddStmt.h"

AddStmt::AddStmt(Program *m) {
    master = m;
}

AddStmt::~AddStmt() {
    delete(o1);
    delete(o2);
}

void AddStmt::compile(std::string line) {
    
}

void AddStmt::run() {

}