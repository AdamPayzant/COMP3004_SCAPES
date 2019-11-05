#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

#include "Variable.h"
#include "Label.h"

class Identifier {
    public:
        Identifier(std::string &);
        ~Identifier();

        // Getters and setters
        void getName(std::string &);
    private:
        std::string name;
};

#endif