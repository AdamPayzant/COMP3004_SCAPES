#include "ArrAccess.h"

ArrAccess::ArrAccess(ArrayVariable *a, std::string acc) {
    arr = a;
    access = acc;
    subtype = "ArrAccess";
}

ArrAccess::~ArrAccess() {

}

int ArrAccess::getVal() {
    // TODO: Go through access value 
}