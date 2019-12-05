# 3004_SCAPES Version 1.0

To provide to the user an IDE capable of creating and managing SCAPL source code files, as well as compiling these source code files in order to finally execute them.

## Authors

Mathieu Leblanc (101092676)  
Edward Adam Payzant (101082175)  
William So (101070267)  
Zacchaeus Leung (101035212)

**Date:** 05/12/2019

## Design Pattern

We implemented the composite design pattern. 
This was implemented through the way we implemented arrays, where arrays store pointers to generic variables instead of explicitly Integer Variables, and the use of polymorphism on the implementation of the print function.
Additionally, this design pattern allows for greater feature potential in the future for what arrays can store, being able to store any Variable subtype, even arrays other should the syntax be added.
Through this implementation, all subclasses of the Variable class can be called to complete the print function through their own implementation, and cascade that behavior through their elements if they are also a composite (array) type.


## Compilation

Ensure that you have extracted all the files held within the tar archive.

Navigate to the "3004_SCAPES" directory and run the following command:

    make

## Launching SCAPES

To launch SCAPES after compiling, in the main directory of SCAPES, run the following command:

    ./SCAPES

## Operation Instructions

You will be shown the SCAPES IDE GUI.
As required by the Deliverable specifications, the functionality of creating a program (essentially enabling the editor window for source code redaction) can be reached by selecting File>New.

As required by the Deliverable specifications, the functionality of saving a program can be reached by selecting File>Save.
A new window will appear. Provide the name of the filename you'd like to save your source code
under.
Accept the dialog after putting in your filename to save the file.

As required by the Deliverable specifications, the functionality of compiling a program can be reached by selecting Program>Compile, and the functionality of running a program can be reached by selecting Program>Run. 

Note that we have also implemented load source file functionality, which can be reached by selecting File>Open.

To verify persistence in a human-readable format, please use either sqlite3 terminal command on the database file created in the directory, or SQLite DB Browser.  
/////COMP3004 Forums clarify that this format is permitted.////////


---

## Source Files

- main.cc - The main file  
- ./Application/Logic/MainController.cc  
- ./Interface/MainWindow.cc  
- ./Interface/UserInputPrompt.cc  
- ./Persistence/DataConductor.cc  
- ./Persistence/FilerSupervisor.cc  
- ./Persistence/PersistenceManager.cc  
- ./Persistence/SQLiteConnector.c  
- ./SCAPL/ArrAccess.cc  
- ./SCAPL/ArrayVariable.cc  
- ./SCAPL/Identifier.cc  
- ./SCAPL/IntegerVariable.cc  
- ./SCAPL/Label.cc  
- ./SCAPL/Literal.cc  
- ./SCAPL/Operand.cc  
- ./SCAPL/Program.cc  
- ./SCAPL/Statement.cc  
- ./SCAPL/Variable.cc  
- ./SCAPL/STMTs/AddStmt.cc  
- ./SCAPL/STMTs/CompStmt.cc  
- ./SCAPL/STMTs/DeclArrStmt.cc  
- ./SCAPL/STMTs/DeclIntStmt.cc  
- ./SCAPL/STMTs/EndStmt.cc  
- ./SCAPL/STMTs/JEqStmt.cc  
- ./SCAPL/STMTs/JLessStmt.cc  
- ./SCAPL/STMTs/JMoreStmt.cc  
- ./SCAPL/STMTs/JumpStmt.cc  
- ./SCAPL/STMTs/MovStmt.cc  
- ./SCAPL/STMTs/PrintStmt.cc  
- ./SCAPL/STMTs/ReadStmt.cc

## Header Files

- ./Application/MainController.h  
- ./Interface/MainWindow.h  
- ./Interface/UserInputPrompt.h  
- ./Persistence/DatabaseConductor.h
- ./Persistence/FileSupervisor.h
- ./Persistence/PersistenceManager.h
- ./Persistence/SQLiteConnector.h
- ./SCAPL/ArrAccess.h
- ./SCAPL/ArrayVariable.h
- ./SCAPL/Identifier.h
- ./SCAPL/IntegerVariable.h
- ./SCAPL/Label.h
- ./SCAPL/Literal.h
- ./SCAPL/Operand.h
- ./SCAPL/Program.h
- ./SCAPL/Statement.h
- ./SCAPL/Value.h
- ./SCAPL/Variable.h
- ./SCAPL/STMTs/AddStmt.h
- ./SCAPL/STMTs/CompStmt.h
- ./SCAPL/STMTs/DeclArrStmt.h
- ./SCAPL/STMTs/DeclIntStmt.h
- ./SCAPL/STMTs/EndStmt.h
- ./SCAPL/STMTs/JEqStmt.h
- ./SCAPL/STMTs/JLessStmt.h
- ./SCAPL/STMTs/JMoreStmt.h
- ./SCAPL/STMTs/JumpStmt.h
- ./SCAPL/STMTs/MovStmt.h
- ./SCAPL/STMTs/PrintStmt.h
- ./SCAPL/STMTs/ReadStmt.h

## Other Files

- D1_T1.scapl  
- D1_T2.scapl  
- D2_T1.scapl
- D2_T2.scapl  
- Makefile  
- README.md  
- SCAPES.pro  
- ./Interface/UserInputPrompt.ui  
- ./Interface/MainWindow.ui  
