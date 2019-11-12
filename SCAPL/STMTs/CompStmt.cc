/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 *
 * Version 1.0:
 * File: SQLiteConnector.h
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



#include "CompStmt.h"
#include "../Program.h"

CompStmt::CompStmt(Program *p) {
    master = p;
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}
/**
* Compile fuction makes the objects for the jump operation
**/
bool CompStmt::compile(std::string &line) {
    // Syntax is "cmp <first value> <second value>"
    std::string operand = line.substr(4, line.size()-4);
    std::string oone;
    std::string otwo;
    bool synCheck = false;
    for(int i = 0; i < operand.size(); i++) {
        if(operand.at(i) == ' ') {
            if(synCheck) {
                return(false);
            }
            else {
                oone = operand.substr(0, i);
                otwo = operand.substr(i+1, line.size()-i);
                synCheck = true;
            }
        }
    }

    std::vector<Identifier*> *ids;
    ids = master->getIds();
    for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
        std::string temp;
        (*iter)->getName(temp);
        if(temp.compare(oone) == 0) {
            o1 = new Operand(*iter);
        }
        else if(temp.compare(otwo) == 0) {
            o2 = new Operand(*iter);
        }
    }
    if(o1 == nullptr || o2 == nullptr) {
        return(false);
    }
    return(true);
    // TODO: Create error case if one or both operands are unassigned
}

/**
* run function produces the result of the run fuction
**/
void CompStmt::run() {

}
