#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "Identifier.h"

class Label: public Identifier {
    public:
        Label(std::string &);
        ~Label();
    private:
};

#endif