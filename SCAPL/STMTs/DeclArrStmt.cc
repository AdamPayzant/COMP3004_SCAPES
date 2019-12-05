#include "DeclArrStmt.h"
#include "../Program.h"

DeclArrStmt::DeclArrStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "DeclArrStmt";
}

void DeclArrStmt::compile(std::string &line){
    line = line.substr(4);
    std::string nextArg = "##_NOTVALID_##";
    std::string nextArg2 = "##_NOTVALID_##";
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
    ids->push_back(new ArrayVariable(nextArg));
    o1 = new Operand(ids->at(ids->size()-1));

    this->master->removeNextArg(line);
    this->master->removeLeadingWhitespace(line);
    if(line.size()==0){
        this->master->setCompileValidityStatus(false);
        errorText = "Instruction provided too few operands";
        this->master->setCompileError(errorText);
        return;
    }
    if(this->master->parseNextArg(line, nextArg2) < 1 || nextArg2.empty()){
        this->master->setCompileValidityStatus(false);
        errorText = "Invalid or non-existent instruction operand provided.";
        this->master->setCompileError(errorText);
        return;
    }

    bool sizeFound = false;
    if(nextArg2[0]=='$'){
        // Array case
        i++;
        std::string arrName;
        std::string accessName;
        int j;
        for(j = i; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(i + 1, j - i - 1);
                break;
            }
        }
        accessName = line.substr(j + 1, line.size() - 1 - j);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName, master);
                o2 = new Operand(temp);

                break;
            }
        }
    }
    else{
        for(i=0; i<nextArg2.size(); ++i){
            if(nextArg2[i]<48 || nextArg2[i]>57){
                break;
            }
        }
        //If literal number
        if(i == nextArg2.size()){
            Literal* tempPtr = new Literal(nextArg2);
            o2 = new Operand(tempPtr);
            sizeFound = true;

        //Else variable
        }else{
            for(i = 0; i < nextArg.size(); ++i){
                if(nextArg[i]<48 || (nextArg[i]>90 && nextArg[i]<97)){
                    this->master->setCompileValidityStatus(false);
                    errorText = "Size operand contains invalid characters";
                    this->master->setCompileError(errorText);
                    return;
                }
            }
            for(i = 0; i < ids->size() ; ++i){
                if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(nextArg) == 0){
                    if(ids->at(i)->getSubtype().compare("ArrayVariable")==0){
                        this->master->setCompileValidityStatus(false);
                        errorText = "Cannot provide entire array as an operand where a value is expected.";
                        this->master->setCompileError(errorText);
                        return;
                    }
                    o2 = new Operand(ids->at(i));
                    sizeFound = true;
                }
            }
        }

    }
    if(!sizeFound){
        this->master->setCompileValidityStatus(false);
        errorText = "Array size operand either contains erroneous characters or is an incorrect variable name";
        this->master->setCompileError(errorText);
        return;
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
void DeclArrStmt::compile(std::string &line){
    // TODO
    // Syntax dca <name> <size>
    int i;
    for(i = 5; i < line.size(); i++) {
        if(line[i] == ' ') {
            break;
        }
    }

    // Creates the array in Operand 1
    std::string name = line.substr(4, i - 5);
    
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ArrayVariable *temp = new ArrayVariable(name);
    o1 = new Operand(temp);
    ids->push_back(temp);

    // Gets the size of the array in Operand 2
    if(isdigit(line[i+1])) {
        // Literal case
        Literal *temp = new Literal(line.substr(5, i - 4));
        o1 = new Operand(temp);
    }
    else if(line[i+1] == '$') {
        // Array case
        i++;
        std::string arrName;
        std::string accessName;
        int j;
        for(j = i; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(i + 1, j - i - 1);
                break;
            }
        }
        accessName = line.substr(j + 1, line.size() - 1 - j);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName, master);
                break;
            }
        }
    }
    else {
        // Variable
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(i + 1, line.size() - i - 1)) == 0) {
                o2 = new Operand(*iter);
            }
        }
    }
}
*/

void DeclArrStmt::run(){
    ArrayVariable *temp = (ArrayVariable *) o1->getIDPtr();
    temp->create(o2->getVal());
}
