
#include "JEqStmt.h"

void JEqStmt::compile(std::string &line) {

}

void JEqStmt::run() {
  if(master->getCFlag() == 0) {
        Label *l;
        o1->getID(l);
        master->changeStmt(l);
    }
}


std::string JEqStmt::getName() {
  std::string n = "JEqStmt";
  return(n);
}