#include <iostream>

#include "formula.h"
#include "notOp.h"

using namespace std;

notOp::notOp(formula *oper)
{
    operand = oper;
}

void notOp::print()
{
    cout << "!";
    cout << "(";
    operand->print();
    cout << ")";
}

formula* notOp::getOperand()
{
    return operand;
}

bool notOp::isEqual(formula *otherFormula)
{
    notOp* newFormula = dynamic_cast<notOp *> (otherFormula);
    if(newFormula != NULL) // if the dynamic cast works
    {
        if(operand->isEqual(newFormula->getOperand()))
        {
            return true;
        }
    }
    return false;
}

formula* notOp::substituteFormula(formula *from, formula *to)
{
    if(this->isEqual(from))
    {
        return to;
    }
    else if(this->getOperand()->isEqual(from))
    {
        formula* toReturn = new notOp(to);
        return toReturn;
    }
    else
    {
        formula *newOperand = this->getOperand()->substituteFormula(from,to);
        formula *toReturn = new notOp(newOperand);
        if(newOperand == NULL)
        {
            return NULL;
        }
        else
        {
            return toReturn;
        }
    }
}

formula* notOp::instantiateFormula(variable *toReplace, formula *newFormula)
{
    variable* currentOperand = dynamic_cast<variable*> (this->getOperand());    // attempt to cast operand to a variable
    formula* tempCurrent;
    bool replaceCurrent = false;

    if(currentOperand != NULL)  // if current operand is a variable
    {
        if(currentOperand->isEqual(toReplace))
        {
            replaceCurrent = true;
            tempCurrent = newFormula;
        }
    }
    else
    {
        tempCurrent = this->getOperand()->instantiateFormula(toReplace, newFormula);    // call instantiate on operand
        if(tempCurrent != NULL)
        {
            replaceCurrent = true;
        }
    }
    
    if(replaceCurrent)
    {
        return new notOp(tempCurrent);
    }
    else
    {
        return NULL;
    }

}

formula* notOp::instFormula(formula *toReplace, formula *newFormula)
{
    if(this->isEqual(toReplace))
    {
        return newFormula;
    }
    
    bool replaceCurrent = false;
    formula* tempCurrent = NULL;

    if(this->getOperand()->isEqual(toReplace))
    {
        replaceCurrent = true;
        tempCurrent = newFormula;
    }
    else
    {
        tempCurrent = this->getOperand()->instFormula(toReplace,newFormula);
        if(tempCurrent != NULL)
        {
            replaceCurrent = true;
        }
    }

    if(replaceCurrent)
    {
        return new notOp(tempCurrent);
    }
}

int notOp::getSize()
{
    return this->getOperand()->getSize();
}

int notOp::getOpSize()
{
    return this->getOperand()->getOpSize() + 1;
}

bool notOp::containsVariable(char variable)
{
    return this->getOperand()->containsVariable();
}