
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
  QSqlQuery sqlcli;

  //DDL
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
    "VALUE NUMBER(10),"
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
    "IDENTIFIER_NAME VARCHAR2(64),"
    "OPERNUM NUMBER(1) NOT NULL,"
    "FOREIGN KEY(IDENTIFIER_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(SID, IDENTIFIER_NAME)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS ARRAY_CONTAIN_VAR ("
    "CONTAINER_NAME VARCHAR2(64),"
    "ELEMENT_NAME VARCHAR2(64),"
    "ELEMENT_INDEX NUMBER(2) NOT NULL,"
    "FOREIGN KEY(CONTAINER_NAME) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(ELEMENT_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(CONTAINER_NAME, ELEMENT_NAME),"
    "CHECK(CONTAINER_NAME != ELEMENT_NAME)"
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
  
  this->connector->disconnect();
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

  this->identifier_vector = identifier_vector;

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

  this->statement_vector = statement_vector;

  /**
   *
   **/
  QSqlQuery sqlcli;

  //DDL
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
    "VALUE NUMBER(10),"
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
    "IDENTIFIER_NAME VARCHAR2(64),"
    "OPERNUM NUMBER(1) NOT NULL,"
    "FOREIGN KEY(IDENTIFIER_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(SID, IDENTIFIER_NAME)"
    ");");

  sqlcli.exec("CREATE TABLE IF NOT EXISTS ARRAY_CONTAIN_VAR ("
    "CONTAINER_NAME VARCHAR2(64),"
    "ELEMENT_NAME VARCHAR2(64),"
    "ELEMENT_INDEX NUMBER(2) NOT NULL,"
    "FOREIGN KEY(CONTAINER_NAME) REFERENCES IDENTIFIER(NAME),"
    "FOREIGN KEY(ELEMENT_NAME) REFERENCES IDENTIFIER(NAME),"
    "PRIMARY KEY(CONTAINER_NAME, ELEMENT_NAME),"
    "CHECK(CONTAINER_NAME != ELEMENT_NAME)"
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


  sqlcli.exec("INSERT INTO IDENTIFIER VALUES ('variableA', 2, '0');");
  sqlcli.exec("INSERT INTO IDENTIFIER VALUES ('variableB', 2, '0');");
  sqlcli.exec("INSERT INTO IDENTIFIER VALUES ('L1', 1, NULL);");
  sqlcli.exec("INSERT INTO IDENTIFIER VALUES ('L2', 1, NULL);");

  sqlcli.exec("INSERT INTO STATEMENT VALUES (0, 3, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (1, 3, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (2, 1, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (3, 1, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (4, 7, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (5, 9, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (6, 2, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (7, 11, NULL);");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (8, 2, 'L1');");
  sqlcli.exec("INSERT INTO STATEMENT VALUES (9, 12, 'L2');");

  sqlcli.exec("INSERT INTO OPERAND VALUES (0, 'variableA', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (1, 'variableB', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (2, 'variableA', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (3, 'variableB', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (4, 'variableA', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (4, 'variableB', 2);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (5, 'L1', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (6, 'variableB', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (7, 'L2', 1);");
  sqlcli.exec("INSERT INTO OPERAND VALUES (8, 'variableA', 1);");

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
              if(this->statement_vector->at(i)->getOperand1() != nullptr && this->statement_vector->at(i)->getOperand1()->getIDPtr() != nullptr){
                  cout << "Operand 1, with name: " << this->statement_vector->at(i)->getOperand1()->getIDPtr()->getNameValue() << endl;
              }
              if(this->statement_vector->at(i)->getOperand2() != nullptr && this->statement_vector->at(i)->getOperand2()->getIDPtr() != nullptr){
                  cout << "Operand 2, with name: " << this->statement_vector->at(i)->getOperand2()->getIDPtr()->getNameValue() << endl;
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
    int tempInt;
    char identifierName[64];
    char identifierValue[12];
    char sqlstmt[128];
    string tempName;
    string identifierSubtype;
    QSqlQuery sqlcli;

    for(i=0; i< this->identifier_vector->size(); i++){
        sqlstmt[0]='\0';
        this->identifier_vector->at(i)->getName(tempName);
        snprintf(identifierName, 63, "%s", tempName.data());
        identifierName[63]='\0';
        //this->identifier_vector->at(i)->getSubtype(identifierSubtype);
        //identifierSubtype = this->identifier_vector->at(i)->getSubtype();

        if(identifierSubtype.compare("Label") == 0){
            identifierSubtype = "1";
            identifierValue[0] = 'N';
            identifierValue[1] = 'U';
            identifierValue[2] = 'L';
            identifierValue[3] = 'L';
            identifierValue[4] = '\0';
        }

        if(identifierSubtype.compare("Variable") == 0){
            identifierSubtype = "2";
            ((Variable*) (this->identifier_vector->at(i)))->getVal(tempInt);
            sprintf(identifierValue, "%d", tempInt);
        }
        sprintf(sqlstmt, "INSERT INTO IDENTIFIER VALUES('%s', %s, %s);", identifierName, identifierSubtype.data(), identifierValue);
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
    string compiledStatementSubtype;
    QSqlQuery sqlcli;
    Identifier* idPtr;

    for(i=0; i<this->statement_vector->size(); i++){
        sqlstmt[0]='\0';
        identifierName[0]='\0';
        snprintf(identifierName, 63, tempName.data());
        identifierName[63]='\0';
        compiledStatementSubtype = this->statement_vector->at(i)->getName();

        if(compiledStatementSubtype.compare("DeclIntStmt") == 0 ||
                compiledStatementSubtype.compare("ReadStmt") == 0 ||
                compiledStatementSubtype.compare("PrintStmt") == 0 ||
                compiledStatementSubtype.compare("CompStmt") == 0 ||
                compiledStatementSubtype.compare("EndStmt") == 0){
            identifierName[0] = 'N';
            identifierName[1] = 'U';
            identifierName[2] = 'L';
            identifierName[3] = 'L';
            identifierName[4] = '\0';
        }
        else{
            idPtr = this->statement_vector->at(i)->getLabel();
            if(idPtr != nullptr){
                idPtr->getName(tempName);
                snprintf(identifierName, 63, "%s", tempName.data());
                identifierName[63]='\0';
            }
            else{
                identifierName[0] = 'N';
                identifierName[1] = 'U';
                identifierName[2] = 'L';
                identifierName[3] = 'L';
                identifierName[4] = '\0';
            }
        }

        if(compiledStatementSubtype.compare("ReadStmt") == 0){
            compiledStatementSubtype = "1";
        }


        if(compiledStatementSubtype.compare("PrintStmt") == 0){
            compiledStatementSubtype = "2";
        }

        if(compiledStatementSubtype.compare("DeclIntStmt") == 0){
            compiledStatementSubtype = "3";
        }


        if(compiledStatementSubtype.compare("CompStmt") == 0){
            compiledStatementSubtype = "7";
        }


        if(compiledStatementSubtype.compare("JMoreStmt") == 0){
            compiledStatementSubtype = "9";
        }


        if(compiledStatementSubtype.compare("JumpStmt") == 0){
            compiledStatementSubtype = "11";
        }


        if(compiledStatementSubtype.compare("EndStmt") == 0){
            compiledStatementSubtype = "12";
        }

        sprintf(sqlstmt, "INSERT INTO STATEMENT VALUES(%d, %s, %s);", i, compiledStatementSubtype.data(), identifierName);
        sqlcli.exec(sqlstmt);
        sqlstmt[0]='\0';
        identifierName[0]='\0';
    }
    return true;
}

bool DatabaseConductor::persistOperands()
{
    int i;
    char identifierName[64];
    char sqlstmt[128];
    std::string tempName;
    QSqlQuery sqlcli;
    Identifier* idPtr;

    for(i=0; i<this->statement_vector->size(); i++){
        sqlstmt[0]='\0';
        identifierName[0]='\0';

        if(this->statement_vector->at(i)->getOperand1() != nullptr){
            this->statement_vector->at(i)->getOperand1()->getID(idPtr);
            if(idPtr){
                try {
                    idPtr->getName(tempName);
                    snprintf(identifierName, 63, "%s", tempName.data());
                    identifierName[63]='\0';
                    int example1 = 1;
                    int example2 = 1;
                    sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %s, %d);", i, identifierName, 1);
                    sqlcli.exec(sqlstmt);
                    sqlstmt[0]='\0';
                }
                catch (int exception)
                {
                }
            }
        }

        if(this->statement_vector->at(i)->getOperand2() != nullptr){
            this->statement_vector->at(i)->getOperand2()->getID(idPtr);
            if(idPtr != nullptr){
                tempName = idPtr->getNameValue();
                snprintf(identifierName, 63, "%s", tempName.data());
                identifierName[63]='\0';
                sprintf(sqlstmt, "INSERT INTO OPERAND VALUES(%d, %s, %d);", i, idPtr->getNameValue().data(), 2);
                sqlcli.exec(sqlstmt);
                sqlstmt[0]='\0';
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
    QSqlQuery sqlcli;

    sqlcli.exec("SELECT NAME, SUBTYPE, VALUE FROM IDENTIFIER;");
    if(sqlcli.first()){
        do{
            std::string name = sqlcli.value(0).toString().toStdString();
            Identifier* newIdentifierPtr = nullptr;
            if(sqlcli.value(1).toInt()==1){
                newIdentifierPtr = new Label(name);
            }
            else if(sqlcli.value(1).toInt()==2){
                newIdentifierPtr = new Variable(name);
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
    QSqlQuery sqlcli;
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
    QSqlQuery sqlcli;
    int i;

    sqlcli.exec("SELECT SID, IDENTIFIER_NAME, OPERNUM FROM OPERAND;");
    if(sqlcli.first()){
        do{
            Statement* statementPtr = nullptr;
            if(!sqlcli.value(0).isNull() && this->statement_vector->at(sqlcli.value(0).toInt()) != nullptr){
                statementPtr = this->statement_vector->at(sqlcli.value(0).toInt());
            }
            if(statementPtr != nullptr){
                if(!sqlcli.value(1).isNull() && !sqlcli.value(2).isNull()){
                    for(i=0; i< this->identifier_vector->size(); i++){
                        if(this->identifier_vector->at(i)->getNameValue().compare(sqlcli.value(1).toString().toStdString()) == 0){
                            if(sqlcli.value(2).value<int>() == 1){
                                statementPtr->setOperand1(new Operand(this->identifier_vector->at(i)));
                            }
                            else if(sqlcli.value(2).value<int>() == 2){
                                statementPtr->setOperand2(new Operand(this->identifier_vector->at(i)));
                            }
                        }
                    }
                }
            }
        }while(sqlcli.next());
    }
    return true;
}
