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

#include "MainController.h"

MainController::MainController(PersistenceManager* persistenceManagerPtr, MainWindow* mainWindowPtr)
{
    this->persistenceManager = persistenceManagerPtr;
    this->mainWindow = mainWindowPtr;
    this->program = nullptr;
}

MainController::~MainController()
{
}

void MainController::clientRequestHandler(string command)
{
    if(command.compare("save") == 0){
        saveSourceCode();
        return;
    }
    if(command.compare("load") == 0){
        loadSourceCode();
        return;
    }
    if(command.compare("compile") == 0){
        compileSourceCode();
    }
    if(command.compare("run") == 0){
        runCompiledProgram();
    }
    return;
}

void MainController::saveSourceCode()
{
    if(persistenceManager->saveToFile(this->mainWindow->getEditorText(), mainWindow->getProgramFilename())){
        string tempString = "";
        tempString.append("Save operation successful.\nFile ");
        tempString.append(this->mainWindow->getProgramFilename().data());
        tempString.append(".scapl saved to default directory.");
        this->mainWindow->setFeedbackText(tempString);
        this->mainWindow->prepareLoadedWindowState();
    }else{
        this->mainWindow->setFeedbackText("An Error occurred during the save operation.");
    }
}

void MainController::loadSourceCode()
{
    if(persistenceManager->loadFromFile(this->mainWindow->getEditorText(), mainWindow->getProgramFilename())){
        this->mainWindow->refreshEditorText();
        string tempString = "";
        tempString.append("Open operation successful.\nFile ");
        tempString.append(this->mainWindow->getProgramFilename().data());
        tempString.append(".scapl opened from default directory.");
        this->mainWindow->setFeedbackText(tempString);
        this->mainWindow->prepareLoadedWindowState();
    }else{
        this->mainWindow->setFeedbackText("An Error occurred during the open operation.");
    }
}

