
#include "CompStmt.h"
#include "../Program.h"

CompStmt::CompStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}


void CompStmt::compile(std::string &line) {
    // Syntax is "cmp <first value> <second value>"
    std::string operand = line.substr(4, line.size()-4);
    std::string oone;
    std::string otwo;
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
    for(int i = 0; i < operand.size(); i++) {
        if(operand.at(i) == ' ') {
            oone = operand.substr(0, i);
            otwo = operand.substr(i+1, line.size()-i);
            break;
        }
    }

    std::vector<Identifier*> *ids;
    ids = master->getIds();
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(oone) == 0) {
            o1 = new Operand(*iter);
        }
        else if(temp.compare(otwo) == 0) {
            o2 = new Operand(*iter);
        }
    }
    // TODO: Create error case if one or both operands are unassigned
}


void CompStmt::run() {

}


std::string CompStmt::getName() {
  std::string n = "CompStmt";
  return(n);
}

Operand* CompStmt::getOperand1()
{
    return this->o1;
}


Operand* CompStmt::getOperand2()
{
    return this->o2;
}

Label* CompStmt::getLabel()
{
    return this->label;
}


void CompStmt::setLabel(Label *l) {
  label = l;
};
