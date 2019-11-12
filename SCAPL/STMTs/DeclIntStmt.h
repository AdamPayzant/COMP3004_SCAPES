#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include <string>

#include "../Program.h"
#include "../Statement.h"
#include "../Identifier.h"
#include "../Variable.h"

class DeclIntStmt: public Statement {
    public:

        DeclIntStmt(Program *);


        ~DeclIntStmt();

        /**
       * Constructor
       * Parameters:
       * -  sting repersenting the instruction
       *
       **/
        void compile(std::string &);

        /**
     * run function produces the result of the code
     **/
        void run();

        std::string getName() { 
          std::string n = "DeclIntStmt";
          return(n);
        };

        void setLabel(Label *l) {
          label = l;
        };
};

#endif
