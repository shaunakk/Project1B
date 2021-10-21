#ifndef HASHBUCKET_H
#define HASHBUCKET_H
#include <string>
#include <iostream>
#include <vector>
#include "hash24.h"
using namespace std;
class Hashbucket
{
public:
    Hashbucket(){};
    void addElement(string word)
    {

        if (count == 0)
        {
            arr = new string[size]();
        }
        arr[count] = word;
        count++;
    };
    void createHashmap()
    {
        if (size == 0)
            return;
        if (size > 1)
        {
            numberTries++;
            mapExists = true;
            secondMap = new string[size * size];
            clearMap();
            hash = Hash24();
            for (int i = 0; i < size; i++)
            {
                if (secondMap[modHash(arr[i])] != " null ")
                {

                    createHashmap();
                    return;
                }
                else
                    secondMap[modHash(arr[i])] = arr[i];
            }
        }
        else
            singleWord = arr[0];
    }
    void increment() { size++; }
    void decrement() { size--; }
    int getSize() { return size; }
    int getCount() { return count; }
    string *getWords() { return arr; }
    string *getSecondMap() { return secondMap; }
    int numberTries = 0;
    string singleWord;

    int modHash(string s) { return hash.hash(s) % (size * size); }
    bool mapExists = false;

private:
    Hash24 hash;
    string *arr;

    void clearMap()
    {
        for (int i = 0; i < size * size; i++)
        {
            secondMap[i] = " null ";
        }
    }
    string *secondMap;
    int size = 0;
    int count = 0;
};
#endif
