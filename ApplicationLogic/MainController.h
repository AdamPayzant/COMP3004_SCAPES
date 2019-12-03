#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <ios>
#include <fstream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

#include "./Interface/MainWindow.h"
#include "./Persistence/PersistenceManager.h"
#include "./SCAPL/Program.h"

class MainWindow;
/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: MainController.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 *
 * File Purpose:
 *     Used to create a controller object that will be used manage the operations required
 * to complete requests received by the application window through user input.
 * Id est, the controller object will coordinate operations completed by both the application window
 * and the persistence objects to ensure program functionality.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 **/
class MainController
{
    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to the Persistence Manager object that directs
         * operations involving making objects or text persistent.
         * - Pointer to the MainWindow object who is the primary widget
         * of the Qt Application and manages user input and view by managing its
         * widgets and delegating calls to the Main Controller.
         **/
        MainController(PersistenceManager*, MainWindow*);

        /**
         * Destructor
         **/
        ~MainController();

        /**
         * Function used by the Interface layer to signal the MainController to
         * begin an operation when the user has requested that action.
         **/
        void clientRequestHandler(string);

        /**
         * Function used to begin an operation involving saving the source code
         * in the editor on the MainWindow to persistence.
         **/
        void saveSourceCode();

        /**
         * Function used to begin an operation involving loading the source code
         * onto the editor on the MainWindow from persistence.
         **/
        void loadSourceCode();

        /**
         * Function used to begin an operation involving compiling the saved version of
         * source code currenty in the editor.
         **/
        void compileSourceCode();

        /**
         * Function used to begin an operation involving running the compiled version
         * of the source code currently in the editor.
         **/
        void runCompiledProgram();

        string& getUserInput();


    private:
        /**
         * Pointer to the Persistence Manager object that directs
         * operations involving making objects or text persistent.
         **/
        PersistenceManager* persistenceManager;

        /**
         * Pointer to the MainWindow object who is the primary widget
         * of the Qt Application and manages user input and view by managing its
         * widgets and delegating calls to the Main Controller.
         **/
        MainWindow* mainWindow;

        /**
         * Pointer to a program object currently being handled by the Main Controller for
         * either compilation or execution.
         **/
        Program* program;
};

#endif
