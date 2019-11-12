#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>


class Identifier {
    public:
        // Getters and setters
        void getName(std::string&);
        std::string getNameValue();
        std::string getSubtype();
    protected:
        std::string name;
        std::string subtype;
};

#endif
