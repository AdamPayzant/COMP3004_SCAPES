
#include "DeclArrStmt.h"
#include "../Program.h"

DeclArrStmt::DeclArrStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "DeclArrStmt";
}

void DeclArrStmt::compile(std::string &line){
    // TODO
}

void DeclArrStmt::run(){
    ArrayVariable *temp = (ArrayVariable *) o1->getIDPtr();
    temp->create(o2->getVal());
} 

std::string DeclArrStmt::getName() {
  std::string n = "DeclArrStmt";
  return(n);
}