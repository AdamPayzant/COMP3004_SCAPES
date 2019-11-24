
#include "MovStmt.h"

std::string MovStmt::getName() {
  std::string n = "MovStmt";
  return(n);
}

Operand* MovStmt::getOperand1()
{
    return this->o1;
}


Operand* MovStmt::getOperand2()
{
    return this->o2;
}

Label* MovStmt::getLabel()
{
    return this->label;
}

void MovStmt::compile(std::string &line) {
    // Syntax: mov <source> <destination>

    int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[5] == ' ') {
            break;
        }
    }
    if(std::isdigit(line[4])) {
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

void MovStmt::setLabel(Label *l) {
  label = l;
};
void MovStmt::run(){
  Variable *des;
  /*
  o1->setID(des)
 dest->setValue(o2.getVal());
 */

}
