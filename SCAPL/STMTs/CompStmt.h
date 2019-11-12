#ifndef COMPSTMT_H
#define COMPSTMT_H

#include <string>

#include "../Statement.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: CompStmt.h
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
class CompStmt: public Statement {
    public:
        /**
         * Constructor
         * Parameters:
         * - Parameters pointer to a program object
         *
         **/
        CompStmt(Program *);

        /**
         * Destructor
         **/
        ~CompStmt();
        
        /**
         *
         **/
        void compile(std::string &);

        /**
         *
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
