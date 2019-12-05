#include "PrintStmt.h"
#include "../Program.h"

PrintStmt::PrintStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "PrintStmt";
}

PrintStmt::~PrintStmt() {
    delete(o1);
}

void PrintStmt::compile(std::string &line) {
    line = line.substr(4);
    std::string nextArg = "##_NOTVALID_##";
    std::string errorText;
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    int i;

    this->master->removeLeadingWhitespace(line);
    if(line.size()==0){
        this->master->setCompileValidityStatus(false);
        errorText = "Instruction provided too few operands";
        this->master->setCompileError(errorText);
        return;
    }
    if(this->master->parseNextArg(line, nextArg) < 1 || nextArg.empty()){
        this->master->setCompileValidityStatus(false);
        errorText = "Invalid or non-existent instruction operand provided.";
        this->master->setCompileError(errorText);
        return;
    }

    bool stringFound = false;
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
                stringFound = true;
            }
        }
    }
    else{
        if(nextArg[0]=='\"'){
            if(nextArg[nextArg.size()-1]=='\"'){
                for(i = 1;i<nextArg.size()-1;++i){
                    if(nextArg[i]=='\"'){
                        this->master->setCompileValidityStatus(false);
                        errorText = "Invalid literal format.";
                        this->master->setCompileError(errorText);
                        return;
                    }
                }
                nextArg = nextArg.substr(1,nextArg.size()-2);
                Literal* tempPtr = new Literal(nextArg);
                o1 = new Operand(tempPtr);
                stringFound = true;
            }
            else{
                this->master->setCompileValidityStatus(false);
                errorText = "Invalid literal format.";
                this->master->setCompileError(errorText);
                return;
            }

        //Else variable
        }else{
            for(i = 0; i < nextArg.size(); ++i){
                if(nextArg[i]<48 || (nextArg[i]>90 && nextArg[i]<97)){
                    this->master->setCompileValidityStatus(false);
                    errorText = "Print instruction operand contains invalid characters";
                    this->master->setCompileError(errorText);
                    return;
                }
            }
            for(i = 0; i < ids->size() ; ++i){
                if(ids->at(i) != nullptr && !ids->at(i)->getNameValue().empty() && ids->at(i)->getNameValue().compare(nextArg) == 0){
                    o1 = new Operand(ids->at(i));
                    stringFound = true;
                }
            }
        }

    }
    if(!stringFound){
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
void PrintStmt::compile(std::string &line) {
    int i = line.size() - 1;
    std::vector<Identifier*> *ids = master->getIds();

    if(line[4] == '\"' || isdigit(line[4])) {
        std::string str = line.substr(5, i - 4);
        Literal *temp = new Literal(str);
        o1 = new Operand(temp);
    }
    else if(line[4] == '$') {
        // Array Case
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

void PrintStmt::run() {
    if(o1 != nullptr && o1->getIDPtr()!=nullptr){
        std::string formattedString;
        if(o1->getIDPtr()->getSubtype().compare("Literal")==0){
            formattedString = ((Literal *) o1->getIDPtr())->getOut();
        }
        else{
            ((Variable*) o1->getIDPtr())->print(formattedString);
        }
        formattedString.append("\n");
        this->master->addPrint(formattedString);
    }
}
