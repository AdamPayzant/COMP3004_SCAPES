#ifndef USERINPUTPROMPT_H
#define USERINPUTPROMPT_H

#include <QDialog>

#include "ui_UserInputPrompt.h"

using namespace std;

namespace Ui {
    class UserInputPrompt;
}
/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: savewindow.h
 * Author: Zacchaeus Leung
 * Date: 08/11/2019
 *
 * Version 2.0:
 * File: SaveWindow.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 *
 * Version 3.0:
 * File: UserInputPrompt
 * Author: Mathieu Leblanc
 * Date: 05/12/2019
 *
 * File Purpose: Used to create a save window where the user can specify the filename
 * they'd like to use for the file that will store their source code in secondary memory.
 * Please note that at this time directory selection is not available, however it will most
 * likely be implemented for Deliverable 2.
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
class UserInputPrompt : public QDialog
{
    Q_OBJECT

    public:
        /**
         * Constructor
         * Parameters:
         * - Pointer to QWidget object corresponding to the Widget that
         * contains the object
         **/
        explicit UserInputPrompt(QWidget* parent = nullptr, std::string = "Placeholder Text", std::string = "tempInput");

        /**
         * Destructor
         **/
        ~UserInputPrompt();

    private slots:
        /**
         * Handler function used to delegate save operation once accepted.
         **/
        void on_userPromptConfirmationBar_accepted();

        /**
         * Handler function used to discard save operation once rejected.
         **/
        void on_userPromptConfirmationBar_rejected();

    private:
        /**
         * Pointer to the user interface model bound to the current SaveWindow object through
         * the namespace Ui
         **/
        Ui::UserInputPrompt* ui;

        std::string operation;
};

#endif
