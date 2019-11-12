

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 *
 * Version 1.0:
 * File: mainWindow.cc
 * Author: Zacchaeus leung
 * Date: 08/11/2019
 *
 * Version 2.0:
 * File: MainWindow.cc
 * Author: Mathieu Leblanc
 * Date 12/11/2019
 *
 * File Purpose:
 *  used to make the main window user interacts with
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 * Connection management operations initially based off example "tablemodel"[1]
 * from Qt Documentation.
 *
 * References:
 * [1] Qt.(2019).Table Model Example.[online]
 *      Available at: https://doc.qt.io/qt-5/qtsql-tablemodel-example.html
 *      [Accessed 12 Nov. 2019].
 *
 * Original Copyright information for the QT Example:
 ** Copyright (C) 2016 The Qt Company Ltd.
 ** Contact: https://www.qt.io/licensing/
 **
 ** This file is part of the examples of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** BSD License Usage
 ** Alternatively, you may use this file under the terms of the BSD license
 ** as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of The Qt Company Ltd nor the names of its
 **     contributors may be used to endorse or promote products derived
 **     from this software without specific prior written permission.
 **
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 **
 ** $QT_END_LICENSE$
 *
 *
 **/

#include "MainWindow.h"

using namespace std;


/**
 * constructor
 * param : Qwiget parent
 **/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainController(nullptr),
    programFilename("")
{
    ui->setupUi(this);
    prepareInitialWindowState();
}
/**
 * Descrtuctor
 **/

MainWindow::~MainWindow()
{
    delete ui;
}
/**
 *
 * Return the current source code
 **/
string MainWindow::getEditorText()
{
    return (ui->sourceTextWindow->toPlainText()).toUtf8().constData();
}

/**
 * set the editor text giving the user the source code to modify
 **/

void MainWindow::setEditorText(string text)
{
    ui->sourceTextWindow->setText(QString::fromStdString(text));
}
/**
 * constructor
 **/

void MainWindow::setFeedbackText(string text)
{
    ui->feedbackWindow->setText(QString::fromStdString(text));
}
/**
 * return main controller
 **/
MainController* MainWindow::getMainController()
{
    return this->mainController;
}

/**
 *  set mian controlelr
 **/
void MainWindow::setMainController(MainController* controllerPtr)
{
    this->mainController = controllerPtr;
}

string& MainWindow::getProgramFilename()
{
    return this->programFilename;
}

/**
 *  set main controlelr
 **/
void MainWindow:: setProgramFilename(string newFilename)
{
    this->programFilename = newFilename;
}

/**
 *  set menu giving description on instructions
 **/
void MainWindow::on_menuButtonNewOption_triggered()
{
    ui->sourceTextWindow->setReadOnly(false);
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setText("Editor window cleared for new source file.\n"
                                "To save your source file, please use the 'Save' menu option.\n"
                                "To compile your source file, please use the 'Compile' menu option.\n"
                                "Clarifications on program details or functionality can be found under the "
                                "'Help' menu option of the menu bar.\n\n"
                                "Please note that creating a new source file using the 'New' menu option without "
                                "saving your current source file will result in the loss of any unsaved changes.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
}
/**
 * open button trigger will get a filename from the user to open
 **/

void MainWindow::on_menuButtonOpenOption_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home", tr("txt files (*.txt)"));
    programFilename = fileName.toUtf8().constData();
    mainController->clientRequestHandler("load");

    ui->sourceTextWindow->setReadOnly(false);
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->show();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(255,255,255));
    ui->feedbackWindow->setText("Editor window cleared for new source file.\n"
                                "To save your source file, please use the 'Save' menu option.\n"
                                "To compile your source file, please use the 'Compile' menu option.\n"
                                "Clarifications on program details or functionality can be found under the "
                                "'Help' menu option of the menu bar.\n\n"
                                "Please note that creating a new source file using the 'New' menu option without "
                                "saving your current source file will result in the loss of any unsaved changes.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->menuButtonSaveOption->setEnabled(true);
    ui->menuButtonCloseOption->setEnabled(true);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
}

/**
 *  set main controller
 **/
void MainWindow::on_menuButtonSaveOption_triggered()
{
    SaveWindow* saveWindow = new SaveWindow(this);
    ui->menuButtonCompileOption->setEnabled(true);
    ui->menuButtonRunOption->setEnabled(true);
    saveWindow->show();
}
/**
 *  trigger inital state when the close is pressed
 **/
void MainWindow::on_menuButtonCloseOption_triggered()
{
    prepareInitialWindowState();
}
/**
 *  Compiler is clicked the clientRequestHandler is triggerd
 **/
void MainWindow::on_menuButtonCompileOption_triggered()
{
    mainController->clientRequestHandler("compile");

}

void MainWindow::on_menuButtonRunOption_triggered()
{
}

void MainWindow::on_menuButtonFuncDescOption_triggered()
{
}

void MainWindow::on_menuButtonAboutOption_triggered()
{
}

/**
 * set the inital state and set the feedback window
 **/

void MainWindow::prepareInitialWindowState()
{
    ui->sourceTextWindow->setReadOnly(true);
    ui->sourceTextWindow->setText("");
    ui->sourceTextWindow->hide();
    QPalette feedbackPalette;
    feedbackPalette.setColor(QPalette::Base, QColor(220,220,220));
    ui->feedbackWindow->setText("To display the editor window, please create ('New' menu option) "
                                "or open ('Open' menu option) a file.");
    ui->feedbackWindow->setPalette(feedbackPalette);
    ui->feedbackWindow->setReadOnly(true);
    ui->menuButtonSaveOption->setEnabled(false);
    ui->menuButtonCloseOption->setEnabled(false);
    ui->menuButtonCompileOption->setEnabled(false);
    ui->menuButtonRunOption->setEnabled(false);
}
