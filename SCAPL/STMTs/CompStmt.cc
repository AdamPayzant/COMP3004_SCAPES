#include "CompStmt.h"
#include "../Program.h"

CompStmt::CompStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "CompStmt";
}

CompStmt::~CompStmt() {
    delete(o1);
    delete(o2);
}


void CompStmt::compile(std::string &line) {
    // TODO: Either operand can be a literal or array value
    // Syntax is "cmp <first value> <second value>"
    int i;
    std::vector<Identifier*> *ids = master->getIds();

    for(i = 5; i < line.size(); i++) {
        if(line[i] == ' ') {
            break;
        }
    }
    if(isdigit(line[4])) {
        std::string v = line.substr(5, i - 4);
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
                ArrAccess *temp = new ArrAccess(downcast, accessName, master);
                o1 = new Operand(temp);
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

    if(isdigit(line[i+1])) {
        std::string v = line.substr(i+1, line.size() - i - 1);
        Literal *temp = new Literal(v);
        o1 = new Operand(temp);
    }
    else if(line[i+1] == '$') {
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
                ArrAccess *temp = new ArrAccess(downcast, accessName, master);
                o2 = new Operand(temp);
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


void CompStmt::run() {
    int val1 = o1->getVal();
    int val2 = o2->getVal();
    if(val1 > val2) {
        master->setCFlag(1);
    }
    else if (val1 < val2) {
        master->setCFlag(-1);
    }
    else {
        master->setCFlag(0);
    }
}
