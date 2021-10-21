#include <iostream>
#include <fstream>
#include "dictionary.h"
using namespace std;
int main(int argc, char *argv[])
{
    ifstream hashArgs(argv[1]);
    Dictionary table(argv[1], argv[2]);
    cout
        << "Queries:" << endl;
    ifstream queries(argv[3]);
    string query;
    while (getline(queries, query))
    {
        table.find(query);
    }
}