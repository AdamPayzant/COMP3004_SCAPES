#include "Program.h"

Program::Program(std::string &f) {
    filename = f;
}

Program::~Program() {
    for(auto s : *stmts) {
        delete(s);
    }
    stmts->clear();
    for(auto id : *ids) {
        delete(id);
    }
    ids->clear();
}

void Program::compile() {
    std::ifstream file(filename);
    // Just a big 'ole map to track statements with their switch options
    std::map<std::string, int> stats = {{"dci", 0}, {"dca", 1}, {"rdi", 2},{"prt",3}, {"mov", 4}, {"add", 5}, {"cmp", 6}, {"jls", 7}, {"jmr", 8}, {"jeq", 9}, {"jmp", 10}, {"end", 11}};

    for(std::string line ; getline(file, line); ) {
        if(line[0] != '#') {
            // I'd rather change this to a map of lambas, but scoping, so now we just get a map and switch statments
            int type = stats[line.substr(3)];
            switch (type) {
                case 0:
                    stmts->push_back(new DeclIntStmt(this));
                case 1:
                    stmts->push_back(new DeclArrStmt(this));
                case 2:
                    stmts->push_back(new ReadStmt(this));
                case 3:
                    stmts->push_back(new PrintStmt(this));
                case 4:
                    stmts->push_back(new MovStmt(this));
                case 5:
                    stmts->push_back(new AddStmt(this));
                case 6:
                    stmts->push_back(new CompStmt(this));
                case 7:
                    stmts->push_back(new JLessStmt(this));
                case 8:
                    stmts->push_back(new JMoreStmt(this));
                case 9:
                    stmts->push_back(new JEqStmt(this));
                case 10:
                    stmts->push_back(new JumpStmt(this));
                case 11:
                    stmts->push_back(new EndStmt(this));
            }
            stmts->at(stmts->size())->compile(line);
        }
    }
}

// TODO
void Program::execute() {

}

// TODO
void Program::print() {

}

void Program::getIds(std::vector<Identifier*> *i) {
    i = ids;
}

// returns the pointer to the comparison flag so compare statements can modify it
void Program::getCFlag(int *cFlag) {
    cFlag = &comparisonFlag;
}