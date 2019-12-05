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
        std::string arrayName;
        std::string accessName;
        bool nameEndFound = false;
        int j;
        for(j = 0; j < nextArg2.size(); j++) {
            if(line[j] == '+') {
                arrayName = nextArg2.substr(1, j);
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
                o2 = new Operand(tempPtr);
                sizeFound = true;
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

void DeclArrStmt::run(){
    ArrayVariable *temp = (ArrayVariable *) o1->getIDPtr();
    temp->create(o2->getVal());
}
