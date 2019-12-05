#include "AddStmt.h"
#include "../Program.h"

AddStmt::AddStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "AddStmt";
}


AddStmt::~AddStmt() {
    delete(o1);
    delete(o2);
}

void AddStmt::compile(std::string &line) {
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

    bool argumentFound = false;
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
        accessName = nextArg.substr(j+1);

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
                argumentFound = true;
                break;
            }
        }
    }
    else{
        for(i=0; i<nextArg.size(); ++i){
            if(nextArg[i]<48 || nextArg[i]>57){
                break;
            }
        }
        //If literal number
        if(i == nextArg.size()){
            Literal* tempPtr = new Literal(nextArg);
            o1 = new Operand(tempPtr);
            argumentFound = true;

        //Else variable
        }else{
            for(i = 0; i < nextArg.size(); ++i){
                if(nextArg[i]<48 || (nextArg[i]>90 && nextArg[i]<97)){
                    this->master->setCompileValidityStatus(false);
                    errorText = "Move instruction value operand contains invalid characters";
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
                    o1 = new Operand(ids->at(i));
                    argumentFound = true;
                    break;
                }
            }
        }

    }
    if(!argumentFound){
        this->master->setCompileValidityStatus(false);
        errorText = "Array size operand either contains erroneous characters or is an incorrect variable name";
        this->master->setCompileError(errorText);
        return;
    }



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

    argumentFound = false;
    if(nextArg2[0]=='$'){
        // Array case
        std::string arrayName;
        std::string accessName;
        bool nameEndFound = false;
        int j;
        for(j = 0; j < nextArg2.size(); j++) {
            if(line[j] == '+') {
                arrayName = nextArg2.substr(1, j-1);
                nameEndFound = true;
                break;
            }
        }
        if(!nameEndFound || j+1>=nextArg2.size()){
            this->master->setCompileValidityStatus(false);
            errorText = "Accessing Array elements requires the format $ArrayName+Index.";
            this->master->setCompileError(errorText);
            return;
        }
        accessName = nextArg2.substr(j+1);

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
                o2 = new Operand(tempPtr);
                argumentFound = true;
                break;
            }
        }
    }
    else{
        for(i = 0; i < nextArg2.size(); ++i){
            if(nextArg2[i]<48 || (nextArg2[i]>90 && nextArg2[i]<97)){
                this->master->setCompileValidityStatus(false);
                errorText = "Add instruction destination operand contains invalid characters";
                this->master->setCompileError(errorText);
                return;
            }
        }
        for(i = 0; i < ids->size() ; ++i){
            if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(nextArg2) == 0){
                if(ids->at(i)->getSubtype().compare("ArrayVariable")==0){
                    this->master->setCompileValidityStatus(false);
                    errorText = "Cannot provide entire array as an operand where a variable or an Array element is expected.";
                    this->master->setCompileError(errorText);
                    return;
                }
                o2 = new Operand(ids->at(i));
                argumentFound = true;
                break;
            }
        }

    }
    if(!argumentFound){
        this->master->setCompileValidityStatus(false);
        errorText = "Add instruction destination operand either contains erroneous characters or is an incorrect variable name";
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


void AddStmt::run() {
    o2->setVal(o1->getVal() + o2->getVal());
}
