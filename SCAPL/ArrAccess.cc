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

/*
int ArrAccess::getVal() {
    return(getVar()->getVal());
}

std::string ArrAccess::getOut() {
    return(std::to_string(getVar()->getVal()));
}

void ArrAccess::setVal(int v) {
    getVar()->setVal(v);
}

ArrayVariable* ArrAccess::getParent(){
    return arr;
}

std::string ArrAccess::getAccess(){
    return access;
}
*/

/*
IntegerVariable * ArrAccess::getVar() {
    Literal *lv;
    ArrAccess *av;
    IntegerVariable *iv;

    lv = nullptr;
    av = nullptr;
    iv = nullptr;

    // TODO: Go through access value 
    if(std::isdigit(access[0])) {
        // Literal access
        lv = new Literal(access);
    }
    else if(access[0] == '$') {
        std::vector<Identifier*> *ids = master->getIds();
        std::string arrName;
        std::string accessName;
        int j;
        for(j = 2; j < access.size(); j++) {
            if(access.at(j) == '+') {
                arrName = access.substr(1, j - 1);
            }
        }
        accessName = access.substr(j + 1, access.size() - 1 - j);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                av = new ArrAccess(downcast, accessName, master);
                break;
            }
        }
    }
    else {
        // Variable access
        std::vector<Identifier*> *ids = master->getIds();
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string tempName;
            (*iter)->getName(tempName);
            if(tempName.compare(access) == 0) {
                iv = (IntegerVariable *) (*iter);
            }
        }
    }
    IntegerVariable* temp;
    if(lv != nullptr) {
        temp = (IntegerVariable *) arr->getAt(lv->getVal());
        delete(lv);
    }
    else if(iv != nullptr) {
        temp = (IntegerVariable *) arr->getAt(iv->getVal());
        // Don't delete iv because it's shared with the main identifiers
    }
    else {
        temp = (IntegerVariable *) arr->getAt(av->getVal());
        delete(av);
    }
    return temp;
}
*/
