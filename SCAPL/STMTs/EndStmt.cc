
#include "EndStmt.h"
#include "../Program.h"

EndStmt::EndStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "EndStmt";
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
