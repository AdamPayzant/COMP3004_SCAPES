#ifndef ARRAYVARIABLE_H
#define ARRAYVARIABLE_H

#include <string>

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
        int getSize();
        int setSize(int newSize);
        virtual void print(std::string&);
    private:
        Variable** arr;
        int size;
};

#endif
