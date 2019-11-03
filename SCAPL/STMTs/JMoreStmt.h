#ifndef JMORESTMT_H
#define JMORESTMT_H

#include <string>

#include "../Statement.h"

class JMoreStmt: public Statement {
    public:
        JMoreStmt();
        ~JMoreStmt();
        void compile(std::string);
        void run();
};

#endif