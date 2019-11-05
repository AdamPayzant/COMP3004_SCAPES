#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include <string>

#include "../Statement.h"
#include "../Identifier.h"
#include "../Variable.h"

class DeclIntStmt: public Statement {
    public:
        DeclIntStmt(Program *);
        ~DeclIntStmt();
        void compile(std::string &);
        void run();
};

#endif