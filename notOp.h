#ifndef NOTOP_H
#define NOTOP_H

#include "formula.h"
#include "variable.h"

class notOp : public formula
{
    private:
        formula *operand;
    public:
        notOp(formula *operand);
        void print();
        formula* getOperand();
        bool isEqual(formula *otherFormula);
        formula* substituteFormula(formula *from, formula *to);
        formula* instantiateFormula(variable *toReplace, formula *newFormula);
        formula* instFormula(formula *toReplace, formula *newFormula);
        int getSize();
        int getOpSize();
        bool containsVariable(char variable);
};

#endif