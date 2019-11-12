
#include "JMoreStmt.h"
#include "../Program.h"

/**
* Constructor
* Parameters:
* -  pointer to a program object
*
**/
JMoreStmt::JMoreStmt(Program *p) {
    master = p;
}
/**
* Destructor
**/
JMoreStmt::~JMoreStmt() {
    delete(label);
}
/**
* compile
* Parameters:
* -  String being the instruction
*
**/
bool JMoreStmt::compile(std::string &line) {
    // Syntax: "jmr <destination label>"
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

void JMoreStmt::run() {

}
