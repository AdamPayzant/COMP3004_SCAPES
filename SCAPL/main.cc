#include "Program.h"

#include<iostream>

using namespace std;

int main();

int main() {
    string file = "./Test.SCAPL";
    Program program(file);
    program.compile();

    cout << "Done" << endl;
}