#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H

#include <string>

#include "../Statement.h"

class DeclArrStmt: public Statement {
    public:
        DeclArrStmt();
        ~DeclArrStmt();
        void compile(std::string);
        void run();
};

#endif