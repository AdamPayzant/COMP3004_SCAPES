#ifndef DECLINTSTMT_H
#define DECLINTSTMT_H

#include <string>

#include "../Statement.h"
#include "../Identifier.h"
#include "../Variable.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: DeclIntStmt.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     //////////////
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class DeclIntStmt: public Statement {
    public:
        /**
         *
         **/
        DeclIntStmt(Program *);

        /**
         *
         **/
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

        /**
         *
         **/
        virtual std::string getName();

        /**
         *
         **/
        virtual Operand* getOperand1();

        /**
         *
         **/
        virtual Operand* getOperand2();

        /**
         *
         **/
        virtual Label* getLabel();

        /**
         *
         **/
        virtual void setLabel(Label *l);
};

#endif
