
#include "JumpStmt.h"
#include "./../Program.h"

/**
* Constructor
* Parameters:
* -  sting repersenting the instruction
*
**/
JumpStmt::JumpStmt(Program *p) {
    master = p;
}

/**
* Destructor
**/
JumpStmt::~JumpStmt() {
    delete(label);
}
/**
* run function produces the result of the code
**/
bool JumpStmt::compile(std::string &line) {
    // Syntax: "jmp <Destination Label>"
    std::string name = line.substr(4, line.size()-4);
    for(int i =0; i < name.size(); i++) {
        if(name.at(i) == ' ') {
            return(false);
        }
    }

    std::vector<Identifier*> *ids = master->getIds();
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(name) == 0) {
            o1 = new Operand(*iter);
            return(true);
        }
    }
    return(false);
}
/**
* run function produces the result of the code
**/

void JumpStmt::run() {

}

std::string JumpStmt::getName() {
  std::string n = "JumpStmt";
  return(n);
}

Operand* JumpStmt::getOperand1()
{
    return this->o1;
}


Operand* JumpStmt::getOperand2()
{
    return this->o2;
}

Label* JumpStmt::getLabel()
{
    return this->label;
}


void JumpStmt::setLabel(Label *l) {
  label = l;
};
