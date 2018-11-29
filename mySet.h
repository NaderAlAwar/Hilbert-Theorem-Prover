#ifndef MYSET_H
#define MYSET_H

#include "formula.h"
#include <vector>

using namespace std;

class mySet
{
    private:
        vector<formula*> contents;
        int limit;  // helps the prover not exceed the set number of theorems
        bool limitExists;
    public:
        mySet();
        mySet(int numberOfTheorems);
        void push(formula *newFormula);
        int getSize();
        formula* at(int index);
};

#endif