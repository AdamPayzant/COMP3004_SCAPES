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

        /**
       * Constructor
       * Parameters:
       * -  sting repersenting the instruction
       *
       **/
        bool compile(std::string &);

        /**
     * run function produces the result of the code
     **/
        void run();
        virtual std::string getName();
        virtual Operand* getOperand1();
        virtual Operand* getOperand2();
        virtual Label* getLabel();
        virtual void setLabel(Label *l);
};

#endif
