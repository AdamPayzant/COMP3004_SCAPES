#include "ReadStmt.h"
#include "../Program.h"
#include <iostream>

ReadStmt::ReadStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "ReadStmt";
}

ReadStmt::~ReadStmt() {
    delete(o1);
}

void ReadStmt::compile(std::string &line) {
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

    bool variableFound = false;
    if(nextArg[0]=='$'){
        // Array case
        std::string arrayName;
        std::string accessName;
        bool nameEndFound = false;
        int j;
        for(j = 0; j < nextArg.size(); j++) {
            if(line[j] == '+') {
                arrayName = nextArg.substr(1, j-1);
                nameEndFound = true;
                break;
            }
        }
        if(!nameEndFound || j+1>=nextArg.size()){
            this->master->setCompileValidityStatus(false);
            errorText = "Accessing Array elements requires the format $ArrayName+Index.";
            this->master->setCompileError(errorText);
            return;
        }
        accessName = line.substr(j+1);

        for(i = 0; i < ids->size() ; ++i){
            if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(arrayName) == 0){
                if(ids->at(i)->getSubtype().compare("ArrayVariable")!=0){
                    this->master->setCompileValidityStatus(false);
                    errorText = "Must provide valid Array variable to access Array elements.";
                    this->master->setCompileError(errorText);
                    return;
                }
                ArrayVariable* downcast = (ArrayVariable*) ids->at(i);
                ArrAccess* tempPtr = new ArrAccess(downcast, accessName, master);
                o1 = new Operand(tempPtr);
                variableFound = true;
                break;
            }
        }
    }
    //Variable case
    else{
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
                        errorText = "Cannot provide entire array as an operand where an array element is expected.";
                        this->master->setCompileError(errorText);
                        return;
                    }
                    o1 = new Operand(ids->at(i));
                    variableFound = true;
                    break;
                }
            }
    }
    if(!variableFound){
        this->master->setCompileValidityStatus(false);
        errorText = "Read operand either contains erroneous characters, is an incorrect variable name, or an erroneous Array element.";
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
void ReadStmt::compile(std::string &line) {
    int i = line.size() - 1;
    std::vector<Identifier*> *ids = master->getIds();

    if(line[4] == '$') {
        // Array case
        std::string arrName;
        std::string accessName;
        int j;
        for(j = 6; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(5, j - 5);
                break;
            }
        }
        accessName = line.substr(j + 1, i - j - 1);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName, master);
                o1 = new Operand(temp);
                break;
            }
        }
    }
    else {
        // Variable case
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(5, i - 4)) == 0) {
                o1 = new Operand(*iter);
            }
        }
    }
}
*/

void ReadStmt::run() {
    std::cout<<"beginning of run stmt"<<std::endl;
    std::string s = master->getUserInput();
    std::cout<<"user inputted: "<<s<<std::endl;
    int input = std::stoi(s);
    std::cout<<"to int: "<<input<<std::endl;
    std::cout<<"subtype: "<<o2->getIDPtr()->getSubtype()<<std::endl;
    o2->setVal(8);
    std::cout<<"o2 value: "<<o2->getVal()<<std::endl;
    std::cout<<"end of run stmt"<<std::endl;
}
