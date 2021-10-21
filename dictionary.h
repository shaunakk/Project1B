#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "hashbucket.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include "hash24.h"
using namespace std;

class Dictionary
{
public:
    Dictionary(string fname, string paramFileName)
    {
        ifstream hashArgs(paramFileName);
        int a, b, c;
        hashArgs >> size;
        hashArgs >> a;
        hashArgs >> b;
        hashArgs >> c;
        hash = Hash24(a, b, c);
        table = new Hashbucket[size]();
        ifstream inputFile(fname);
        string word;
        while (getline(inputFile, word))
        {
            firstPass(word);
        }
        inputFile.clear();
        inputFile.seekg(0, ios::beg);
        while (getline(inputFile, word))
        {
            secondPass(word);
        }

        for (int i = 0; i < size; i++)
        {
            table[i].createHashmap();
        }
        displayStats();
    };
    void firstPass(string element)
    {
        table[modHash(element)].increment();
    }
    void secondPass(string element)
    {
        if (!findBool(element))
            table[modHash(element)].addElement(element);
        else
        {
            duplicates++;
            table[modHash(element)].decrement();
        }
    }
    void displayStats()
    {
        int numberOfTries[21] = {0};
        int wordsInBuckets[21] = {0};
        int totalWords = 0;
        int maxCollisions = 0;
        int maxCollisionsIndex = 0;
        double averageFunctionsTried = 0;
        for (int i = 0; i < size; i++)
        {
            int bucketSize = table[i].getSize();
            int numberTries = table[i].numberTries;
            if (bucketSize > maxCollisions)
            {
                maxCollisionsIndex = i;
                maxCollisions = bucketSize;
            }
            if (numberTries <= 20)
                numberOfTries[numberTries] += 1;
            if (bucketSize <= 20)
                wordsInBuckets[bucketSize] += 1;
            totalWords += bucketSize;
        }
        if (maxCollisions == 1)
            maxCollisions = 0;
        hash.dump();
        cout
            << "Number of words = " << totalWords << endl
            << "Table size = " << size << endl
            << "Max collisions = " << maxCollisions << endl;
        for (int i = 0; i < 21; i++)
        {
            cout << "# of primary slots with " << i << " words = " << wordsInBuckets[i] << endl;
        }
        cout << "** Words in the slot with most collisions ***" << endl;
        for (int i = 0; i < maxCollisions; i++)
        {
            if (table[maxCollisionsIndex].getWords() != nullptr)
                cout << table[maxCollisionsIndex].getWords()[i] << endl;
        }
        for (int i = 1; i < 21; i++)
        {
            cout << "# of secondary hash tables trying " << i << " hash functions = " << numberOfTries[i] << endl;
            averageFunctionsTried += i * numberOfTries[i];
        }
        if (averageFunctionsTried != 0)
            averageFunctionsTried /= (size - wordsInBuckets[0] - wordsInBuckets[1]);
        cout << "Average # of hash functions tried = " << averageFunctionsTried << endl;
    }
    void find(string query)
    {
        bool exists = false;
        int index = modHash(query);
        if (table[index].mapExists)
        {
            if (table[index].getSecondMap()[table[index].modHash(query)] == query)
                exists = true;
        }
        else if (table[index].singleWord == query)
            exists = true;
        if (exists)
            cout
                << query << " found at " << index << endl;
        else
            cout << query << " not found" << endl;
    }
    bool findBool(string query)
    {
        int index = modHash(query);
        bool exists = false;
        for (int i = 0; i < table[index].getCount(); i++)
        {
            if (query == table[index].getWords()[i])
            {
                exists = true;
            }
        }
        return exists;
    }
    int size;
    Hashbucket *table;

private:
    int modHash(string s) { return hash.hash(s) % size; }
    Hash24 hash;
    int duplicates = 0;
};
#endif