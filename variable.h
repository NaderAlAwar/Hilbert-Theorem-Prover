#ifndef VARIABLE_H
#define VARIABLE_H

#include "formula.h"

class variable : public formula
{
    private:
        char var;

    public:
        variable(char var);
        void print();
        char getVariable();
        bool isEqual(formula *otherFormula);
        formula* substituteFormula(formula *from, formula *to);
        formula* instantiateFormula(variable *toReplace, formula *newFormula);
        formula* instFormula(formula *toReplace, formula *newFormula);
        int getSize();
        int getOpSize();
        bool containsVariable(char variable);
};

#endif