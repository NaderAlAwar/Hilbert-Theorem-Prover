#ifndef IMPLOP_H
#define IMPLOP_H

#include "formula.h"
#include "variable.h"

class implOp : public formula
{
    private:
        formula *lOperand;
        formula *rOperand;

    public:
        implOp(formula *left, formula *right);
        void print();
        formula* getLeftOperand();
        formula* getRightOperand();
        void setLeftOperand(formula *left);
        void setRightOperand(formula *right);
        bool isEqual(formula *otherFormula);
        formula* substituteFormula(formula *from, formula *to);
        formula* instantiateFormula(variable *toReplace, formula *newFormula);
        formula* instFormula(formula *toReplace, formula *newFormula);
        int getSize();
        int getOpSize();
        bool containsVariable(char variable);
};

#endif