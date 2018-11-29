#include <iostream>
#include "formula.h"
#include "implOp.h"

using namespace std;

implOp::implOp(formula *left, formula *right)
{
    lOperand = left;
    rOperand = right;
}

void implOp::print()
{
    cout << "(";
    lOperand->print();
    cout << "->";
    rOperand->print();
    cout << ")";
}

formula* implOp::getLeftOperand()
{
    return lOperand;
}

formula* implOp::getRightOperand()
{
    return rOperand;
}

void implOp::setLeftOperand(formula *left)
{
    lOperand = left;
}

void implOp::setRightOperand(formula *right)
{
    rOperand = right;
}

bool implOp::isEqual(formula *otherFormula)
{
    implOp* newFormula = dynamic_cast<implOp *> (otherFormula);
    if(newFormula != NULL)  // if the dynamic cast works
    {
        if(lOperand->isEqual(newFormula->getLeftOperand()) && rOperand->isEqual(newFormula->getRightOperand()))
        {
            return true;
        }  
    }
    return false;
}

formula* implOp::substituteFormula(formula *from, formula *to)
{
    if(this->isEqual(from)) // if this implication is what we want to change
    {
        return to;
    }
    else if(this->getLeftOperand()->isEqual(from))
    {
        formula* toReturn = new implOp(to,this->getRightOperand());  // replace left operand
        return toReturn;
    }
    else if(this->getRightOperand()->isEqual(from))
    {
        formula* toReturn = new implOp(this->getLeftOperand(),to);  // replace right operand
        return toReturn; 
    }
    else
    {
        formula *newLeft = this->getLeftOperand()->substituteFormula(from, to);    // try to find a match in the left operand
        if(newLeft == NULL)
        {
            formula *newRight = this->getRightOperand()->substituteFormula(from,to); // try to find a match in the right operand
            if(newRight == NULL)
            {
                return NULL;
            }
            else
            {
                formula *toReturn = new implOp(this->getRightOperand(),newRight);   // construct a formula with the new right operand
                return toReturn;
            }
        }
        else
        {
            formula *toReturn = new implOp(newLeft, this->getRightOperand());   // construct a formula with the new form of the left operand
            return toReturn;
        }
    }
}

formula* implOp::instantiateFormula(variable *toReplace, formula *newFormula)
{
    variable* leftOperand = dynamic_cast<variable *> (this->getLeftOperand());    // try to cast the left Operand to a variable
    variable* rightOperand = dynamic_cast<variable *> (this->getRightOperand());
    formula* tempLeft,* tempRight;   // will temporarily hold a formula if either left or right are not variables. will be used to construct the new formula
    bool replaceLeft = false;
    bool replaceRight = false;

    if(leftOperand != NULL) // if the left operand is of type variable
    {
        if(leftOperand->isEqual(toReplace))
        {
            replaceLeft = true; // the left operand will be replaced
            tempLeft = newFormula;  // in order to build the new formula
        }
    }
    else
    {
        tempLeft = this->getLeftOperand()->instantiateFormula(toReplace, newFormula);   // call recursively on left operand
        if(tempLeft != NULL)    // a replacement was found in the leftOperand
        {
            replaceLeft = true;
        }
    }

    if(rightOperand != NULL)
    {
        if(rightOperand->isEqual(toReplace))
        {
            replaceRight = true;
            tempRight = newFormula;
        }
    }
    else
    {
        tempRight = this->getRightOperand()->instantiateFormula(toReplace, newFormula);
        if(tempRight != NULL)
        {
            replaceRight = true;
        }
    }

    if(replaceRight && replaceLeft)
    {
        return new implOp(tempLeft, tempRight);
    }
    else if(replaceRight)
    {
        return new implOp(this->getLeftOperand(), tempRight); // return a new formula with only the rhs changed
    }
    else if(replaceLeft)
    {
        return new implOp(tempLeft, this->getRightOperand());
    }
    else
    {
        return NULL;    // no variable was replaced
    }
    
}

formula* implOp::instFormula(formula *toReplace, formula *newFormula)
{
    if(this->isEqual(toReplace))
    {
        return newFormula;
    }
    bool replaceLeft = false;
    bool replaceRight = false;
    formula *tempLeft = NULL;
    formula *tempRight = NULL;

    if(this->getLeftOperand()->isEqual(toReplace))
    {
        replaceLeft = true;
        tempLeft = newFormula;
    }
    else
    {
        tempLeft = this->getLeftOperand()->instFormula(toReplace,newFormula);
        if(tempLeft != NULL)
        {
            replaceLeft = true;
        }
    }
    
    if(this->getRightOperand()->isEqual(toReplace))
    {
        replaceRight = true;
        tempRight = newFormula;
    }
    else
    {
        tempRight = this->getRightOperand()->instFormula(toReplace,newFormula);
        if(tempRight != NULL)
        {
            replaceRight = true;
        }
    }

    if(replaceRight && replaceLeft)
    {
        return new implOp(tempLeft, tempRight);
    }
    else if(replaceRight)
    {
        return new implOp(this->getLeftOperand(), tempRight); // return a new formula with only the rhs changed
    }
    else if(replaceLeft)
    {
        return new implOp(tempLeft, this->getRightOperand());
    }
    else
    {
        return NULL;    // no variable was replaced
    }
}

int implOp::getSize()
{
    return this->getLeftOperand()->getSize() + this->getRightOperand()->getSize();
}

int implOp::getOpSize()
{
    return this->getLeftOperand()->getOpSize() + this->getRightOperand()->getOpSize() + 1;
}

bool implOp::containsVariable(char variable)
{
    if(this->getLeftOperand()->containsVariable(variable) || this->getRightOperand()->containsVariable(variable))
    {
        return true;
    }
}
