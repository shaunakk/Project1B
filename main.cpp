#include <iostream>
#include <fstream>
#include "dictionary.h"
using namespace std;
int main(int argc, char *argv[])
{
    ifstream hashArgs(argv[1]);
    Dictionary table(argv[2], argv[1]);
    // cout
    //     << "Queries:" << endl;
    ifstream queries(argv[3]);
    string query;
    while (getline(queries, query))
    {
        table.find(query);
    }
}