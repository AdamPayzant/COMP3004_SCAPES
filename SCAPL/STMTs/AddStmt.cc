
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
        Literal *temp = new Literal(v);
        o1 = new Operand(temp);
    }
    else if(line[4] == '$') {
        // Do the array add-y thing
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

    if(line[i+1] == '$') {
        // Array Case
    }
    else {
        // Variable
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(i, line.size() - i - 1)) == 0) {
                o2 = new Operand(*iter);
            }
        }
    }
}


void AddStmt::run() {
  // get operands
  // add  number 2 to 1
  // set the value
    IntegerVariable *des = (IntegerVariable *) o1->getIDPtr();
    int val = o1->getVal() + o2->getVal();
    des->setVal(val);
}

std::string AddStmt::getName() {
  std::string n = "AddStmt";
  return(n);
}