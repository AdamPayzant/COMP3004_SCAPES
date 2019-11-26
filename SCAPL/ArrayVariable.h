#ifndef ARRAYVARIABLE_H
#define ARRAYVARIABLE_H

#include <string>

#include "Variable.h"
#include "IntegerVariable.h"

class ArrayVariable: public Variable {
    public:
        ArrayVariable(int, std::string &);
        ~ArrayVariable();
        void create();
        void setAt(int);
        Variable* getAt(int);
    private:
        Variable** arr;
        int size;
};

#endif