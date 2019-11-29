
#include "AddStmt.h"

AddStmt::AddStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "AddStmt";
}


AddStmt::~AddStmt() {
    delete(o1);
    delete(o2);
}


void AddStmt::compile(std::string &line) {
    // Syntax: add <value> <target>
    int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[i] == ' ') {
            break;
        }
    }
    if(isdigit(line[4])) {
        int v = std::stoi(line.substr(5, i - 4));
        Literal *temp = new Literal(v);
        o1 = new Operand(temp);
    }
    else if(line[4] == '$') {
        // Do the array add-y thing
        std::string arrName;
        std::string accessName;
        int j;
        for(j = 6; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(5, j - 5);
            }
        }
        accessName = line.substr(j + 1, i - j - 1);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName);
                break;
            }
        }
    }
    else {
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(5, i - 4)) == 0) {
                o1 = new Operand(*iter);
            }
        }
    }

    if(line[i+1] == '$') {
        i++;
        std::string arrName;
        std::string accessName;
        int j;
        for(j = i; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(i + 1, j - i - 1);
            }
        }
        accessName = line.substr(j + 1, line.size() - 1 - j);
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string an;
            (*iter)->getName(an);
            if(an.compare(arrName) == 0) {
                ArrayVariable *downcast = (ArrayVariable *) (*iter);
                ArrAccess *temp = new ArrAccess(downcast, accessName);
                break;
            }
        }
    }
    else {
        // Variable
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(i + 1, line.size() - i - 1)) == 0) {
                o2 = new Operand(*iter);
            }
        }
    }
}


void AddStmt::run() {
    // get operands
    // add  number 2 to 1
    // set the value
    o2->setVal(o1->getVal() + o2->getVal());
}

std::string AddStmt::getName() {
  std::string n = "AddStmt";
  return(n);
}