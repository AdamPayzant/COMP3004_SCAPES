#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Identifier.h
 * Author: Edward Adam Payzant
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to define the Identifier superclass, which is a superclass that contains
 * a declaration of the general state and behavior that will be inherited and/or independently
 * implemented by its subclasses.
 * These subclasses will be used to create an internal representation of an identifier, which contains
 * the state operands associated with SCAPL instructions.
 * They are not operand objects, but they are internal representations of the state of operands, which
 * is why operand objects contain a pointer to an identifier object.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Identifier {
    public:
        /**
         *
         **/
        void getName(std::string&);

        /**
         *
         **/
        std::string getNameValue();

        /**
         *
         **/
        std::string getSubtype();

    protected:
        /**
         *
         **/
        std::string name;

        /**
         *
         **/
        std::string subtype;
};

#endif
