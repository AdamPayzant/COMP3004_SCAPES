#include "ReadStmt.h"
#include "../Program.h"
#include <iostream>

ReadStmt::ReadStmt(Program *p) {
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = p;
    subtype = "ReadStmt";
}

ReadStmt::~ReadStmt() {
    delete(o1);
}

void ReadStmt::compile(std::string &line) {
    int i = line.size() - 1;
    std::vector<Identifier*> *ids = master->getIds();

    if(line[4] == '$') {
        // Array case
        std::string arrName;
        std::string accessName;
        int j;
        for(j = 6; j < line.size(); j++) {
            if(line.at(j) == '+') {
                arrName = line.substr(5, j - 5);
                break;
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
        // Variable case
        for(auto iter = ids->begin(); iter != ids->end(); ++iter) {
            std::string temp;
            (*iter)->getName(temp);
            if(temp.compare(line.substr(5, i - 4)) == 0) {
                o1 = new Operand(*iter);
            }
        }
    }
}

void ReadStmt::run() {
    std::cout<<"beginning of run stmt"<<std::endl;
    std::string s = master->getUserInput();
    std::cout<<"user inputted: "<<s<<std::endl;
    int input = std::stoi(s);
    std::cout<<"to int: "<<input<<std::endl;
    std::cout<<"subtype: "<<o2->getIDPtr()->getSubtype()<<std::endl;
    o2->setVal(8);
    std::cout<<"o2 value: "<<o2->getVal()<<std::endl;
    std::cout<<"end of run stmt"<<std::endl;
}
