#ifndef DECLARRSTMT_H
#define DECLARRSTMT_H

#include <string>

#include "../Statement.h"

class DeclArrStmt: public Statement {
    public:
        DeclArrStmt(Program *);
        ~DeclArrStmt();
        void compile(std::string &);
        void run();
};

#endif