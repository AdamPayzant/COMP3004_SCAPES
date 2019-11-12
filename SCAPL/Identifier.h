#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>


class Identifier {
    public:
        // Getters and setters
        void getName(std::string &);
        void getSubtype(std::string &);
    protected:
        std::string name;
        std::string subtype;
};

#endif
