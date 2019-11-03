#ifndef ENDSTMT_H
#define ENDSTMT_H

#include <string>

#include "../Statement.h"

class EndStmt: public Statement {
    public:
        EndStmt();
        ~EndStmt();
        void compile(std::string);
        void run();
};

#endif