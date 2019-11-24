
#include "JLessStmt.h"

void JLessStmt::compile(std::string &line) {

}

void JLessStmt::run() {
  if(master->getCFlag() == -1) {
        Label *l;
        o1->getID(l);
        master->changeStmt(l);
    }
}


std::string JLessStmt::getName() {
  std::string n = "JLessStmt";
  return(n);
}
