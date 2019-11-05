#ifndef JUMPSTMT_H
#define JUMPSTMT_H

#include <string>

#include "../Statement.h"

class JumpStmt: public Statement {
    public:
        JumpStmt(Program *);
        ~JumpStmt();
        void compile(std::string &);
        void run();
};

#endif