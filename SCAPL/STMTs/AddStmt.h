#ifndef ADDSTMT_H
#define ADDSTMT_H

#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include "../Statement.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: AddStmt.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     //////////
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class AddStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * - Parameters pointer to a program object
         **/
        AddStmt(Program *);

        /**
         *
         **/
        ~AddStmt();

        /**
         * Compile fuction
         * the fuction compiles the instrucution into objects to be executed
         **/
        void compile(std::string &);
        /**
         * run function produces the result of the run fuction
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
