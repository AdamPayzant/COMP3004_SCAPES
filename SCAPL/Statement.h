#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>

#include "Program.h"
#include "Operand.h"
#include "Label.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Statement.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to define the Statement superclass, which is an abstract class that contains
 * a declaration of the general state and behavior that will be inherited and/or independently
 * implemented by its subclasses.
 * These subclasses will be used to create an internal representation of an instruction that should
 * be executed during execution of compiled SCAPL code.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Program;
class Statement {
    public:
        /**
         * Destructor
         **/
        ~Statement();
        /**
         * Function used to compile the statement being provided as a parameter value
         **/
        virtual void compile(std::string &) = 0;

        /**
         * Function used to execute the state contained within the current statement
         **/
        virtual void run() = 0;

        /**
         * Getter function used to return name of the subclass of the current statement
         **/
        std::string getName();

        /**
         * Getter function used to return a pointer to the first operand object associated with the statement
         **/
        Operand* getOperand1();

        /**
         * Setter function used to set a pointer to the first operand object associated with the statement
         **/
        void setOperand1(Operand*);

        /**
         * Getter function used to return a pointer to the second operand object associated with the statement
         **/
        Operand* getOperand2();

        /**
         * Setter function used to set a pointer to the first operand object associated with the statement
         **/
        void setOperand2(Operand*);

        /**
         * Getter function used to return a pointer to the label object associated with the statement
         **/
        Label* getLabel();

        /**
         * Setter function used to set a pointer to the label object associated with the statement
         **/
        void setLabel(Label *l);

    protected:
        /**
         * Pointer to the program from which the statement was derived
         **/
        Program *master;

        /**
         * Pointer to the first operand object associated with the statement
         **/
        Operand *o1;

        /**
         * Pointer to the second operand object associated with the statement
         **/
        Operand *o2;

        /**
         * Pointer to the label object associated with the statement
         **/
        Label *label;

        /**
         * String variable used to hold the subclass name of the current statement
         **/
        std::string subtype;
};

#endif
