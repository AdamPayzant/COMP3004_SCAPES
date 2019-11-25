
#include "AddStmt.h"

AddStmt::AddStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "AddStmt";
}


AddStmt::~AddStmt() {
    delete(o1);
    delete(o2);
}


void AddStmt::compile(std::string &line) {
    // Syntax: add <o1> <o2>
    int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[5] == ' ') {
            break;
        }
    }
    if(isdigit(line[4])) {
        int v = std::stoi(line.substr(4, i - 4));
        o1 = new Operand(v);
    }
    else {
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(4, i - 4)) == 0) {
                o1 = new Operand(*iter);
            }
        }
    }

    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(line.substr(i, line.size() - i - 1)) == 0) {
            o2 = new Operand(*iter);
        }
    }
}


void AddStmt::run() {
  // get operands
  // add  number 2 to 1
  // set the value
    Variable *des = o1->getIDPtr();
    des->setVal(o1->getVal()+o2->getVal());

}


std::string AddStmt::getName() {
  std::string n = "AddStmt";
  return(n);
}

Operand* AddStmt::getOperand1()
{
    return this->o1;
}


Operand* AddStmt::getOperand2()
{
    return this->o2;
}

Label* AddStmt::getLabel()
{
    return this->label;
}


void AddStmt::setLabel(Label *l) {
  label = l;
}
