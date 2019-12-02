
#include "DatabaseConductor.h"
#include "./../SCAPL/Variable.h"
#include "./../SCAPL/Label.h"

#include <iostream>
#include <string>

using namespace std;

DatabaseConductor::DatabaseConductor()
{
  this->connector = nullptr;
  this->program = nullptr;
  this->identifier_vector = nullptr;
  this->statement_vector = nullptr;
  this->filename="";
}

DatabaseConductor::~DatabaseConductor()
{
}

bool DatabaseConductor::persistProgramObjects(std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  setFilename(filename);
  this->connector = new SQLiteConnector(this->filename);
  this->connector->connect();
  this->identifier_vector = identifier_vector;
  this->statement_vector = statement_vector;

  /**
   * 
   **/
  QSqlQuery sqlcli(this->connector->getSQLiteDatabase());

  //DDL
  sqlcli.exec("DROP TABLE IF EXISTS ANON_OPERAND");
  sqlcli.exec("DROP TABLE IF EXISTS ARRAY_CONTAIN_VAR;");
  sqlcli.exec("DROP TABLE IF EXISTS OPERAND;");
  sqlcli.exec("DROP TABLE IF EXISTS STATEMENT;");
  sqlcli.exec("DROP TABLE IF EXISTS IDENTIFIER;");
  sqlcli.exec("DROP TABLE IF EXISTS STATEMENT_TYPE;");
  sqlcli.exec("DROP TABLE IF EXISTS IDENTIFIER_TYPE;");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS IDENTIFIER_TYPE ("
    "ITID NUMBER(1) PRIMARY KEY,"
    "TYPE_NAME VARCHAR2(64) NOT NULL"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS STATEMENT_TYPE ("
    "STID NUMBER(2) PRIMARY KEY,"
    "TYPE_NAME VARCHAR2(64) NOT NULL"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS IDENTIFIER ("
    "NAME VARCHAR2(64) PRIMARY KEY,"
    "SUBTYPE NUMBER(2) NOT NULL,"
    "VALUE VARCHAR2(64),"
    "FOREIGN KEY(SUBTYPE) REFERENCES IDENTIFIER_TYPE(ITID)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS STATEMENT ("
    "SID INTEGER PRIMARY KEY,"
    "SUBTYPE NUMBER(2) NOT NULL,"
    "LABEL VARCHAR2(64),"
    "FOREIGN KEY(LABEL) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(SUBTYPE) REFERENCES STATEMENT_TYPE(STID)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS OPERAND ("
    "SID NUMBER(3),"
    "OPERNUM NUMBER(1),"
    "IDENTIFIER_NAME VARCHAR2(64) NOT NULL,"
    "PRIMARY KEY(SID, OPERNUM),"
    "FOREIGN KEY(SID) REFERENCES STATEMENT(SID)"
    "FOREIGN KEY(IDENTIFIER_NAME) REFERENCES IDENTIFIER(NAME)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS ANON_OPERAND ("
    "SID NUMBER(3),"
    "OPERNUM NUMBER(1),"
    "IDENTIFIER_NAME VARCHAR2(64) NOT NULL,"
    "VALUE VARCHAR2(64) NOT NULL,"
    "PRIMARY KEY(SID, OPERNUM),"
    "FOREIGN KEY(SID) REFERENCES STATEMENT(SID),"
    "FOREIGN KEY(IDENTIFIER_NAME) REFERENCES IDENTIFIER(NAME)"
    ");");

  //Initial DML
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (0, 'IDENTIFIER');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (1, 'LABEL');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (2, 'VARIABLE');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (3, 'INTEGERVARIABLE');");
  sqlcli.exec("INSERT INTO IDENTIFIER_TYPE VALUES (4, 'ARRAYVARIABLE');");

  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (0, 'STATEMENT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (1, 'READSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (2, 'PRINTSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (3, 'DECLINTSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (4, 'DECLARRSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (5, 'MOVSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (6, 'ADDSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (7, 'COMPSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (8, 'JLESSSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (9, 'JMORESTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (10, 'JEQSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (11, 'JUMPSTMT');");
  sqlcli.exec("INSERT INTO STATEMENT_TYPE VALUES (12, 'ENDSTMT');");

  this->persistIdentifiers();
  this->persistStatements();
  this->persistOperands();

  delete this->connector;
  this->connector = nullptr;
  return true;
}

bool DatabaseConductor::restoreProgramObjects(Program* program, std::vector<Identifier*>* identifier_vector, std::vector<Statement*>* statement_vector, string filename)
{
  setFilename(filename);
  this->connector = new SQLiteConnector(this->filename);
  this->connector->connect();
  this->program = program;

  int i;
  /*
  if(this->identifier_vector != nullptr){
      for(i=0; i < this->identifier_vector->size(); i++){
          delete this->identifier_vector->at(i);
      }
      this->identifier_vector->clear();
  }
  if(identifier_vector != nullptr){
      for(i=0; i< identifier_vector->size(); i++){
          delete identifier_vector->at(i);
      }
      identifier_vector->clear();
  }
  else{
      return false;
  }
  */

  this->identifier_vector = identifier_vector;

  /*
  if(this->statement_vector != nullptr){
      for(i=0; i< this->statement_vector->size(); i++){
          delete this->statement_vector->at(i);
      }
      this->statement_vector->clear();
  }

  if(statement_vector != nullptr){
      for(i=0; i< statement_vector->size(); i++){
          delete statement_vector->at(i);
      }
      statement_vector->clear();
  }
  else{
      return false;
  }
  */

  this->statement_vector = statement_vector;

  /**
   *
   **/
  QSqlQuery sqlcli(this->connector->getSQLiteDatabase());

  this->restoreIdentifiers();
  this->restoreStatements();
  this->restoreOperands();

  //char* tempString;
  if(this->statement_vector != nullptr){
      for(i=0; i< this->statement_vector->size(); i++){
          if(this->statement_vector->at(i) != nullptr){
              //delete tempString;
              //sprintf(tempString, "Statement number %d with type: %s", i, this->statement_vector->at(i)->getName().c_str());
              //sprintf(tempString, "Statement number %d", i);
              //cout << tempString << endl;
              cout << "Statement number " << i << " with type: " << this->statement_vector->at(i)->getName().c_str() << endl;
              if(this->statement_vector->at(i)->getOperand1() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr()->getSubtype().compare("Literal")!=0 && this->statement_vector->at(i)->getOperand1()->getIDPtr()->getSubtype().compare("ArrAccess")!=0){
                  cout << "Operand 1, with name: " << this->statement_vector->at(i)->getOperand1()->getIDPtr()->getNameValue() << endl;
              }
              else if(this->statement_vector->at(i)->getOperand1() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr()->getSubtype().compare("Literal")==0){
                  cout << "Operand 1, with value: " << ((Literal*) this->statement_vector->at(i)->getOperand1()->getIDPtr())->getOut() << endl;
              }
              else if(this->statement_vector->at(i)->getOperand1() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr()->getSubtype().compare("ArrAccess")==0){
                  cout << "Operand 1, with value: " << ((ArrAccess*) this->statement_vector->at(i)->getOperand1()->getIDPtr())->getAccess() << endl;
              }
              if(this->statement_vector->at(i)->getOperand2() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr()->getSubtype().compare("Literal")!=0 && this->statement_vector->at(i)->getOperand2()->getIDPtr()->getSubtype().compare("ArrAccess")!=0){
                  cout << "Operand 2, with name: " << this->statement_vector->at(i)->getOperand2()->getIDPtr()->getNameValue() << endl;
              }
              else if(this->statement_vector->at(i)->getOperand2() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr()->getSubtype().compare("Literal")==0){
                  cout << "Operand 2, with value: " << ((Literal*) this->statement_vector->at(i)->getOperand2()->getIDPtr())->getOut() << endl;
              }
              else if(this->statement_vector->at(i)->getOperand2() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr()->getSubtype().compare("ArrAccess")==0){
                  cout << "Operand 2, with value: " << ((ArrAccess*) this->statement_vector->at(i)->getOperand2()->getIDPtr())->getAccess() << endl;
              }
              if(this->statement_vector->at(i)->getLabel() != nullptr){
                  cout << "Label, with name: " << this->statement_vector->at(i)->getLabel()->getNameValue() << endl;
              }
          }
      }
  }

  this->connector->disconnect();
  delete this->connector;
  this->connector = nullptr;
  return true;
}

string DatabaseConductor::getFilename() const
{
  return this->filename;
}

void DatabaseConductor::setFilename(string newFilename)
{
  this->filename = newFilename;
}

bool DatabaseConductor::persistIdentifiers()
{
    int i;
    char identifierName[64];
    char identifierValue[12];
    char sqlstmt[128];
    string tempName;
    string identifierSubtype;
    QSqlQuery sqlcli(this->connector->getSQLiteDatabase());

    for(i=0; i< this->identifier_vector->size(); i++){
        if(this->identifier_vector->at(i) == nullptr){
            continue;
        }
        sqlstmt[0]='\0';
        identifierSubtype = this->identifier_vector->at(i)->getSubtype();
        identifierValue[0] = 'N';
        identifierValue[1] = 'U';
        identifierValue[2] = 'L';
        identifierValue[3] = 'L';
        identifierValue[4] = '\0';

        if(identifierSubtype.compare("Literal") == 0){
            continue;
        }
        else{
            this->identifier_vector->at(i)->getName(tempName);
            snprintf(identifierName, 63, "%s", tempName.data());
        }
        identifierName[63]='\0';

        if(identifierSubtype.compare("Label") == 0){
            identifierSubtype = "1";
        }

        if(identifierSubtype.compare("IntegerVariable") == 0){
            identifierSubtype = "3";
            sprintf(identifierValue, "%d", ((IntegerVariable*) (this->identifier_vector->at(i)))->getVal());
        }

        if(identifierSubtype.compare("ArrayVariable") == 0){
            identifierSubtype = "4";
        }
        sprintf(sqlstmt, "INSERT INTO IDENTIFIER VALUES('%s', %s, %s);", identifierName, identifierSubtype.data(), identifierValue);
        cout << sqlstmt << endl;
        sqlcli.exec(sqlstmt);
    }
    return true;
}

bool DatabaseConductor::persistStatements()
{
    int i;
    char identifierName[64];
    char sqlstmt[128];
    string tempName;
    string statementSubtype;
    QSqlQuery sqlcli(this->connector->getSQLiteDatabase());
    Identifier* labelPtr;

    for(i=0; i<this->statement_vector->size(); i++){
        if(this->statement_vector->at(i) == nullptr){
            continue;
        }
        sqlstmt[0]='\0';
        identifierName[63]='\0';
        labelPtr = nullptr;
        statementSubtype = this->statement_vector->at(i)->getName();
        identifierName[0] = 'N';
        identifierName[1] = 'U';
        identifierName[2] = 'L';
        identifierName[3] = 'L';
        identifierName[4] = '\0';
        labelPtr = this->statement_vector->at(i)->getLabel();
        if(labelPtr != nullptr){
            labelPtr->getName(tempName);
            if(!tempName.empty()){
                snprintf(identifierName, 63, "%s", tempName.data());
                identifierName[63]='\0';
            }
        }

        if(statementSubtype.compare("ReadStmt") == 0){
            statementSubtype = "1";
        }

        if(statementSubtype.compare("PrintStmt") == 0){
            statementSubtype = "2";
        }

        if(statementSubtype.compare("DeclIntStmt") == 0){
            statementSubtype = "3";
        }

        if(statementSubtype.compare("DeclArrStmt") == 0){
            statementSubtype = "4";
        }

        if(statementSubtype.compare("MovStmt") == 0){
            statementSubtype = "5";
        }

        if(statementSubtype.compare("AddStmt") == 0){
            statementSubtype = "6";
        }

        if(statementSubtype.compare("CompStmt") == 0){
            statementSubtype = "7";
        }

        if(statementSubtype.compare("JLessStmt") == 0){
            statementSubtype = "8";
        }

        if(statementSubtype.compare("JMoreStmt") == 0){
            statementSubtype = "9";
        }

        if(statementSubtype.compare("JEqStmt") == 0){
            statementSubtype = "10";
        }

        if(statementSubtype.compare("JumpStmt") == 0){
            statementSubtype = "11";
        }

        if(statementSubtype.compare("EndStmt") == 0){
            statementSubtype = "12";
        }

        sprintf(sqlstmt, "INSERT INTO STATEMENT VALUES(%d, %s, '%s');", i, statementSubtype.data(), identifierName);
        cout << sqlstmt << endl;
        sqlcli.exec(sqlstmt);
    }
    return true;
}

bool DatabaseConductor::persistOperands()
{
    int i;
        char identifierName[64];
        char identifierValue[64];
        string identifierSubtype;
        char sqlstmt[128];
        std::string tempName;
        QSqlQuery sqlcli(this->connector->getSQLiteDatabase());
        Identifier* idPtr;

        for(i=0; i<this->statement_vector->size(); i++){
            sqlstmt[0]='\0';
            identifierName[0]='\0';
            idPtr = nullptr;
            identifierValue[0] = 'N';
            identifierValue[1] = 'U';
            identifierValue[2] = 'L';
            identifierValue[3] = 'L';
            identifierValue[4] = '\0';

            if(this->statement_vector->at(i)->getOperand1() != nullptr){
                this->statement_vector->at(i)->getOperand1()->getID(&idPtr);
                if(idPtr != nullptr){
                    identifierSubtype = idPtr->getSubtype();
                    if(identifierSubtype.compare("Literal") == 0){
                        snprintf(identifierName, 63, "%s%d_%d", "_LITERAL_", i, 1);
                        sprintf(identifierValue, "%s", ((Literal*) idPtr)->getOut().data());
                        sprintf(sqlstmt, "INSERT INTO ANON_OPERAND VALUES(%d, %d, '%s', '%s');", i, 1, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }else if(identifierSubtype.compare("ArrAccess") == 0 && ((ArrAccess*) idPtr)->getParent() != nullptr &&
                             !((ArrAccess*) idPtr)->getAccess().empty()){
                        snprintf(identifierName, 63, "%s", ((ArrAccess*) idPtr)->getParent()->getNameValue().data());
                        snprintf(identifierValue, 63, "%s", ((ArrAccess*) idPtr)->getAccess().data());
                        sprintf(sqlstmt, "INSERT INTO ANON_OPERAND VALUES(%d, %d, '%s', '%s');", i, 1, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }
                    else{
                        idPtr->getName(tempName);
                        if(!tempName.empty()){
                            snprintf(identifierName, 63, "%s", tempName.data());
                            identifierName[63]='\0';
                            sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %d, '%s');", i, 1, identifierName);
                            cout << sqlstmt << endl;
                            sqlcli.exec(sqlstmt);
                        }
                    }
                }else{
                    cout << "Operand 1 detected as null during statement : " << idPtr << endl;
                }
            }

            sqlstmt[0]='\0';
            identifierName[0]='\0';
            idPtr = nullptr;
            identifierValue[0] = 'N';
            identifierValue[1] = 'U';
            identifierValue[2] = 'L';
            identifierValue[3] = 'L';
            identifierValue[4] = '\0';

            if(this->statement_vector->at(i)->getOperand2() != nullptr){
                this->statement_vector->at(i)->getOperand2()->getID(&idPtr);
                if(idPtr != nullptr){
                    identifierSubtype = idPtr->getSubtype();
                    if(identifierSubtype.compare("Literal") == 0){
                        snprintf(identifierName, 63, "%s%d_%d", "_LITERAL_", i, 2);
                        sprintf(identifierValue, "%s", ((Literal*) idPtr)->getOut().data());
                        sprintf(sqlstmt, "INSERT INTO ANON_OPERAND VALUES(%d, %d, '%s', '%s');", i, 2, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }else if(identifierSubtype.compare("ArrAccess") == 0 && ((ArrAccess*) idPtr)->getParent() != nullptr &&
                             !((ArrAccess*) idPtr)->getAccess().empty()){
                        snprintf(identifierName, 63, "%s", ((ArrAccess*) idPtr)->getParent()->getNameValue().data());
                        snprintf(identifierValue, 63, "%s", ((ArrAccess*) idPtr)->getAccess().data());
                        sprintf(sqlstmt, "INSERT INTO ANON_OPERAND VALUES(%d, %d, '%s', '%s');", i, 2, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }
                    else{
                        idPtr->getName(tempName);
                        if(!tempName.empty()){
                            snprintf(identifierName, 63, "%s", tempName.data());
                            identifierName[63]='\0';
                            sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %d, '%s');", i, 2, identifierName);
                            cout << sqlstmt << endl;
                            sqlcli.exec(sqlstmt);
                        }
                    }
                }else{
                    cout << "Operand 2 detected as null during statement : " << i << endl;
                }
            }

        }
    return true;
}

bool DatabaseConductor::restoreIdentifiers()
{
    /**
     *
     **/
    QSqlQuery sqlcli(this->connector->getSQLiteDatabase());

    sqlcli.exec("SELECT NAME, SUBTYPE, VALUE FROM IDENTIFIER;");
    if(sqlcli.first()){
        do{
            std::string name = sqlcli.value(0).toString().toStdString();
            Identifier* newIdentifierPtr = nullptr;
            if(sqlcli.value(1).toInt()==1){
                newIdentifierPtr = new Label(name);
            }
            else if(sqlcli.value(1).toInt()==3){
                newIdentifierPtr = new IntegerVariable(name);
                if(!sqlcli.value(2).isNull()){
                    ((IntegerVariable*) newIdentifierPtr)->setVal(sqlcli.value(2).toInt());
                }
            }
            else if(sqlcli.value(1).toInt()==4){
                newIdentifierPtr = new ArrayVariable(name);
            }
            if(newIdentifierPtr != nullptr){
                identifier_vector->push_back(newIdentifierPtr);
            }
        }while(sqlcli.next());
    }
    return true;
}

bool DatabaseConductor::restoreStatements()
{
    /**
     *
     **/
    QSqlQuery sqlcli(this->connector->getSQLiteDatabase());
    int i;

    sqlcli.exec("SELECT SID, SUBTYPE, LABEL FROM STATEMENT;");
    if(sqlcli.first()){
        do{
            Statement* newStatementPtr = nullptr;
            if(sqlcli.value(1).toInt()==1){
                newStatementPtr = new ReadStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==2){
                newStatementPtr = new PrintStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==3){
                newStatementPtr = new DeclIntStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==4){
                newStatementPtr = new DeclArrStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==5){
                newStatementPtr = new MovStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==6){
                newStatementPtr = new AddStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==7){
                newStatementPtr = new CompStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==8){
                newStatementPtr = new JLessStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==9){
                newStatementPtr = new JMoreStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==10){
                newStatementPtr = new JEqStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==11){
                newStatementPtr = new JumpStmt(this->program);
            }
            else if(sqlcli.value(1).toInt()==12){
                newStatementPtr = new EndStmt(this->program);
            }
            if(newStatementPtr != nullptr){
                if(!sqlcli.value(2).isNull()){
                    for(i=0; i< this->identifier_vector->size(); i++){
                        if(this->identifier_vector->at(i)->getNameValue().compare(sqlcli.value(2).toString().toStdString()) == 0){
                            newStatementPtr->setLabel((Label *) this->identifier_vector->at(i));
                        }
                    }
                }
                this->statement_vector->push_back(newStatementPtr);
            }
        }while(sqlcli.next());
        return true;
    }
    else{
        return false;
    }
}

bool DatabaseConductor::restoreOperands()
{
    /**
     *
     **/
    QSqlQuery sqlcli(this->connector->getSQLiteDatabase());
    int i;

    sqlcli.exec("SELECT SID, OPERNUM, IDENTIFIER_NAME FROM OPERAND;");
    if(sqlcli.first()){
        do{
            Statement* statementPtr = nullptr;
            if(!sqlcli.value(0).isNull() && this->statement_vector->at(sqlcli.value(0).toInt()) != nullptr){
                statementPtr = this->statement_vector->at(sqlcli.value(0).toInt());
            }
            if(statementPtr != nullptr){
                if(!sqlcli.value(1).isNull() && !sqlcli.value(2).isNull()){
                    for(i=0; i< this->identifier_vector->size(); i++){
                        if(this->identifier_vector->at(i)->getNameValue().compare(sqlcli.value(2).toString().toStdString()) == 0){
                            if(sqlcli.value(1).value<int>() == 1){
                                statementPtr->setOperand1(new Operand(this->identifier_vector->at(i)));
                            }
                            else if(sqlcli.value(1).value<int>() == 2){
                                statementPtr->setOperand2(new Operand(this->identifier_vector->at(i)));
                            }
                        }
                    }
                }
            }
        }while(sqlcli.next());
    }


    sqlcli.exec("SELECT SID, OPERNUM, IDENTIFIER_NAME, VALUE FROM ANON_OPERAND WHERE IDENTIFIER_NAME LIKE '_LITERAL_%';");
    if(sqlcli.first()){
        do{
            Statement* statementPtr = nullptr;
            if(!sqlcli.value(0).isNull() && this->statement_vector->at(sqlcli.value(0).toInt()) != nullptr){
                statementPtr = this->statement_vector->at(sqlcli.value(0).toInt());
            }
            if(statementPtr != nullptr){
                if(!sqlcli.value(1).isNull() && !sqlcli.value(2).isNull() && !sqlcli.value(3).isNull()){
                    if(sqlcli.value(1).value<int>() == 1){
                        statementPtr->setOperand1(new Operand(new Literal(sqlcli.value(3).toString().toStdString())));
                    }
                    else if(sqlcli.value(1).value<int>() == 2){
                        statementPtr->setOperand2(new Operand(new Literal(sqlcli.value(3).toString().toStdString())));
                    }
                }
            }
        }while(sqlcli.next());
    }


    sqlcli.exec("SELECT SID, OPERNUM, IDENTIFIER_NAME, VALUE FROM ANON_OPERAND WHERE IDENTIFIER_NAME NOT LIKE '_LITERAL_%';");
    if(sqlcli.first()){
        do{
            Statement* statementPtr = nullptr;
            if(!sqlcli.value(0).isNull() && this->statement_vector->at(sqlcli.value(0).toInt()) != nullptr){
                statementPtr = this->statement_vector->at(sqlcli.value(0).toInt());
            }
            if(statementPtr != nullptr){
                if(!sqlcli.value(1).isNull() && !sqlcli.value(2).isNull() && !sqlcli.value(3).isNull()){
                    for(i=0; i< this->identifier_vector->size(); i++){
                        if(this->identifier_vector->at(i)->getNameValue().compare(sqlcli.value(2).toString().toStdString()) == 0){
                            if(sqlcli.value(1).value<int>() == 1){
                                statementPtr->setOperand1(new Operand(new ArrAccess((ArrayVariable*) this->identifier_vector->at(i), sqlcli.value(3).toString().toStdString(), this->program)));
                            }
                            else if(sqlcli.value(1).value<int>() == 2){
                                statementPtr->setOperand2(new Operand(new ArrAccess((ArrayVariable*) this->identifier_vector->at(i), sqlcli.value(3).toString().toStdString(), this->program)));
                            }
                        }
                    }
                }
            }
        }while(sqlcli.next());
    }
    return true;
}


//TEMPORARY FOR TESTING
void DatabaseConductor::setProgram(Program* program){
    this->program = program;
}
