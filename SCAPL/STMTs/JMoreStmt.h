#ifndef JMORESTMT_H
#define JMORESTMT_H

#include <string>

#include "../Statement.h"

class JMoreStmt: public Statement {
    public:
      /**
     * Constructor
     * Parameters:
     * -  sting repersenting the instruction
     *
     **/
        JMoreStmt(Program *);
        /**
        * Destructor
        **/
        ~JMoreStmt();
        /**
        * compile
        * Parameters:
        * -  String being the instruction
        *
        **/
        void compile(std::string &);
        /**
     * run function produces the result of the code
     **/
        void run();

        std::string getName() { 
            std::string n = "JMoreStmt";
            return(n);
         };

         void setLabel(Label *l) {
          label = l;
         };
};

#endif
