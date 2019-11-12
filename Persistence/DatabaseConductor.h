#ifndef DATABASECONDUCTOR_H
#define DATABASECONDUCTOR_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <string>
#include <stdio.h>
using namespace std;

#include "SQLiteConnector.h"
#include "./../SCAPL/Identifier.h"
#include "./../SCAPL/Statement.h"

#define MAX_IDENTIFIER_ARRAY_SIZE 256
#define MAX_STATEMENT_ARRAY_SIZE 128

/**
 * Program: School of Computer Science Assembly Programming Environment System
 * Author: //TODO: Team Name
 * Date: 12/11/2019
 * 
 * Version 1.0:
 * File: DatabaseConductor.h
 * Author: Mathieu Leblanc
 * Date: 12/11/2019
 * 
 * File Purpose:
 *     Used to create a DatabaseConductor object, which will be used to
 * coordinate the management of a connection with a local SQLite Database, 
 * generate any calls for update or querying operations that must be done 
 * on the database, as well as the generation of instances of objects from 
 * query results.
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
class DatabaseConductor
{
  public:
    /**
     * 
     **/
    DatabaseConductor();

    /**
     * Destructor
     **/
    ~DatabaseConductor();

    /**
     * 
     **/
    bool persistProgramObjects(std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     * 
     **/ 
    bool restoreProgramObjects(std::vector<Identifier*>*, std::vector<Statement*>*, string);

    /**
     * Getter function used to get the current value of the source code's 
     * file name.
     **/
    string getFilename() const;

    /**
     * Setter function used to set the value of the source code's file name.
     * Cannot change the file name while a connection to a database is open.
     * Parameters:
     * - Reference to string variable that is holding a source file name.
     **/
    void setFilename(string);

  private:
    /**
     * 
     **/
    SQLiteConnector* connector;

    /**
     * 
     **/
    std::vector<Identifier*>* identifier_vector;

    /**
     * 
     **/
    std::vector<Statement*>* statement_vector;

    /**
     *
     **/
    string filename;

    /**
     * 
     **/
    bool persistIdentifiers();

    /**
     * 
     **/
    bool persistStatements();

    /**
     * 
     **/
    bool restoreIdentifiers();

    /**
     * 
     **/
    bool restoreStatements();
};

#endif