void MainController::compileSourceCode()
{
    /*
    if(this->program != nullptr){
        delete this->program;
    }
    this->program = nullptr;
    */
    this->program = new Program(mainWindow->getProgramFilename());
    //this->program->compile();


    std::string variable_name = "L1";
    this->program->getIds()->push_back(new Label(variable_name));
    variable_name = "L2";
    this->program->getIds()->push_back(new Label(variable_name));
    variable_name = "L3";
    this->program->getIds()->push_back(new Label(variable_name));
    variable_name = "L4";
    this->program->getIds()->push_back(new Label(variable_name));
    variable_name = "L5";
    this->program->getIds()->push_back(new Label(variable_name));
    variable_name = "L6";
    this->program->getIds()->push_back(new Label(variable_name));

    this->program->getStmts()->push_back(new JumpStmt(this->program));
    this->program->getStmts()->at(0)->setOperand1(new Operand(this->program->getIds()->at(0)));

    variable_name = "a";
    this->program->getIds()->push_back(new IntegerVariable(variable_name));
    this->program->getStmts()->push_back(new DeclIntStmt(this->program));
    this->program->getStmts()->at(1)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(1)->setOperand2(new Operand(new Literal("1")));
    this->program->getStmts()->at(1)->setLabel((Label *) this->program->getIds()->at(0));

    variable_name = "b";
    this->program->getIds()->push_back(new ArrayVariable(variable_name));
    this->program->getStmts()->push_back(new DeclArrStmt(this->program));
    this->program->getStmts()->at(2)->setOperand1(new Operand(this->program->getIds()->at(7)));
    this->program->getStmts()->at(2)->setOperand2(new Operand(new Literal("1")));

    this->program->getStmts()->push_back(new MovStmt(this->program));
    this->program->getStmts()->at(3)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(3)->setOperand2(new Operand(new Literal("1")));

    this->program->getStmts()->push_back(new ReadStmt(this->program));
    this->program->getStmts()->at(4)->setOperand1(new Operand(new ArrAccess((ArrayVariable*)this->program->getIds()->at(7), "1", this->program)));

    this->program->getStmts()->push_back(new AddStmt(this->program));
    this->program->getStmts()->at(5)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(5)->setOperand2(new Operand(new Literal("1")));
    this->program->getStmts()->at(5)->setLabel((Label *) this->program->getIds()->at(1));

    this->program->getStmts()->push_back(new PrintStmt(this->program));
    this->program->getStmts()->at(6)->setOperand1(new Operand(new Literal("jumped to loop")));

    this->program->getStmts()->push_back(new CompStmt(this->program));
    this->program->getStmts()->at(7)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(7)->setOperand2(new Operand(new ArrAccess((ArrayVariable*)this->program->getIds()->at(7), "$b+1", this->program)));

    this->program->getStmts()->push_back(new JLessStmt(this->program));
    this->program->getStmts()->at(8)->setOperand1(new Operand(this->program->getIds()->at(1)));

    this->program->getStmts()->push_back(new JEqStmt(this->program));
    this->program->getStmts()->at(9)->setOperand1(new Operand(this->program->getIds()->at(2)));

    this->program->getStmts()->push_back(new AddStmt(this->program));
    this->program->getStmts()->at(10)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(10)->setOperand2(new Operand(new Literal("1")));
    this->program->getStmts()->at(10)->setLabel((Label *) this->program->getIds()->at(2));

    this->program->getStmts()->push_back(new CompStmt(this->program));
    this->program->getStmts()->at(11)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(11)->setOperand2(new Operand(this->program->getIds()->at(7)));

    this->program->getStmts()->push_back(new JMoreStmt(this->program));
    this->program->getStmts()->at(12)->setOperand1(new Operand(this->program->getIds()->at(3)));

    this->program->getStmts()->push_back(new JLessStmt(this->program));
    this->program->getStmts()->at(13)->setOperand1(new Operand(this->program->getIds()->at(4)));

    this->program->getStmts()->push_back(new PrintStmt(this->program));
    this->program->getStmts()->at(14)->setOperand1(new Operand(new Literal("a is greater than b")));
    this->program->getStmts()->at(14)->setLabel((Label *) this->program->getIds()->at(3));

    this->program->getStmts()->push_back(new JumpStmt(this->program));
    this->program->getStmts()->at(15)->setOperand1(new Operand(this->program->getIds()->at(5)));

    this->program->getStmts()->push_back(new PrintStmt(this->program));
    this->program->getStmts()->at(16)->setOperand1(new Operand(new Literal("a is greater than b")));
    this->program->getStmts()->at(16)->setLabel((Label *) this->program->getIds()->at(4));

    this->program->getStmts()->push_back(new JumpStmt(this->program));
    this->program->getStmts()->at(17)->setOperand1(new Operand(this->program->getIds()->at(5)));

    this->program->getStmts()->push_back(new PrintStmt(this->program));
    this->program->getStmts()->at(18)->setOperand1(new Operand(this->program->getIds()->at(6)));
    this->program->getStmts()->at(18)->setLabel((Label *) this->program->getIds()->at(5));

    this->program->getStmts()->push_back(new PrintStmt(this->program));
    this->program->getStmts()->at(19)->setOperand1(new Operand(this->program->getIds()->at(7)));

    this->program->getStmts()->push_back(new EndStmt(this->program));


    this->persistenceManager->setDBCProgram(this->program);
    this->persistenceManager->persistProgramObjects(this->program->getIds(), this->program->getStmts(), mainWindow->getProgramFilename());
}

void MainController::runCompiledProgram()
{
    /*
    if(this->program != nullptr){
        delete this->program;
    }
    this->program = nullptr;
    */
    this->program = new Program(mainWindow->getProgramFilename(), this);
    this->persistenceManager->restoreProgramObjects(this->program, this->program->getIds(), this->program->getStmts(), mainWindow->getProgramFilename());
    this->program->execute();
}

string& MainController::promptUserForInput(){
    this->mainWindow->promptUserForInput("Please provide a value:");
    return this->mainWindow->getTempUserInput();
}
