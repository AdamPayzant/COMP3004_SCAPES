#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>

#include "Identifier.h"

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
 *     Used to create a Variable object, which is an internal representation of
 * the variable object that should be formed during execution of compiled SCAPL code.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Variable: public Identifier {

    public:
        /**
         * Constructor
         * Parameters:
         * - Reference to a string variable holding the name value of the variable
         **/
        Variable(std::string &);
        Variable();
};

#endif
