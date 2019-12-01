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
    return(getVar()->getVal());
}

std::string ArrAccess::getOut() {
    return(std::to_string(getVar()->getVal()));
}

void ArrAccess::setVal(int v) {
    getVar()->setVal(v);
}

IntegerVariable * ArrAccess::getVar() {
    Literal *lv;
    ArrAccess *av;
    IntegerVariable *iv;

    // TODO: Go through access value 
    if(std::isdigit(access[0])) {
        // Literal access
        lv = new Literal(std::stoi(access));
    }
    else if(access[0] == '$') {
        // OH GOD CASCADING ARRAYS
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