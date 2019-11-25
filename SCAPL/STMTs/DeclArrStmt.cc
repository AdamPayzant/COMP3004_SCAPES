
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

std::string DeclArrStmt::getName() {
  std::string n = "DeclArrStmt";
  return(n);
}

Operand* DeclArrStmt::getOperand1()
{
    return this->o1;
}


Operand* DeclArrStmt::getOperand2()
{
    return this->o2;
}

Label* DeclArrStmt::getLabel()
{
    return this->label;
}


void DeclArrStmt::setLabel(Label *l) {
  label = l;
};
void DeclArrStmt::compile(std::string &line){
  // TODO: REDO
  // Syntax: dca <Name> <Size>
  std::string name = line.substr(4, line.size()-4);
  while(name.at(0) == ' ') {
      line.erase(name.begin());
  }
  std::vector<Identifier*> *ids;
  ids = master->getIds();
  ids->push_back(new Variable(name));
  // do we have to  maybe declaire a array in a different way if the subclasses are definied

}


void DeclArrStmt::run(){

}
