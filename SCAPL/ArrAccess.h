#ifndef ARRACCESS_H
#define ARRACCESS_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "Program.h"
#include "Value.h"
#include "ArrayVariable.h"
#include "Identifier.h"

class ArrAccess: public Identifier, public Value {
    public:
        ArrAccess(ArrayVariable *, std::string, Program *);
        ~ArrAccess();
        int getVal();
        void setVal(int);
    private:
        IntegerVariable* getVar();
        ArrayVariable* arr;
        std::string access;
        Program *master;
};

#endif