#include "EndStmt.h"
#include "../Program.h"

EndStmt::EndStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "EndStmt";
}


EndStmt::~EndStmt() {
    // No Pointers to delete
}


void EndStmt::compile(std::string &line) {
    std::string errorText;
    if(line.size() == 3){
        return;
    }
    else{
        line = line.substr(4);
        this->master->removeLeadingWhitespace(line);
        if(line.size()>0){
            this->master->setCompileValidityStatus(false);
            errorText = "Instruction provided too many operands";
            this->master->setCompileError(errorText);
            return;
        }
        return;
    }
}


void EndStmt::run() {
    master->end();
}
