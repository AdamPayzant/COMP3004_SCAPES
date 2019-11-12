#ifndef JUMPSTMT_H
#define JUMPSTMT_H

#include <string>

#include "../Statement.h"
#include "../Label.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: JumpStmt.h
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
class JumpStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * -  pointer to a program object
         *
         **/
        JumpStmt(Program *);

        /**
         * run function produces the result of the code
         **/
        ~JumpStmt();

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
