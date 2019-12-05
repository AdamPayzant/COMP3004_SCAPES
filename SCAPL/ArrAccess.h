#ifndef ARRACCESS_H
#define ARRACCESS_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "Value.h"
#include "ArrayVariable.h"
#include "Identifier.h"
#include "IntegerVariable.h"
#include "Literal.h"

class Program;
class ArrAccess: public Identifier, public Value {
    public:
        ArrAccess(ArrayVariable *, std::string, Program *);
        ~ArrAccess();
        int getVal();
        std::string getOut();
        void setVal(int);
        ArrayVariable* getParent();
        std::string getAccess();
        void print(std::string&);
    private:
        IntegerVariable* getVar();
        ArrayVariable* arr;
        std::string access;
        Program *master;
};

#endif
