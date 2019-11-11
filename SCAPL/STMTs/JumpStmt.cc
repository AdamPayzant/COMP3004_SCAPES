#include "JumpStmt.h"

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
void JumpStmt::compile(std::string &line) {
    // Syntax: "jmp <Destination Label>"
    // Nothing to do here for now
}
/**
* run function produces the result of the code
**/

void JumpStmt::run() {

}
