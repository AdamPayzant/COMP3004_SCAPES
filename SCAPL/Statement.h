#ifndef STATEMENT_H
#define STATEMENT_H

#include <string>
#include <vector>

#include "Operand.h"
#include "Label.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Variable.h
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
        ~Statement() {
            if(o1 != nullptr) {
                delete(o1);
            }
            if(o2 != nullptr) {
                delete(o2);
            }
        };
        virtual void compile(std::string &) = 0;
        virtual void run() = 0;
        virtual std::string getName() = 0;
        virtual Operand* getOperand1() = 0;
        virtual Operand* getOperand2() = 0;
        virtual Label* getLabel() = 0;
        virtual void setLabel(Label *l) = 0;
    protected:
        // Master program
        Program *master;
        // Two operands (Either can be NULL)
        Operand *o1;
        Operand *o2;
        // Label (Can be NULL)
        Label *label;
        std::string subtype;
};

#endif
