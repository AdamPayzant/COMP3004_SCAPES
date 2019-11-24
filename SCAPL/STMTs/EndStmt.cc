
#include "EndStmt.h"

EndStmt::EndStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
}

EndStmt::~EndStmt() {
    // No Pointers to delete
}

void EndStmt::compile(std::string &name) {
    // Doesn't have anything in the line to consider
}

void EndStmt::run() {

}

std::string EndStmt::getName() {
  std::string n = "EndStmt";
  return(n);
}
