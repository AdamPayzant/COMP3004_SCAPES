#include "DeclIntStmt.h"
#include "../Program.h"

DeclIntStmt::DeclIntStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "DeclIntStmt";
}

DeclIntStmt::~DeclIntStmt() {

}

void DeclIntStmt::compile(std::string &line) {
    line = line.substr(4, line.size()-4);
    std::string nextArg = "##_NOTVALID_##";
    std::string errorText;
    this->master->removeLeadingWhitespace(line);
    if(this->master->parseNextArg(line, nextArg) < 1 || nextArg.empty()){
        this->master->setCompileValidityStatus(false);
        errorText = "Invalid or non-existent instruction operation provided.";
        this->master->setCompileError(errorText);
        return;
    }
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    int i;
    for(i = 0; i < nextArg.size(); ++i){
        if(nextArg[i]<48 || (nextArg[i]>90 && nextArg[i]<97)){
            this->master->setCompileValidityStatus(false);
            errorText = "Variable name ";
            errorText.append(nextArg);
            errorText.append("contains invalid characters");
            this->master->setCompileError(errorText);
            return;
        }
    }

    for(i = 0; i < ids->size() ; ++i){
        if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(nextArg) == 0){
            this->master->setCompileValidityStatus(false);
            errorText = "Cannot declare variable with name ";
            errorText.append(nextArg);
            errorText.append("; A variable with that name has already been declared.");
            this->master->setCompileError(errorText);
            return;
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
    ids->push_back(new IntegerVariable(nextArg));
    o1 = new Operand(ids->at(ids->size()-1));
}


void DeclIntStmt::run() {
    //integers declared during compiliation
}
