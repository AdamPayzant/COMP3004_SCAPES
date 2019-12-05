
#ifndef VALUE_H
#define VALUE_H

#include <string>

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: Value.h
 * Author: Edward Adam Payzant
 * Date: 05/12/2019
 *
 * File Purpose:
 *     Used to define the Value superclass, which is an abstract class that contains
 * a declaration of the general state and behavior that will be inherited and/or independently
 * implemented by its subclasses.
 * These subclasses will be used to store values, and allow for consistent value accessing
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 *
 **/
class Value {
    public:
        virtual int getVal() = 0;
        virtual std::string getOut() = 0;
        virtual void setVal(int) = 0;
};

#endif
