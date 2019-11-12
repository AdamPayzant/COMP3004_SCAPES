
#include "JumpStmt.h"
#include "../Program.h"

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
            return{false};
        }
    }

    std::vector<Identifier*> *ids = master->getIds();
    for(int i = 0; i < ids->size(); i++) {
        std::string n; 
        ids->at(i)->getName(n);
        if(n.compare(name) == 0) {
            label = ids->at(i);
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
