#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

#include "Identifier.h"

class Variable: public Identifier {
    public:
        Variable(std::string &);
        void setVal(int &);
        void getVal(int &);
    private:
        int value;
};

#endif