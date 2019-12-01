#ifndef OPERAND_H
#define OPERAND_H

#include "Identifier.h"
#include "Variable.h"
#include "IntegerVariable.h"
#include "ArrayVariable.h"
#include "Value.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Operand.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create an Operand object, which is an internal representation of
 * an operand of a SCAPL assembly instruction.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Operand {
    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to the Identifier serving as the Operand of a statement.
         **/
        Operand(Identifier *);

        /**
         * Destructor
         **/
        ~Operand();

        /**
         * Getter method for pointer to the identifier of the Operand.
         **/
        void getID(Identifier**);

        Identifier* getIDPtr();

        /**
         * Setter method for pointer to the identifier of the Operand.
         **/
        void setID(Identifier*);

        int getVal();
        std::string getOut();
        void setVal(int);
        
    private:
        /**
         * Pointer to the Identifier serving as the Operand of a statement.
         **/
        Identifier *id;
};

#endif
