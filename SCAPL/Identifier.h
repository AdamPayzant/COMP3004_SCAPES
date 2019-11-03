#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

#include "Variable.h"
#include "Label.h"

class Identifier {
    public:
    private:
        std::string name;
        Variable value;
        Label label;
};

#endif