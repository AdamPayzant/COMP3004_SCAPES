#ifndef JEQSTMT_H
#define JEQSTMT_H

#include <string>

#include "../Statement.h"

class JEqStmt: public Statement {
    public:
        JEqStmt(Program *);
        ~JEqStmt();
        void compile(std::string);
        void run();
};

#endif