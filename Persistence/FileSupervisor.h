#ifndef FILESUPERVISOR_H
#define FILESUPERVISOR_H

#include <ios>
#include <fstream>
#include <string>

using namespace std;

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 * 
 * Version 1.0:
 * File: FileSupervisor.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 * 
 * File Purpose:
 *     Used to create an SQLiteConnector object, which will be used to
 * open, manage, and finally close a connection with a local SQLite Database.
 * 
 * Formatting style based on course notes and course work from COMP2401 and 
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering 
 * of COMP2404.
 * File operations based on descriptions and examples presented on specific pages
 * found on cplusplus.com[1][2][3].
 * All rights and credit remain with referenced definitions and samples from original authors.
 * References:
 * [1] cplusplus.com.(2019).Input/output with files.[online]
 *      Available at: http://www.cplusplus.com/doc/tutorial/files/ 
 *      [Accessed 12 Nov. 2019].
 * [2] cplusplus.com.(2019).std::ofstream.[online]
 *      Available at: http://www.cplusplus.com/reference/fstream/ofstream/ 
 *      [Accessed 12 Nov. 2019].
 * [3] cplusplus.com.(2019).std::ifstream.[online]
 *      Available at: http://www.cplusplus.com/reference/fstream/ifstream/ 
 *      [Accessed 12 Nov. 2019].
 **/
class FileSupervisor
{
  public:
    /**
     * Constructor
     **/
    FileSupervisor();

    /**
     * Destructor
     **/
    ~FileSupervisor();

    /**
     * Function used to save the contents of a referenced string (parameter 1) to secondary memory
     * in a file whose name or path is provided (parameter 2).
     * Parameters:
     * - Reference to a string whose contents will be saved to secondary memory.
     * - string value correlating to either the filename or path of the file that will
     *   be saved to secondary memory containing the contents of parameter 1.
     **/
    bool saveToFile(string&, string);

    /**
     * Function used to load the contents of a file into the referenced string (parameter 1).
     * Parameters:
     * - Reference to a string whose contents will be formed from the contents of the file whose
     *   filename or path is provided as parameter 2.
     * - Filename or path to the file whose contents we'd like to load into the referenced string (parameter 1).
     **/
    bool loadFromFile(string&, string);
};

#endif
