
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
  // TODO: REDO
  // Syntax: dca <Name> <Size>
  // O1 is going to store the array, it's gross I know but it will make things more effecient
  // O2 stores the size
  /*
  std::string name = line.substr(4, line.size()-4);
  std::vector<Identifier*> *ids;
  ids = master->getIds();
  ids->push_back(new ArrayVariable(name));
  */

    int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[i] == ' ') {
            break;
        }
    }
    std::string name = line.substr(3, i - 4);
    ArrayVariable *temp;
    ids->push_back(temp);
    o1 = new Operand(temp);

    if(std::isdigit(line[i+1])) {
        o2 = new Operand(stoi(line.substr(i, line.size() - 1 - i)));
    }
    else {
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(i, line.size() - i - 1)) == 0) {
                o2 = new Operand(*iter);
            }
        }
    }
}

void DeclArrStmt::run(){
    ArrayVariable *temp = (ArrayVariable *) o1->getIDPtr();
    temp->create(o2->getVal());
} 

std::string DeclArrStmt::getName() {
  std::string n = "DeclArrStmt";
  return(n);
}