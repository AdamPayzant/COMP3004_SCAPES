
#include "DeclArrStmt.h"

std::string DeclArrStmt::getName() {
  std::string n = "DeclArrStmt";
  return(n);
}

void DeclArrStmt::compile(std::string &line){

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
