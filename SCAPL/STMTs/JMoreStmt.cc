#include "JMoreStmt.h"
#include "../Program.h"

JMoreStmt::JMoreStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "JMoreStmt";
}

JMoreStmt::~JMoreStmt() {
    delete(label);
}

void JMoreStmt::compile(std::string &line) {
    line = line.substr(4);
    std::string nextArg = "##_NOTVALID_##";
    std::string errorText;
    this->master->removeLeadingWhitespace(line);
    if(this->master->parseNextArg(line, nextArg) < 1 || nextArg.empty()){
        this->master->setCompileValidityStatus(false);
        errorText = "Invalid or non-existent instruction operand provided.";
        this->master->setCompileError(errorText);
        return;
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    int i;
    for(i = 0; i < ids->size() ; ++i){
        if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(nextArg) == 0){
            if(ids->at(i)->getSubtype().compare("Label") != 0){
                this->master->setCompileValidityStatus(false);
                errorText = "Jump instruction operand must be a label";
                this->master->setCompileError(errorText);
                return;
            }
            else{
                Label* tempPtr = (Label*) ids->at(i);
                o1 = new Operand(tempPtr);
                break;
            }
        }
    }
    this->master->removeNextArg(line);
    this->master->removeLeadingWhitespace(line);
    if(line.size()>0){
        this->master->setCompileValidityStatus(false);
        errorText = "Instruction provided too many operands";
        this->master->setCompileError(errorText);
        return;
    }
}


/*
void JMoreStmt::compile(std::string &line) {
    // Syntax: "jmr <destination label>"
    std::string target = line.substr(3, line.size() - 4);
    o1 = new Operand(master->getID(target));
}
*/

void JMoreStmt::run() {
    if(master->getCFlag() == 1) {
        master->changeStmt((Label *) o1->getIDPtr());
    }
}
