
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
  sqlcli.exec("DROP TABLE IF EXISTS ARRACCESS");
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

  std::string variable_name = "a";
  this->identifier_vector->push_back(new IntegerVariable(variable_name));
  this->statement_vector->push_back(new DeclIntStmt(this->program));
  this->statement_vector->at(0)->setOperand1(new Operand(this->identifier_vector->at(0)));

  variable_name = "b";
  this->identifier_vector->push_back(new IntegerVariable(variable_name));
  this->statement_vector->push_back(new DeclIntStmt(this->program));
  Operand * example = new Operand(this->identifier_vector->at((1)));
  Identifier * examplePtr = nullptr;
  example->getID(&examplePtr);
  cout << "This is an example for operand with identifier pointer: " << example->getIDPtr() << endl;
  cout << "This is an example for operand with identifier pointer: " << examplePtr << endl;
  this->statement_vector->at(1)->setOperand1(new Operand(this->identifier_vector->at(1)));

  this->statement_vector->push_back(new ReadStmt(this->program));
  this->statement_vector->at(2)->setOperand1(new Operand(this->identifier_vector->at(0)));

  this->statement_vector->push_back(new ReadStmt(this->program));
  this->statement_vector->at(3)->setOperand1(new Operand(this->identifier_vector->at(1)));

  this->statement_vector->push_back(new CompStmt(this->program));
  this->statement_vector->at(4)->setOperand1(new Operand(this->identifier_vector->at(0)));
  this->statement_vector->at(4)->setOperand2(new Operand(this->identifier_vector->at(1)));

  variable_name = "L1";
  this->identifier_vector->push_back(new Label(variable_name));
  this->statement_vector->push_back(new JMoreStmt(this->program));
  this->statement_vector->at(5)->setOperand1(new Operand(this->identifier_vector->at(2)));

  this->statement_vector->push_back(new PrintStmt(this->program));
  this->statement_vector->at(6)->setOperand1(new Operand(this->identifier_vector->at(1)));

  variable_name = "L2";
  this->identifier_vector->push_back(new Label(variable_name));
  this->statement_vector->push_back(new JumpStmt(this->program));
  this->statement_vector->at(7)->setOperand1(new Operand(this->identifier_vector->at(3)));

  this->statement_vector->push_back(new PrintStmt(this->program));
  this->statement_vector->at(8)->setOperand1(new Operand(this->identifier_vector->at(0)));
  this->statement_vector->at(8)->setLabel((Label *) this->identifier_vector->at(2));

  this->statement_vector->push_back(new EndStmt(this->program));
  this->statement_vector->at(9)->setLabel((Label *) this->identifier_vector->at(3));


  this->persistIdentifiers();
  this->persistStatements();
  this->persistOperands();
  
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
    char identifierName[64];
    char identifierValue[12];
    char sqlstmt[128];
    string tempName;
    string identifierSubtype;
    QSqlQuery sqlcli;

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
    QSqlQuery sqlcli;
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
        QSqlQuery sqlcli;
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
                        sprintf(sqlstmt, "INSERT INTO LITERAL_OPERAND VALUES(%d, %d, '%s', '%s');", i, 1, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }else if(identifierSubtype.compare("ArrAccess") == 0 && ((ArrAccess*) idPtr)->getParent() != nullptr &&
                             !((ArrAccess*) idPtr)->getAccess().empty()){
                        snprintf(identifierName, 63, "%s", ((ArrAccess*) idPtr)->getParent()->getNameValue().data());
                        snprintf(identifierValue, 63, "%s", ((ArrAccess*) idPtr)->getAccess().data());
                        sprintf(sqlstmt, "INSERT INTO ARRACCESS_OPERAND VALUES(%d, %d, '%s', '%s');", i, 1, identifierName, identifierValue);
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

                cout << "Operand 2 not detected as null during statement : " << i << endl;
                this->statement_vector->at(i)->getOperand2()->getID(&idPtr);
                if(idPtr != nullptr){
                    identifierSubtype = idPtr->getSubtype();
                    if(identifierSubtype.compare("Literal") == 0){
                        snprintf(identifierName, 63, "%s%d_%d", "_LITERAL_", i, 2);
                        sprintf(identifierValue, "%s", ((Literal*) idPtr)->getOut().data());
                        sprintf(sqlstmt, "INSERT INTO LITERAL_OPERAND VALUES(%d, %d, '%s', '%s');", i, 2, identifierName, identifierValue);
                        cout << sqlstmt << endl;
                        sqlcli.exec(sqlstmt);
                    }else if(identifierSubtype.compare("ArrAccess") == 0 && ((ArrAccess*) idPtr)->getParent() != nullptr &&
                             !((ArrAccess*) idPtr)->getAccess().empty()){
                        snprintf(identifierName, 63, "%s", ((ArrAccess*) idPtr)->getParent()->getNameValue().data());
                        snprintf(identifierValue, 63, "%s", ((ArrAccess*) idPtr)->getAccess().data());
                        sprintf(sqlstmt, "INSERT INTO ARRACCESS_OPERAND VALUES(%d, %d, '%s', '%s');", i, 2, identifierName, identifierValue);
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

    return true;
}

bool DatabaseConductor::restoreStatements()
{
    return true;
}

bool DatabaseConductor::restoreOperands()
{

    return true;
}


//TEMPORARY FOR TESTING
void DatabaseConductor::setProgram(Program* program){
    this->program = program;
}
