#include "ArrAccess.h"
#include "Program.h"

ArrAccess::ArrAccess(ArrayVariable *a, std::string acc, Program *m) {
    arr = a;
    access = acc;
    master = m;
    subtype = "ArrAccess";
}

ArrAccess::~ArrAccess() {

}

int ArrAccess::getVal() {
    if(getVar()!=nullptr){
        getVar()->getVal();
    }
    else{
        return -1;
    }
}

std::string ArrAccess::getOut() {
    return(std::to_string(getVar()->getVal()));
}

void ArrAccess::setVal(int v) {
    if(getVar()!=nullptr){
        getVar()->setVal(v);
    }
}

ArrayVariable* ArrAccess::getParent(){
    return arr;
}

std::string ArrAccess::getAccess(){
    return access;
}

IntegerVariable * ArrAccess::getVar() {
    Literal *lv;
    ArrAccess *av;
    IntegerVariable *iv;

    lv = nullptr;
    av = nullptr;
    iv = nullptr;


    for (int i=0; i<access.size(); ++i) {
        if(access[i]<48 || access[i]>57){
            return nullptr;
        }
    }
    if(std::stoi(access) >= this->arr->getSize()) return nullptr;
    return (IntegerVariable*)this->arr->getAt(std::stoi(access));
}

void ArrAccess::print(std::string& formattedString){
    if(getVar()==nullptr){
        formattedString.append("NULL");
    }
    else{
        formattedString.append(getOut());
    }
}
