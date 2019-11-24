
#include "PrintStmt.h"
#include "../Program.h"

PrintStmt::PrintStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "PrintStmt";
}

PrintStmt::~PrintStmt() {
    delete(o1);
}

void PrintStmt::compile(std::string &line) {
    std::string operand = line.substr(4, line.size()-4);
    while(operand.at(0) == ' ') {
        line.erase(operand.begin());
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();

    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(operand) == 0) {
            o1 = new Operand(*iter);
            return;
        }
    }
    // Make an error case here perhaps
}

void PrintStmt::run() {
    /*
Std::String s;

s=std::to_string(o1.getValue());
master->addPrint(s);
*/
}


std::string PrintStmt::getName() {
  std::string n = "PrintStmt";
  return(n);
}

Operand* PrintStmt::getOperand1()
{
    return this->o1;
}


Operand* PrintStmt::getOperand2()
{
    return this->o2;
}

Label* PrintStmt::getLabel()
{
    return this->label;
}


void PrintStmt::setLabel(Label *l) {
  label = l;
};
