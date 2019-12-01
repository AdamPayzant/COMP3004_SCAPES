#include "ArrAccess.h"

ArrAccess::ArrAccess(ArrayVariable *a, std::string acc, Program *m) {
    arr = a;
    access = acc;
    master = m;
    subtype = "ArrAccess";
}

ArrAccess::~ArrAccess() {

}

int ArrAccess::getVal() {
    Literal *lv;
    ArrAccess *av;
    IntegerVariable *iv;

    // TODO: Go through access value 
    if(std::isdigit(access[0])) {
        // Literal access
        Literal val(std::stoi(access));
    }
    else if(access[0] == '$') {
        // OH GOD CASCADING ARRAYS
        std::vector<Identifier*> *ids = master->getIds();
        int i;
        for(i = 2; i < access.size(); i++) {
            if(access[i] == '+') {
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
    }
    else if(iv != nullptr) {
        temp = (IntegerVariable *) arr->getAt(iv->getVal());
    }
    else {
        temp = (IntegerVariable *) arr->getAt(av->getVal());
    }
}

void ArrAccess::setVal(int v) {
    
}