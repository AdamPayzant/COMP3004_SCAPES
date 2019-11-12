#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QFileDialog>
#include <QString>
#include <QInputDialog>
#include <QFile>
#include <iostream>

#include "./../ui_MainWindow.h"
#include "./../ApplicationLogic/MainController.h"
#include "SaveWindow.h"
using namespace std;

namespace Ui {
    class MainWindow;
}

class MainController;
/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: mainWindow.h
 * Author: Zacc
 * Date: 08/11/2019
 *
 * Version 2.0:
 * File: MainWindow.h
 * Author: Mathieu Leblanc
 * Date 12/11/2019
 *
 * File Purpose: Used to create the main window of the SCAPES application, from which the user
 * will be able to create a source file, open an existing source file, save the current source
 * file in the editor window, close the current source file, compile the current source file, or
 * run the compiled version of the current source file if found in storage.
 *
 * Formatting style based on course notes and course work from COMP2401 and
 * COMP2404.
 * Class design based on course notes and course work from Fall 2018 offering
 * of COMP2404.
 * User interface creation and management operations initially based off example "application"[1]
 * from Qt Documentation.
 *
 * References:
 * [1] Qt.(2019).Application Example.[online]
 *      Available at: https://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
 *      [Accessed 08 Nov. 2019].
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
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        /**
         *Consturctor
         * Default constructor
         **/
        explicit MainWindow(QWidget *parent = nullptr);

        /**
         *Distructor
         **/
        ~MainWindow();

        /**
        *
        * retrieves the text from the Editor textbox
        **/
        string getEditorText();

        /**
        * set the editor text for the
        *
        **/
        void setEditorText(string text);

        /**
         * sets the feedback text
         **/
        void setFeedbackText(string text);

        /**
         * returns the controller object to call other fuctions
         **/
        MainController* getMainController();

        /**
         * sets main controller
         **/
        void setMainController(MainController*);

        /**
         * get the file name for saving
         **/
        string& getProgramFilename();

        /**
         * set the file name for a drectory to save
         **/
        void setProgramFilename(string);

    private slots:
        /**
         * trigger new button
         **/
        void on_menuButtonNewOption_triggered();

        /**
         * trigger open button
         **/
        void on_menuButtonOpenOption_triggered();

        /**
         * trigger save button
         **/
        void on_menuButtonSaveOption_triggered();

        /**
         * trigger close
         **/
        void on_menuButtonCloseOption_triggered();

        /**
         *
         **/
        void on_menuButtonCompileOption_triggered();

        /**
         *
         **/
        void on_menuButtonRunOption_triggered();

        /**
         *trigger description button
         **/
        void on_menuButtonFuncDescOption_triggered();

        /**
         * trigger about button
         **/
        void on_menuButtonAboutOption_triggered();

    private:

        /**
         * ui object pointer
         **/
        Ui::MainWindow *ui;

        /**
         * the main controller object
         **/
        MainController* mainController;

        /**
         * filename to be saved
         **/
        string  programFilename;

        /**
         * inital state of the window
         **/
        void prepareInitialWindowState();

};

#endif
