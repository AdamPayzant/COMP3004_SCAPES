
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
void JMoreStmt::compile(std::string &line) {
    // Syntax: "jmr <destination label>"
    // Nothing to do here for now
}
/**
* run function produces the result of the code
**/

void JMoreStmt::run() {

}
