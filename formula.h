#ifndef FORMULA_H
#define FORMULA_H

// #include "variable.h"

class variable;

class formula
{
    public:
        virtual void print() = 0;
        virtual bool isEqual(formula *otherFormula) = 0;
        virtual formula* substituteFormula(formula *from, formula* to) = 0; // replace single occurrence of from with to
        virtual formula* instantiateFormula(variable *toReplace, formula *newFormula) = 0; // replace all occurrences of toReplace with newFormula
        virtual formula* instFormula(formula *toReplace, formula *newFormula) = 0;
        virtual int getSize() = 0;    // returns the number of variables in a formula
        virtual int getOpSize() = 0;    // returns the number of operators in a formula
        virtual bool containsVariable(char variable) = 0;
};

#endif