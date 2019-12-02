#ifndef ARRAYVARIABLE_H
#define ARRAYVARIABLE_H

#include <string>

#include "ArrAccess.h"
#include "Variable.h"
#include "Value.h"
#include "Literal.h"
#include "IntegerVariable.h"

class ArrAccess;
class ArrayVariable: public Variable {
    public:
        ArrayVariable(std::string &);
        ~ArrayVariable();
        void create(int);
        void setAt(int, int);
        Variable* getAt(int);
    private:
        Variable** arr;
        int size;
};

#endif
