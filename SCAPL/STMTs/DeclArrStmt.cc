#include "DeclArrStmt.h"
#include "../Program.h"

DeclArrStmt::DeclArrStmt(Program *m)
{
    o1 = nullptr;
    o2 = nullptr;
    label = nullptr;
    master = m;
    subtype = "DeclArrStmt";
}

void DeclArrStmt::compile(std::string &line){
    // TODO
    // Syntax dca <name> <size>
    int i;
    for(i = 5; i < line.size(); i++) {
        if(line[i] == ' ') {
            break;
        }
    }

    // Creates the array in Operand 1
    std::string name = line.substr(4, i - 5);
    
    std::vector<Identifier*> *ids;
    ids = master->getIds();
    ArrayVariable *temp = new ArrayVariable(name);
    o1 = new Operand(temp);
    ids->push_back(temp);

    // Gets the size of the array in Operand 2
    if(isdigit(line[i+1])) {
        // Literal case
        Literal *temp = new Literal(line.substr(5, i - 4));
        o1 = new Operand(temp);
    }
    else if(line[i+1] == '$') {
        // Array case
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

void DeclArrStmt::run(){
    ArrayVariable *temp = (ArrayVariable *) o1->getIDPtr();
    temp->create(o2->getVal());
}
