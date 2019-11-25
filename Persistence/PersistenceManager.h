#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <string>
#include <vector>
using namespace std;

#include "DatabaseConductor.h"
#include "FileSupervisor.h"
#include "./../SCAPL/Identifier.h"
#include "./../SCAPL/Statement.h"

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 * 
 * Version 1.0:
 * File: PersistenceManager.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 * 
 * File Purpose:
 *     Used to create a PersistenceManager object, which will be used to
 * coordinate operations involving object or source code persistence by providing
 * a unifying interface of the storage layer services.
 * 
 * Formatting style based on course notes and course work from COMP2401 and 
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering 
 * of COMP2404.
 * 
 **/
class PersistenceManager
{
  public:
    /**
     * Constructor
     **/
    PersistenceManager();

    /**
     * Destructor
     **/
    ~PersistenceManager();

    /**
     * Function used to delegate the operations required to render the Identifier and Statement
     * objects currently held within a Program object's vectors into persistence.
     **/
    bool persistProgramObjects(std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     * Function used to delegate the operations required to instantiate the Identifier and Statement
     * objects currently held within the database into the vectors of a Program object.
     **/
    bool restoreProgramObjects(Program* program, std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     * Function used to delegate the operations required to save the contents of the editor textbox
     * into secondary memory as a SCAPL source file.
     **/
    bool saveToFile(string, string&);

    /**
     * Function used to delegate the operations required to load the contents of a SCAPL source file
     * from secondary memory into the editor textbox.
     **/
    bool loadFromFile(string&, string&);

  private:
    /**
     * Object used to manage operations relating to object persistence in the database
     **/
    DatabaseConductor databaseConductor;

    /**
     * Object used to manage operations relating to source codee persistance on secondary memory
     **/
    FileSupervisor fileSupervisor;

    /**
     * Used to store a local instance of the editor textbox's text in case of interface layer failure.
     **/
    string sourceCodeSnapshot;
};

#endif
