#ifndef ARRACCESS_H
#define ARRACCESS_H

#include <string>

#include "Value.h"
#include "ArrayVariable.h"
#include "Identifier.h"

class ArrAccess: public Identifier, public Value {
    public:
        ArrAccess(ArrayVariable *, std::string);
        ~ArrAccess();
        int getVal();
    private:
        ArrayVariable* arr;
        std::string access;
};

#endif